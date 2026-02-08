package com.example.lwprpcharness

import android.content.Context
import android.content.res.AssetManager
import android.opengl.EGL14
import android.opengl.EGLConfig
import android.opengl.EGLContext
import android.opengl.EGLDisplay
import android.opengl.EGLSurface
import android.util.Log
import com.sonymobile.experienceflow.renderer.CurveRenderer
import java.io.File
import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.util.concurrent.Callable
import java.util.concurrent.Executors
import java.util.concurrent.Future
import java.util.concurrent.TimeUnit
import java.util.concurrent.atomic.AtomicReference
import android.opengl.GLES20
import java.security.MessageDigest

/**
 * Drives the JNI entrypoints via a minimal CurveRenderer stub class (same package/name
 * as the original Sony app).
 *
 * Also provides "state pointers" so the PC side can read/diff object memory.
 */
class CurveHarness(private val context: Context, private val session: NativeSession) {

    companion object {
        private const val TAG = "CurveHarness"

        // Offsets (relative to module base) inferred from the decompiled native pseudocode.
        // These are in .bss, so they must be added to the module base.
        private const val OFF_MAP_INT_RENDERERIF = 0x18860L
        private const val OFF_COUNTER_NEXT_ID = 0x18878L

        // Mangled C++ symbol for std::map<int, RendererInterface>::operator[](int&)
        private const val SYM_MAP_INDEX =
            "_ZNSt3mapIi17RendererInterfaceSt4lessIiESaISt4pairIKiS0_EEEixERS4_"

        // RendererInterface-like entry stored in the std::map:
        //   [0x00] renderer*   ("*v6 = v8" in the decompiled init path)
        //   [0x04] inited flag ("*((uint8_t*)v6 + 4)" is checked/set)
        private const val RI_OFF_RENDERER_PTR = 0x00

        // Renderer object field:
        //   Curve::requestColors(*(Curve **)(renderer + 92), ...)
        // so the Curve* lives at renderer+0x5C (92).
        private const val R_OFF_CURVE_PTR = 0x5C

        // Conservative snapshot sizes (raw bytes) based on static offset evidence.
        // You can override from PC by specifying size in read().
        const val SNAP_RI_SIZE = 0x80
        const val SNAP_CURVE_SIZE = 0x180
        const val SNAP_RENDERER_SIZE = 0x400  // guess; adjust once we map renderer fields
    }

    private class CurveRendererHarness : CurveRenderer() {
        fun initPublic(am: AssetManager): Int = init(am)
        fun activatePublic(id: Int) = activate(id)
        fun deactivatePublic(id: Int) = deactivate(id)
        fun requestColorsPublic(id: Int, am: AssetManager, theme: Int) = requestColors(id, am, theme)
        // Sony signature: (id, x, y, w, h, sw, sh)
        fun updateScreenLayoutPublic(id: Int, x: Int, y: Int, w: Int, h: Int, sw: Int, sh: Int) =
            updateScreenLayout(id, x, y, w, h, sw, sh)
        fun renderPublic(id: Int, am: AssetManager) = render(id, am)
        fun touchDownPublic(id: Int, x: Float, y: Float) = touchDown(id, x, y)
        fun touchPublic(id: Int, x: Float, y: Float) = touch(id, x, y)
        fun touchUpPublic(id: Int, x: Float, y: Float) = touchUp(id, x, y)
        fun getSleepRecommendationPublic(id: Int): Int = getSleepRecommendation(id)
    }

    private val drv = CurveRendererHarness()
    private var id: Int = -1
	    // render() 直後の 1x1 ReadPixels から得た簡易ハッシュ（PC 側の見た目比較用）
	    private var frameRb: FrameReadback? = null

    private data class Globals(
        val mapAddr: Long,
        val counterAddr: Long,
        val source: String,
    )

    private val curveThread = AtomicReference<Thread>()
    private val curveExec = Executors.newSingleThreadExecutor { r ->
        Thread(r, "CurveGL").also { curveThread.set(it) }
    }

    @Volatile private var egl: EglEnv? = null
    @Volatile private var globals: Globals? = null

    private fun isCurveThread(): Boolean = Thread.currentThread() == curveThread.get()

    private fun <T> onCurve(block: () -> T): T {
        if (isCurveThread()) return block()
        val f = curveExec.submit(Callable { block() })
        return f.get(60, TimeUnit.SECONDS)
    }

    /**
     * The Sony renderer code assumes a current EGL context. Some vendor drivers will
     * hard-crash if you call into GLES without one, so we keep a tiny pbuffer context
     * alive on a dedicated thread.
     */
    private class EglEnv {
        private val display: EGLDisplay
        private val surface: EGLSurface
        private val context: EGLContext

        init {
            display = EGL14.eglGetDisplay(EGL14.EGL_DEFAULT_DISPLAY)
            require(display != EGL14.EGL_NO_DISPLAY) { "EGL: no display" }
            val vers = IntArray(2)
            require(EGL14.eglInitialize(display, vers, 0, vers, 1)) { "EGL: init failed" }

            val attribs = intArrayOf(
                EGL14.EGL_RENDERABLE_TYPE, EGL14.EGL_OPENGL_ES2_BIT,
                EGL14.EGL_SURFACE_TYPE, EGL14.EGL_PBUFFER_BIT,
                EGL14.EGL_RED_SIZE, 8,
                EGL14.EGL_GREEN_SIZE, 8,
                EGL14.EGL_BLUE_SIZE, 8,
                EGL14.EGL_ALPHA_SIZE, 8,
                EGL14.EGL_NONE,
            )
            val configs = arrayOfNulls<EGLConfig>(1)
            val num = IntArray(1)
            require(EGL14.eglChooseConfig(display, attribs, 0, configs, 0, configs.size, num, 0) && num[0] > 0) {
                "EGL: no config"
            }
            val cfg = configs[0]!!

            val ctxAttribs = intArrayOf(
                EGL14.EGL_CONTEXT_CLIENT_VERSION, 2,
                EGL14.EGL_NONE,
            )
            context = EGL14.eglCreateContext(display, cfg, EGL14.EGL_NO_CONTEXT, ctxAttribs, 0)
            require(context != EGL14.EGL_NO_CONTEXT) { "EGL: create context failed" }

            val surfAttribs = intArrayOf(
                EGL14.EGL_WIDTH, 1,
                EGL14.EGL_HEIGHT, 1,
                EGL14.EGL_NONE,
            )
            surface = EGL14.eglCreatePbufferSurface(display, cfg, surfAttribs, 0)
            require(surface != EGL14.EGL_NO_SURFACE) { "EGL: create surface failed" }

            makeCurrent()
        }

        fun makeCurrent() {
            require(EGL14.eglMakeCurrent(display, surface, surface, context)) { "EGL: makeCurrent failed" }
        }
    }

    private fun ensureEgl() {
        if (egl == null) {
            egl = EglEnv()
        }
        egl?.makeCurrent()
    }

    private fun ensureVmLoaded() {
        // Ensure libraries are VM-visible for static JNI symbol lookup.
        // Prefer absolute path in nativeLibraryDir to avoid name resolution issues.
        val libDir = File(context.applicationInfo.nativeLibraryDir)
        val gnustl = File(libDir, "libgnustl_shared.so")
        val lwplocal = File(libDir, "liblwplocal_proxy.so")
        try {
            if (gnustl.exists()) System.load(gnustl.absolutePath)
        } catch (_: Throwable) {
        }
        try {
            if (lwplocal.exists()) System.load(lwplocal.absolutePath)
        } catch (t: Throwable) {
            // If this fails, native method calls will throw UnsatisfiedLinkError.
            Log.e(TAG, "System.load liblwplocal_proxy failed: " + t.message, t)
        }
    }

    private fun initIfNeededLocked(): Int {
        ensureVmLoaded()
        ensureEgl()
        if (id >= 0) return id
        id = drv.initPublic(context.assets)
        // New renderer ID changes global state; drop cached globals.
        globals = null
        return id
    }

    

fun reset(): Map<String, Any?> = onCurve {
    val out = LinkedHashMap<String, Any?>()
    val oldId = id
    out["oldId"] = oldId
    if (oldId != -1) {
        try {
            drv.deactivatePublic(oldId)
            out["deactivate"] = "ok"
        } catch (t: Throwable) {
            out["deactivate"] = "error"
            out["deactivate_error"] = (t.javaClass.name + ": " + (t.message ?: ""))
        }
    }
    // Force next initIfNeeded() to create a fresh curve instance.
    id = -1
    out["ok"] = true
    out
}
    fun initIfNeeded(): Int = onCurve { initIfNeededLocked() }

    private fun u16le(b: ByteArray, off: Int): Int {
        return (b[off].toInt() and 0xFF) or ((b[off + 1].toInt() and 0xFF) shl 8)
    }

    private fun u32le(b: ByteArray, off: Int): Long {
        val v = (b[off].toInt() and 0xFF) or
            ((b[off + 1].toInt() and 0xFF) shl 8) or
            ((b[off + 2].toInt() and 0xFF) shl 16) or
            ((b[off + 3].toInt() and 0xFF) shl 24)
        return v.toLong() and 0xFFFFFFFFL
    }

    private fun readU32(addr: Long): Long {
        val buf = NativeBridge.readMem(addr, 4)
        return u32le(buf, 0)
    }

    private fun resolveGlobalsLocked(moduleBase: Long, loadedPath: String): Globals {
        globals?.let { return it }

        val moduleName = File(loadedPath).name
        val viaScan = tryResolveGlobalsByScanning(moduleName)
        if (viaScan != null) {
            globals = viaScan
            return viaScan
        }

        val fallback = Globals(
            mapAddr = moduleBase + OFF_MAP_INT_RENDERERIF,
            counterAddr = moduleBase + OFF_COUNTER_NEXT_ID,
            source = "fixed_offsets",
        )
        globals = fallback
        return fallback
    }

    /**
     * Try to discover the globals addresses (map<int,RendererInterface> and the next-id counter)
     * by scanning literal-pool references in CurveRenderer_init and then probing by calling init.
     */
    private fun tryResolveGlobalsByScanning(moduleName: String): Globals? {
        val initFn = NativeBridge.dlsym(session.handle, "Java_com_sonymobile_experienceflow_renderer_CurveRenderer_init")
        if (initFn == 0L) return null

        val mappings = ProcMaps.findModuleMappings(moduleName)
        if (mappings.isEmpty()) return null
        val rwSegs = mappings.filter { it.perms.startsWith("rw") }
        if (rwSegs.isEmpty()) return null

        fun inRw(addr: Long): Boolean = rwSegs.any { addr >= it.start && addr < it.end }

        val candidates = scanLiteralPoolAbs(initFn, ::inRw)
        if (candidates.size < 2) return null

        // Snapshot before
        val before = candidates.associateWith { readU32(it) }

        // Probe: call init once more to force counter increment / map update.
        try {
            ensureEgl()
            drv.initPublic(context.assets)
        } catch (t: Throwable) {
            Log.w(TAG, "probe initPublic failed: ${t.message}")
            return null
        }

        val after = candidates.associateWith { readU32(it) }

        // Pick counter: value should increase by a small delta (typically +1).
        val counterCand = candidates
            .map { addr ->
                val b = before[addr] ?: 0L
                val a = after[addr] ?: 0L
                val delta = (a - b) and 0xFFFFFFFFL
                Triple(addr, a, delta)
            }
            .filter { (_, a, delta) -> a in 1..0x100000 && delta in 1..8 }
            .minByOrNull { (_, a, delta) -> (if (delta == 1L) 0 else 1) * 1_000_000L + a }

        val counterAddr = counterCand?.first ?: return null

        // Pick map: best guess is “the other one”; if multiple remain, prefer a pointer-ish value.
        val rest = candidates.filter { it != counterAddr }
        val mapAddr = when {
            rest.size == 1 -> rest[0]
            rest.isNotEmpty() -> {
                rest.maxByOrNull { after[it] ?: 0L } ?: rest[0]
            }
            else -> return null
        }

        return Globals(
            mapAddr = mapAddr,
            counterAddr = counterAddr,
            source = "scan_init_literalpool",
        )
    }

    private fun scanLiteralPoolAbs(initFn: Long, inRw: (Long) -> Boolean): Set<Long> {
        val codeAddr = initFn and 0xFFFFFFFEL // clear Thumb bit if present
        val codeMap = ProcMaps.findEntryContaining(codeAddr) ?: return emptySet()

        val maxLen = 0x1200L
        val len = kotlin.math.min(maxLen, codeMap.end - codeAddr).toInt().coerceAtLeast(0)
        if (len < 8) return emptySet()

        val code = NativeBridge.readMem(codeAddr, len)
        val codeEnd = codeAddr + code.size

        fun readU32MaybeInline(addr: Long): Long {
            return if (addr >= codeAddr && addr + 4 <= codeEnd) {
                val off = (addr - codeAddr).toInt()
                u32le(code, off)
            } else {
                readU32(addr)
            }
        }

        val out = LinkedHashSet<Long>()
        val isThumb = (initFn and 1L) != 0L
        if (isThumb) {
            // Thumb literal load: LDR Rt, [PC, #imm*4]  => 0b01001 Rt imm8
            var i = 0
            while (i + 2 <= code.size) {
                val hw = u16le(code, i)
                if ((hw and 0xF800) == 0x4800) {
                    val imm8 = hw and 0xFF
                    val pc = ((codeAddr + i + 4) and 0xFFFFFFFCL)
                    val litAddr = pc + imm8.toLong() * 4L
                    if (litAddr + 4 <= codeMap.end) {
                        val abs = readU32MaybeInline(litAddr)
                        if (inRw(abs)) out.add(abs)
                    }
                }
                i += 2
            }
        } else {
            // ARM literal load: LDR Rd, [PC, #imm12]  => 0xE59Fxxxx / 0xE51Fxxxx
            var i = 0
            while (i + 4 <= code.size) {
                val w = u32le(code, i)
                val hi = w and 0xFFFF0000L
                if (hi == 0xE59F0000L || hi == 0xE51F0000L) {
                    val imm = w and 0xFFF
                    val pc = ((codeAddr + i + 8) and 0xFFFFFFFCL)
                    val litAddr = if (hi == 0xE59F0000L) pc + imm else pc - imm
                    if (litAddr + 4 <= codeMap.end && litAddr >= codeMap.start) {
                        val abs = readU32MaybeInline(litAddr)
                        if (inRw(abs)) out.add(abs)
                    }
                }
                i += 4
            }
        }
        return out
    }

    data class Ptrs(
        val id: Int,
        val moduleBase: Long,
        val mapAddr: Long,
        val counterAddr: Long,
        val rendererInterfacePtr: Long,
        val rendererPtr: Long,
        val curvePtr: Long,
        val globalsSource: String
    )

    private fun getPtrsLocked(): Ptrs {
        val idNow = initIfNeededLocked()
        val loadedPath = session.loadedPath ?: "liblwplocal_proxy.so"
        val base = ProcMaps.findModuleBase(loadedPath)
            ?: ProcMaps.findModuleBase("liblwplocal.so")
            ?: 0L
        if (base == 0L) {
            return Ptrs(idNow, 0L, 0L, 0L, 0L, 0L, 0L, "no_module_base")
        }

        val g = resolveGlobalsLocked(base, loadedPath)
        val mapAddr = g.mapAddr
        val counterAddr = g.counterAddr

        // Verify globals fall into a RW segment of the mapped module.
        val moduleName = File(loadedPath).name
        val mappings = ProcMaps.findModuleMappings(moduleName)
        val rwSegs = mappings.filter { it.perms.startsWith("rw") }
        fun inRw(addr: Long): Boolean = rwSegs.any { addr >= it.start && addr < it.end }

        // If we cannot validate, or the addresses are not in RW, do not attempt std::map access.
        if (rwSegs.isEmpty() || !inRw(mapAddr) || !inRw(counterAddr)) {
            return Ptrs(idNow, base, mapAddr, counterAddr, 0L, 0L, 0L, g.source + "_not_rw")
        }

        // When addresses come from fixed offsets, treat as unsafe for pointer-walking.
        // (It may still be correct on some builds, but we avoid crashing when it is not.)
        if (g.source == "fixed_offsets") {
            return Ptrs(idNow, base, mapAddr, counterAddr, 0L, 0L, 0L, g.source + "_disabled")
        }

        // dlsym map operator
        val fn = NativeBridge.dlsym(session.handle, SYM_MAP_INDEX)
        if (fn == 0L) {
            return Ptrs(idNow, base, mapAddr, counterAddr, 0L, 0L, 0L, g.source + "_dlsym_fail")
        }

        // prepare key (int id) in native memory
        val keyPtr = NativeBridge.malloc(4)
        try {
            val bb = ByteBuffer.allocate(4).order(ByteOrder.LITTLE_ENDIAN)
            bb.putInt(idNow)
            NativeBridge.writeMem(keyPtr, bb.array())

            val res = try {
                NativeBridge.callWords(fn, intArrayOf(mapAddr.toInt(), keyPtr.toInt()))
            } catch (t: Throwable) {
                null
            }

            val riPtr = ((res?.getOrNull(0) ?: 0L) and 0xFFFFFFFFL)
            if (riPtr < 0x10000L) {
                return Ptrs(idNow, base, mapAddr, counterAddr, riPtr, 0L, 0L, g.source + "_mapop_fail")
            }

            // RendererInterface-like entry: first word is renderer*
            val rPtr = try {
                val rPtrBytes = NativeBridge.readMem(riPtr + RI_OFF_RENDERER_PTR, 4)
                ByteBuffer.wrap(rPtrBytes).order(ByteOrder.LITTLE_ENDIAN).int.toLong() and 0xFFFFFFFFL
            } catch (t: Throwable) {
                0L
            }

            // Curve* is stored inside the renderer object at renderer + 0x5C (92).
            val cPtr: Long = if (rPtr >= 0x10000L && rPtr < 0xFFFF0000L) {
                try {
                    val cPtrBytes = NativeBridge.readMem(rPtr + R_OFF_CURVE_PTR, 4)
                    ByteBuffer.wrap(cPtrBytes).order(ByteOrder.LITTLE_ENDIAN).int.toLong() and 0xFFFFFFFFL
                } catch (t: Throwable) {
                    0L
                }
            } else {
                0L
            }

            return Ptrs(idNow, base, mapAddr, counterAddr, riPtr, rPtr, cPtr, g.source)
        } finally {
            NativeBridge.free(keyPtr)
        }
    }

    private fun getPtrs(): Ptrs = onCurve { getPtrsLocked() }

    
private data class FrameReadback(val rgbaHex: String, val sha256: String, val glError: Int)

private fun readbackFrame1x1(): FrameReadback? {
    // EGL コンテキストが current であることが前提（ensureEgl() の後、render の直後で呼ぶ）
    return try {
        val buf = ByteBuffer.allocateDirect(4).order(ByteOrder.nativeOrder())
        GLES20.glFinish()
        GLES20.glReadPixels(0, 0, 1, 1, GLES20.GL_RGBA, GLES20.GL_UNSIGNED_BYTE, buf)
        val err = GLES20.glGetError()
        val b = ByteArray(4)
        buf.position(0)
        buf.get(b)
        val rgbaHex = "%02x%02x%02x%02x".format(b[0].toInt() and 0xff, b[1].toInt() and 0xff, b[2].toInt() and 0xff, b[3].toInt() and 0xff)
        val md = MessageDigest.getInstance("SHA-256")
        val sha = md.digest(b).joinToString("") { "%02x".format(it) }
        FrameReadback(rgbaHex = rgbaHex, sha256 = sha, glError = err)
    } catch (_: Throwable) {
        null
    }
}

fun call(method: String, args: List<Any?>): Map<String, Any?> = onCurve {
        val idNow = initIfNeededLocked()
        val am = context.assets

        val result: Any? = when (method) {
            "activate" -> { drv.activatePublic(idNow); null }
            "deactivate" -> { drv.deactivatePublic(idNow); null }
            "requestColors" -> {
                val theme = (args.getOrNull(0) as? Number)?.toInt() ?: 0
                drv.requestColorsPublic(idNow, am, theme); null
            }
            "updateScreenLayout" -> {
                // CurveRendererImpl.updateScreenLayout(x, y, w, h, sw, sh)
                val x = (args.getOrNull(0) as? Number)?.toInt() ?: 0
                val y = (args.getOrNull(1) as? Number)?.toInt() ?: 0
                val w = (args.getOrNull(2) as? Number)?.toInt() ?: 1080
                val h = (args.getOrNull(3) as? Number)?.toInt() ?: 2400
                val sw = (args.getOrNull(4) as? Number)?.toInt() ?: w
                val sh = (args.getOrNull(5) as? Number)?.toInt() ?: h
                drv.updateScreenLayoutPublic(idNow, x, y, w, h, sw, sh)
                null
            }
            "render" -> { drv.renderPublic(idNow, am); frameRb = readbackFrame1x1(); null }
            "touchDown" -> {
                val x = (args.getOrNull(0) as? Number)?.toFloat() ?: 0.5f
                val y = (args.getOrNull(1) as? Number)?.toFloat() ?: 0.5f
                drv.touchDownPublic(idNow, x, y); null
            }
            "touch" -> {
                val x = (args.getOrNull(0) as? Number)?.toFloat() ?: 0.6f
                val y = (args.getOrNull(1) as? Number)?.toFloat() ?: 0.6f
                drv.touchPublic(idNow, x, y); null
            }
            "touchUp" -> {
                val x = (args.getOrNull(0) as? Number)?.toFloat() ?: 0.6f
                val y = (args.getOrNull(1) as? Number)?.toFloat() ?: 0.6f
                drv.touchUpPublic(idNow, x, y); null
            }
            "getSleepRecommendation" -> drv.getSleepRecommendationPublic(idNow)
            else -> throw IllegalArgumentException("unknown method: $method")
        }

        val p = try { getPtrsLocked() } catch (t: Throwable) { Ptrs(idNow, 0L, 0L, 0L, 0L, 0L, 0L, "ptrs_exception") }
        val out = LinkedHashMap<String, Any?>()
        out["ok"] = true
        out["method"] = method
        out["result"] = result
        out["id"] = p.id
        out["moduleBase"] = "0x" + p.moduleBase.toString(16)
        out["mapAddr"] = "0x" + p.mapAddr.toString(16)
        out["counterAddr"] = "0x" + p.counterAddr.toString(16)
        out["rendererInterfacePtr"] = "0x" + p.rendererInterfacePtr.toString(16)
        out["rendererPtr"] = "0x" + p.rendererPtr.toString(16)
        out["curvePtr"] = "0x" + p.curvePtr.toString(16)
        out["globalsSource"] = p.globalsSource
// render のフレーム（1x1 readback）ハッシュ。内部レイアウトが異なる C 化版でも「見た目」比較に使う。
if (method == "render") {
    out["frameRgbaHex"] = frameRb?.rgbaHex
    out["frameSha256"] = frameRb?.sha256
    out["frameGlErr"] = frameRb?.glError
}

        out
    }

    fun ptrs(): Map<String, Any?> = onCurve {
        val p = try { getPtrsLocked() } catch (t: Throwable) { Ptrs(0, 0L, 0L, 0L, 0L, 0L, 0L, "ptrs_exception") }
        linkedMapOf(
            "ok" to true,
            "id" to p.id,
            "moduleBase" to ("0x" + p.moduleBase.toString(16)),
            "mapAddr" to ("0x" + p.mapAddr.toString(16)),
            "counterAddr" to ("0x" + p.counterAddr.toString(16)),
            "rendererInterfacePtr" to ("0x" + p.rendererInterfacePtr.toString(16)),
            "rendererPtr" to ("0x" + p.rendererPtr.toString(16)),
            "curvePtr" to ("0x" + p.curvePtr.toString(16)),
            "globalsSource" to p.globalsSource,
            "hintSizes" to mapOf(
                "rendererInterface" to SNAP_RI_SIZE,
                "curve" to SNAP_CURVE_SIZE,
                "renderer" to SNAP_RENDERER_SIZE
            )
        )
    }
}
