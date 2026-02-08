package com.example.lwprpcharness

import android.content.Context
import android.util.Base64
import android.util.Log
import android.system.Os
import java.security.MessageDigest
import java.io.FileInputStream
import android.os.Process
import android.os.Build
import java.io.BufferedReader
import java.io.BufferedWriter
import java.io.File
import java.io.InputStreamReader
import java.io.OutputStreamWriter
import java.net.InetSocketAddress
import java.net.ServerSocket
import java.net.Socket
import java.util.concurrent.atomic.AtomicBoolean
import org.json.JSONArray
import org.json.JSONObject

private const val TAG = "RpcServer"
private const val VERSION = "curve_trycatch_v2_fix26_proxy5_dynprobe_targets_v1"

class RpcServer(
    private val port: Int,
    private val logWriter: LogWriter,
    private val session: NativeSession,
    private val appContext: Context
) {

    private val running = AtomicBoolean(false)
    private var thread: Thread? = null
    private var serverSocket: ServerSocket? = null

    // Drives JNI entrypoints via stub CurveRenderer class
    private var curveHarness: CurveHarness? = null
    private fun curve(): CurveHarness {
        val cur = curveHarness
        if (cur != null) return cur
        val created = CurveHarness(appContext, session)
        curveHarness = created
        return created
    }

    fun start() {
        if (running.getAndSet(true)) return
        thread = Thread {
            try {
                val ss = ServerSocket()
                ss.reuseAddress = true

                // IMPORTANT:
                // Bind to all local interfaces (0.0.0.0) so adb forward definitely reaches it,
                // while it is still practically only reachable from the device itself unless you expose ports.
                ss.bind(InetSocketAddress(port))

                serverSocket = ss
                Log.i("LwpRpc", "RPC server listening on 0.0.0.0:$port")

                while (running.get()) {
                    val client = ss.accept()
                    Log.i("LwpRpc", "client accepted: ${client.inetAddress?.hostAddress}:${client.port}")
                    handleClient(client)
                }
            } catch (e: Exception) {
                Log.e("LwpRpc", "server_error", e)
                logWriter.logLine(jsonLine("server_error", mapOf("err" to (e.message ?: ""), "ex" to e.javaClass.name)))
            } finally {
                try { serverSocket?.close() } catch (_: Exception) {}
                running.set(false)
                Log.i("LwpRpc", "RPC server stopped")
            }
        }
        thread!!.name = "RpcServer"
        thread!!.start()
    }

    fun stop() {
        running.set(false)
        try { serverSocket?.close() } catch (_: Exception) {}
    }

    private fun handleClient(sock: Socket) {
        sock.use { s ->
            val br = BufferedReader(InputStreamReader(s.getInputStream(), Charsets.UTF_8))
            val bw = BufferedWriter(OutputStreamWriter(s.getOutputStream(), Charsets.UTF_8))

            var line: String?
            while (true) {
                line = br.readLine() ?: break
                if (line!!.isBlank()) continue

                val reqRaw = line!!
                val ts = System.currentTimeMillis()

                val resp: JSONObject = try {
                    val req = JSONObject(reqRaw)
                    handleRequest(req)
                } catch (e: Exception) {
                    JSONObject().put("ok", false).put("error", "bad_request").put("message", e.message ?: "")
                }

                val logObj = JSONObject()
                    .put("ts", ts)
                    .put("req", safeJson(reqRaw))
                    .put("resp", resp)
                logWriter.logLine(logObj.toString())

                // Also to logcat for quick diagnosis
                Log.i("LwpRpc", "req=$reqRaw resp=${resp.toString()}")

                bw.write(resp.toString())
                bw.write("\n")
                bw.flush()
            }
        }
    }

    private fun handleRequest(req: JSONObject): JSONObject {
        return try {
            val cmd = req.optString("cmd", "")
            when (cmd) {
            "ping" -> JSONObject()
                .put("ok", true)
                .put("version", VERSION)
                // Debug: report dlopen flag constants to confirm installed build.
                .put("rtld_now", NativeBridge.RTLD_NOW)
                .put("rtld_global", NativeBridge.RTLD_GLOBAL)
            "device_info" -> {
                val nativeDir = appContext.applicationInfo.nativeLibraryDir
                val pm = appContext.packageManager
                val pi = pm.getPackageInfo(appContext.packageName, 0)
                val vc: Long = if (android.os.Build.VERSION.SDK_INT >= 28) pi.longVersionCode else pi.versionCode.toLong()
                val abis = JSONArray()
                for (a in Build.SUPPORTED_ABIS) abis.put(a)
                JSONObject()
                    .put("ok", true)
                    .put("version", VERSION)
                    .put("package", appContext.packageName)
                    .put("versionName", pi.versionName ?: "")
                    .put("versionCode", vc)
                    .put("sdk", Build.VERSION.SDK_INT)
                    .put("abis", abis)
                    .put("brand", Build.BRAND ?: "")
                    .put("manufacturer", Build.MANUFACTURER ?: "")
                    .put("model", Build.MODEL ?: "")
                    .put("device", Build.DEVICE ?: "")
                    .put("product", Build.PRODUCT ?: "")
                    .put("fingerprint", Build.FINGERPRINT ?: "")
                    .put("pid", Process.myPid())
                    .put("uid", Process.myUid())
                    .put("nativeLibraryDir", nativeDir)
            }
            "libdir_list" -> {
                val includeHash = req.optBoolean("hash", false)
                val dir = File(appContext.applicationInfo.nativeLibraryDir)
                val files = dir.listFiles()?.sortedBy { it.name } ?: emptyList()
                val arr = JSONArray()
                for (f in files) {
                    val o = JSONObject()
                        .put("name", f.name)
                        .put("size", f.length())
                        .put("mtime", f.lastModified())
                    if (includeHash) {
                        o.put("sha256", sha256File(f))
                    }
                    arr.put(o)
                }
                JSONObject().put("ok", true).put("dir", dir.absolutePath).put("count", arr.length()).put("files", arr)
            }
            "file_hash" -> {
                val pathRaw = req.optString("path", "")
                val name = req.optString("name", "")
                val path = when {
                    pathRaw.isNotEmpty() -> pathRaw
                    name.isNotEmpty() -> File(appContext.applicationInfo.nativeLibraryDir, name).absolutePath
                    else -> ""
                }
                if (path.isEmpty()) {
                    JSONObject().put("ok", false).put("error", "no_path")
                } else {
                    val f = File(path)
                    if (!f.exists() || !f.isFile) {
                        JSONObject().put("ok", false).put("error", "not_found").put("path", path)
                    } else {
                        JSONObject().put("ok", true)
                            .put("path", f.absolutePath)
                            .put("size", f.length())
                            .put("mtime", f.lastModified())
                            .put("sha256", sha256File(f))
                    }
                }
            }

            "proc_status" -> {
                val maxLines = req.optInt("max", 200).coerceIn(1, 4000)
                val parsed = req.optBoolean("parsed", true)
                val txt = readTextLines("/proc/self/status", maxLines)
                if (!parsed) {
                    JSONObject().put("ok", true).put("path", "/proc/self/status").put("lines", JSONArray(txt))
                } else {
                    val obj = JSONObject()
                    for (ln in txt) {
                        val idx = ln.indexOf(':')
                        if (idx <= 0) continue
                        val k = ln.substring(0, idx).trim()
                        val v = ln.substring(idx + 1).trim()
                        obj.put(k, v)
                    }
                    JSONObject().put("ok", true).put("path", "/proc/self/status").put("kv", obj)
                }
            }

            "proc_limits" -> {
                val maxLines = req.optInt("max", 200).coerceIn(1, 4000)
                val txt = readTextLines("/proc/self/limits", maxLines)
                JSONObject().put("ok", true).put("path", "/proc/self/limits").put("lines", JSONArray(txt))
            }

            "threads" -> {
                val max = req.optInt("max", 512).coerceIn(1, 8192)
                val list = listThreads(max)
                JSONObject().put("ok", true).put("count", list.length()).put("list", list)
            }

            "fds" -> {
                val max = req.optInt("max", 512).coerceIn(1, 8192)
                val list = listFds(max)
                JSONObject().put("ok", true).put("count", list.length()).put("list", list)
            }
            "maps" -> {
                val filter = req.optString("filter", "")
                val max = req.optInt("max", 200).coerceIn(1, 5000)
                val maps = ProcMaps.parseSelf()
                val outArr = JSONArray()
                var n = 0
                for (m in maps) {
                    if (filter.isNotEmpty() && !m.path.contains(filter)) continue
                    val o = JSONObject()
                        .put("start", toHex(m.start))
                        .put("end", toHex(m.end))
                        .put("perms", m.perms)
                        .put("offset", toHex(m.offset))
                        .put("inode", m.inode)
                        .put("path", m.path)
                    outArr.put(o)
                    n++
                    if (n >= max) break
                }
                JSONObject().put("ok", true)
                    .put("filter", if (filter.isEmpty()) JSONObject.NULL else filter)
                    .put("count", n)
                    .put("list", outArr)
            }
            "modules" -> {
                val filter = req.optString("filter", "")
                val maps = ProcMaps.parseSelf()
                val byPath = LinkedHashMap<String, MutableList<ProcMaps.Mapping>>()
                for (m in maps) {
                    val path = m.path
                    if (path.isEmpty()) continue
                    if (filter.isNotEmpty() && !path.contains(filter)) continue
                    byPath.getOrPut(path) { ArrayList() }.add(m)
                }
                val outArr = JSONArray()
                for ((path, lst) in byPath) {
                    var base = Long.MAX_VALUE
                    var end = 0L
                    val perms = LinkedHashSet<String>()
                    for (m in lst) {
                        if (m.start < base) base = m.start
                        if (m.end > end) end = m.end
                        perms.add(m.perms)
                    }
                    outArr.put(JSONObject()
                        .put("path", path)
                        .put("base", toHex(base))
                        .put("end", toHex(end))
                        .put("perms", JSONArray(perms.toList()))
                    )
                }
                JSONObject().put("ok", true).put("count", outArr.length()).put("list", outArr)
            }
            "addr_info" -> {
                val addrAny = when {
                    req.has("addr") -> req.get("addr")
                    req.has("ptr") -> req.get("ptr")
                    else -> 0
                }
                val addr = parsePtr(addrAny)
                val m = ProcMaps.findEntryContaining(addr)
                if (m == null) {
                    JSONObject().put("ok", false).put("error", "not_mapped").put("addr", toHex(addr))
                } else {
                    JSONObject().put("ok", true)
                        .put("addr", toHex(addr))
                        .put("mapping", JSONObject()
                            .put("start", toHex(m.start))
                            .put("end", toHex(m.end))
                            .put("perms", m.perms)
                            .put("offset", toHex(m.offset))
                            .put("inode", m.inode)
                            .put("path", m.path)
                        )
                }
            }
            "dladdr" -> {
                val addrAny = when {
                    req.has("addr") -> req.get("addr")
                    req.has("ptr") -> req.get("ptr")
                    else -> 0
                }
                val addr = parsePtr(addrAny)
                val arr = NativeBridge.dladdr(addr)
                if (arr.isEmpty()) {
                    JSONObject().put("ok", false).put("error", "not_found").put("addr", toHex(addr))
                } else {
                    JSONObject().put("ok", true)
                        .put("addr", toHex(addr))
                        .put("fname", arr.getOrNull(0) ?: "")
                        .put("sname", arr.getOrNull(1) ?: "")
                        .put("fbase", arr.getOrNull(2) ?: "")
                        .put("saddr", arr.getOrNull(3) ?: "")
                }
            }
            "log_mark" -> {
                val tag = req.optString("tag", "mark")
                val note = req.optString("note", "")
                val obj = JSONObject().put("ts", System.currentTimeMillis()).put("kind", "mark").put("tag", tag)
                if (note.isNotEmpty()) obj.put("note", note)
                logWriter.logLine(obj.toString())
                JSONObject().put("ok", true)
            }

            "status" -> {
                JSONObject()
                    .put("ok", true)
                    .put("handle", toHex(session.handle))
                    .put("loadedPath", session.loadedPath ?: JSONObject.NULL)
            }
            "targets_list" -> {
                val arr = JSONArray()
                for (t in Targets.listTargets(appContext)) {
                    arr.put(JSONObject()
                        .put("name", t.name)
                        .put("path", t.path)
                        .put("size", t.size)
                        .put("sha256", t.sha256)
                    )
                }
                JSONObject().put("ok", true).put("targets", arr).put("current", Targets.getTargetPath(appContext))
            }
            "target_get" -> {
                JSONObject().put("ok", true).put("path", Targets.getTargetPath(appContext))
            }
            "target_set" -> {
                // NOTE: liblwplocal_proxy reads this file on first call (lazy dlopen).
                // If you change this after CurveHarness has already invoked native methods,
                // you should restart the harness process (or add a future proxy reset).
                val path = req.getString("path")
                Targets.setTargetPath(appContext, path)
                JSONObject().put("ok", true).put("path", Targets.getTargetPath(appContext))
            }
            "load_app_lib" -> {
                val name = req.getString("name")
                val nativeDir = appContext.applicationInfo.nativeLibraryDir
                val path = File(nativeDir, name).absolutePath
                val flags = req.optInt("flags", NativeBridge.RTLD_NOW or NativeBridge.RTLD_LOCAL)

                val preloadRaw = req.optString("preload", "")
                val preload = if (preloadRaw.isNotEmpty() && !preloadRaw.contains('/')) {
                    File(nativeDir, preloadRaw).absolutePath
                } else preloadRaw
                if (preload.isNotEmpty()) {
                    // NOTE:
                    // Some Android builds reject RTLD_GLOBAL in certain contexts.
                    // Preload is best-effort and does not strictly require GLOBAL here.
                    val h1 = NativeBridge.dlopen(preload, NativeBridge.RTLD_NOW)
                    if (h1 == 0L) {
                        return JSONObject().put("ok", false).put("error", "dlopen_preload_failed")
                            .put("message", NativeBridge.dlerrorString())
                    }
                }

                if (session.handle != 0L) {
                    try { NativeBridge.dlclose(session.handle) } catch (_: Exception) {}
                    session.handle = 0L
                    session.loadedPath = null
                }

                val h = NativeBridge.dlopen(path, flags)
                if (h == 0L) {
                    JSONObject().put("ok", false).put("error", "dlopen_failed").put("message", NativeBridge.dlerrorString())
                } else {
                    session.handle = h
                    session.loadedPath = path
                    JSONObject().put("ok", true).put("handle", toHex(h)).put("path", path)
                }
            }
            "load" -> {
                val path = req.getString("path")
                val flags = req.optInt("flags", NativeBridge.RTLD_NOW or NativeBridge.RTLD_LOCAL)

                val preload = req.optString("preload", "")
                if (preload.isNotEmpty()) {
                    val h1 = NativeBridge.dlopen(preload, NativeBridge.RTLD_NOW)
                    if (h1 == 0L) {
                        return JSONObject().put("ok", false).put("error", "dlopen_preload_failed")
                            .put("message", NativeBridge.dlerrorString())
                    }
                }

                if (session.handle != 0L) {
                    try { NativeBridge.dlclose(session.handle) } catch (_: Exception) {}
                    session.handle = 0L
                    session.loadedPath = null
                }

                val h = NativeBridge.dlopen(path, flags)
                if (h == 0L) {
                    JSONObject().put("ok", false).put("error", "dlopen_failed").put("message", NativeBridge.dlerrorString())
                } else {
                    session.handle = h
                    session.loadedPath = path
                    JSONObject().put("ok", true).put("handle", toHex(h)).put("path", path)
                }
            }
            "close" -> {
                if (session.handle != 0L) {
                    NativeBridge.dlclose(session.handle)
                    session.handle = 0L
                    session.loadedPath = null
                }
                JSONObject().put("ok", true)
            }
            "exports" -> {
                val path = req.optString("path", session.loadedPath ?: "")
                val filter = req.optString("filter", "").takeIf { it.isNotEmpty() }
                if (path.isEmpty()) {
                    JSONObject().put("ok", false).put("error", "no_path")
                } else {
                    val arr = NativeBridge.listExports(path, filter)
                    val ja = JSONArray()
                    for (sym in arr) ja.put(sym)
                    JSONObject().put("ok", true).put("path", path).put("symbols", ja)
                }
            }
            "dlsym" -> {
                if (session.handle == 0L) {
                    JSONObject().put("ok", false).put("error", "not_loaded")
                } else {
                    val name = req.getString("name")
                    val addr = NativeBridge.dlsym(session.handle, name)
                    if (addr == 0L) {
                        JSONObject().put("ok", false).put("error", "dlsym_failed").put("message", NativeBridge.dlerrorString())
                    } else {
                        JSONObject().put("ok", true).put("name", name).put("addr", toHex(addr))
                    }
                }
            }
            "resolve_many" -> {
                if (session.handle == 0L) {
                    JSONObject().put("ok", false).put("error", "not_loaded")
                } else {
                    val names = req.optJSONArray("names") ?: JSONArray()
                    val out = JSONArray()
                    for (i in 0 until names.length()) {
                        val name = names.optString(i, "")
                        if (name.isEmpty()) continue
                        val addr = NativeBridge.dlsym(session.handle, name)
                        out.put(JSONObject().put("name", name).put("addr", toHex(addr)))
                    }
                    JSONObject().put("ok", true).put("list", out)
                }
            }
            "resolve_exports" -> {
                if (session.handle == 0L) {
                    JSONObject().put("ok", false).put("error", "not_loaded")
                } else {
                    val path = req.optString("path", session.loadedPath ?: "")
                    val filter = req.optString("filter", "").takeIf { it.isNotEmpty() }
                    if (path.isEmpty()) {
                        JSONObject().put("ok", false).put("error", "no_path")
                    } else {
                        val syms = NativeBridge.listExports(path, filter)
                        val out = JSONArray()
                        for (sym in syms) {
                            val addr = NativeBridge.dlsym(session.handle, sym)
                            out.put(JSONObject().put("name", sym).put("addr", toHex(addr)))
                        }
                        JSONObject().put("ok", true).put("path", path).put("count", out.length()).put("list", out)
                    }
                }
            }
            "call_words" -> {
                val fnPtr = when {
                    req.has("addr") -> parsePtr(req.get("addr"))
                    req.has("name") -> {
                        if (session.handle == 0L) return JSONObject().put("ok", false).put("error", "not_loaded")
                        val name = req.getString("name")
                        val addr = NativeBridge.dlsym(session.handle, name)
                        if (addr == 0L) return JSONObject().put("ok", false).put("error", "dlsym_failed").put("message", NativeBridge.dlerrorString())
                        addr
                    }
                    else -> 0L
                }
                if (fnPtr == 0L) {
                    JSONObject().put("ok", false).put("error", "no_target")
                } else {
                    val argsJson = req.optJSONArray("args") ?: JSONArray()
                    val args = IntArray(argsJson.length())
                    for (i in 0 until argsJson.length()) {
                        args[i] = parseU32Word(argsJson.get(i))
                    }
                    val ret = NativeBridge.callWords(fnPtr, args)
                    val r0 = ret.getOrNull(0) ?: 0L
                    val r1 = ret.getOrNull(1) ?: 0L
                    JSONObject().put("ok", true)
                        .put("fn", toHex(fnPtr))
                        .put("r0", toHexU32(r0))
                        .put("r1", toHexU32(r1))
                }
            }
            "malloc" -> {
                val size = parseU32Word(req.get("size"))
                val ptr = NativeBridge.malloc(size)
                JSONObject().put("ok", true).put("ptr", toHex(ptr)).put("size", size)
            }
            "free" -> {
                val ptr = parsePtr(req.get("ptr"))
                NativeBridge.free(ptr)
                JSONObject().put("ok", true)
            }
            "write", "mem_write" -> {
                val ptrAny = when {
                    req.has("ptr") -> req.get("ptr")
                    req.has("addr") -> req.get("addr")
                    else -> 0
                }
                val ptr = parsePtr(ptrAny)
                val b64 = req.optString("data_b64", req.optString("data", ""))
                val data = Base64.decode(b64, Base64.DEFAULT)

                if (ptr < 0x10000L || data.isEmpty()) {
                    JSONObject()
                        .put("ok", false)
                        .put("error", "bad_ptr_or_data")
                        .put("ptr", toHex(ptr))
                        .put("size", data.size)
                } else {
                    val ok = NativeBridge.writeMem(ptr, data)
                    JSONObject().put("ok", ok).put("ptr", toHex(ptr)).put("size", data.size)
                }
            }

            "read", "mem_read" -> {
                val ptrAny = when {
                    req.has("ptr") -> req.get("ptr")
                    req.has("addr") -> req.get("addr")
                    else -> 0
                }
                val ptr = parsePtr(ptrAny)
                val sizeAny = when {
                    req.has("size") -> req.get("size")
                    req.has("len") -> req.get("len")
                    else -> 0
                }
                val size0 = parseU32Word(sizeAny)
                val max = 1024 * 1024
                val size = size0.coerceIn(0, max)

                if (ptr < 0x10000L || size <= 0) {
                    JSONObject()
                        .put("ok", false)
                        .put("error", "bad_ptr_or_size")
                        .put("ptr", toHex(ptr))
                        .put("size", size)
                } else {
                    val data = NativeBridge.readMem(ptr, size)
                    val b64 = Base64.encodeToString(data, Base64.NO_WRAP)
                    JSONObject().put("ok", true).put("data_b64", b64).put("size", data.size).put("ptr", toHex(ptr))
                }
            }

            "curve_init" -> {
                val id = curve().initIfNeeded()
                JSONObject().put("ok", true).put("id", id)
            }
            "curve_init_native" -> {
                // Backward-compatible alias (older PC tools call this name).
                // Use the same safe init path as curve_init.
                val id = curve().initIfNeeded()
                JSONObject().put("ok", true).put("id", id)
            }
            "curve_reset" -> {
                // Reset curve/renderer state so traces become comparable across runs.
                // Convert Map -> JSONObject so the response stays JSON-friendly.
                val out = curve().reset()
                JSONObject().put("ok", true).put("result", JSONObject(out))
            }
            "curve_ptrs" -> {
                JSONObject(curve().ptrs())
            }
            "curve_call" -> {
                var method = req.optString("method", "")
                val params = ArrayList<Any?>()

                val paramsArr = req.optJSONArray("params")
                if (paramsArr != null) {
                    for (i in 0 until paramsArr.length()) params.add(paramsArr.opt(i))
                } else {
                    val a = req.optJSONArray("args")
                    if (a != null) {
                        if (method.isEmpty() && a.length() > 0 && a.opt(0) is String) {
                            method = a.optString(0)
                            for (i in 1 until a.length()) params.add(a.opt(i))
                        } else {
                            for (i in 0 until a.length()) params.add(a.opt(i))
                        }
                    }
                }

                JSONObject(curve().call(method, params))
            }

                else -> JSONObject().put("ok", false).put("error", "unknown_cmd").put("cmd", cmd)
            }
        } catch (t: Throwable) {
            Log.e(TAG, "RPC exception", t)
            JSONObject().put("ok", false).put("error", "exception").put("message", t.toString())
        }
    }

    private fun sha256File(f: File): String {
        val md = MessageDigest.getInstance("SHA-256")
        FileInputStream(f).use { fis ->
            val buf = ByteArray(64 * 1024)
            while (true) {
                val r = fis.read(buf)
                if (r <= 0) break
                md.update(buf, 0, r)
            }
        }
        val dig = md.digest()
        val sb = StringBuilder(dig.size * 2)
        for (b in dig) sb.append(String.format("%02x", b))
        return sb.toString()
    }

    private fun readTextLines(path: String, maxLines: Int): List<String> {
        val out = ArrayList<String>(minOf(maxLines, 256))
        try {
            BufferedReader(InputStreamReader(File(path).inputStream(), Charsets.UTF_8)).use { br ->
                while (true) {
                    val ln = br.readLine() ?: break
                    out.add(ln)
                    if (out.size >= maxLines) break
                }
            }
        } catch (_: Exception) {
            // ignore
        }
        return out
    }

    private fun listThreads(max: Int): JSONArray {
        val dir = File("/proc/self/task")
        val tids = dir.listFiles()?.filter { it.isDirectory && it.name.all(Char::isDigit) }
            ?.sortedBy { it.name.toLong() } ?: emptyList()
        val out = JSONArray()
        var n = 0
        for (t in tids) {
            if (n >= max) break
            val tid = t.name.toLongOrNull() ?: continue
            val name = try {
                File(t, "comm").readText(Charsets.UTF_8).trim()
            } catch (_: Exception) {
                ""
            }
            out.put(JSONObject().put("tid", tid).put("name", name))
            n++
        }
        return out
    }

    private fun listFds(max: Int): JSONArray {
        val dir = File("/proc/self/fd")
        val fds = dir.listFiles()?.filter { it.name.all(Char::isDigit) }
            ?.sortedBy { it.name.toInt() } ?: emptyList()
        val out = JSONArray()
        var n = 0
        for (f in fds) {
            if (n >= max) break
            val fd = f.name.toIntOrNull() ?: continue
            val target = try {
                Os.readlink(f.absolutePath)
            } catch (_: Exception) {
                ""
            }
            out.put(JSONObject().put("fd", fd).put("target", target))
            n++
        }
        return out
    }

    private fun safeJson(raw: String): Any {
        return try {
            JSONObject(raw)
        } catch (_: Exception) {
            raw
        }
    }

    private fun jsonLine(kind: String, kv: Map<String, Any?>): String {
        val o = JSONObject().put("kind", kind)
        for ((k, v) in kv) {
            o.put(k, v)
        }
        return o.toString()
    }

    private fun parseU32Word(v: Any): Int {
        return when (v) {
            is Int -> v
            is Long -> v.toInt()
            is Double -> v.toInt()
            is String -> {
                val s = v.trim()
                val n = if (s.startsWith("0x") || s.startsWith("0X")) s.substring(2).toLong(16) else s.toLong()
                n.toInt()
            }
            else -> 0
        }
    }

    private fun parsePtr(v: Any): Long {
        return when (v) {
            is Long -> v
            is Int -> v.toLong()
            is Double -> v.toLong()
            is String -> {
                val s = v.trim()
                if (s.startsWith("0x") || s.startsWith("0X")) s.substring(2).toLong(16) else s.toLong()
            }
            else -> 0L
        }
    }

    private fun toHex(ptr: Long): String {
        val v = ptr and 0xFFFFFFFFL
        return "0x" + v.toString(16)
    }

    private fun toHexU32(v: Long): String {
        return "0x" + (v and 0xFFFFFFFFL).toString(16)
    }
}
