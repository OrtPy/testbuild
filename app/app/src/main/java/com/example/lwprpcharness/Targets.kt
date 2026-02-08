package com.example.lwprpcharness

import android.content.Context
import android.util.Log
import java.io.File
import java.io.FileOutputStream
import java.io.InputStream
import java.security.MessageDigest

/**
 * Manages "target" native libraries for analysis.
 *
 * We intentionally keep this simple and deterministic:
 * - Extract asset originals to internal storage so native code (proxy) can dlopen() them by absolute path.
 * - Store the currently selected real library path in filesDir/lwplocal_real_path.txt (read by lwplocal_proxy).
 */
object Targets {
    private const val TAG = "Targets"

    private const val ASSET_ORIG95 = "native/armeabi-v7a/liblwplocal.so"
    private const val ASSET_GNUSTL  = "native/armeabi-v7a/libgnustl_shared.so"

    private const val DIR_NAME = "targets"
    private const val FILE_REAL_PATH = "lwplocal_real_path.txt"

    fun targetsDir(ctx: Context): File = File(ctx.filesDir, DIR_NAME)
    fun realPathFile(ctx: Context): File = File(ctx.filesDir, FILE_REAL_PATH)

    data class TargetInfo(
        val name: String,
        val path: String,
        val size: Long,
        val sha256: String
    )

    /** Ensure assets are extracted (idempotent). */
    @Synchronized
    fun ensurePrepared(ctx: Context) {
        val dir = targetsDir(ctx)
        if (!dir.exists()) dir.mkdirs()

        // Extract orig95 lib from assets
        val outOrig = File(dir, "orig95_liblwplocal.so")
        extractAssetIfDifferent(ctx, ASSET_ORIG95, outOrig)

        // Extract gnustl from assets as well (optional, but useful for triage)
        val outGn = File(dir, "orig95_libgnustl_shared.so")
        extractAssetIfDifferent(ctx, ASSET_GNUSTL, outGn)

        // Default target: orig95 (only if not already set)
        val realFile = realPathFile(ctx)
        if (!realFile.exists() || realFile.readTextSafe().isBlank()) {
            setTargetPath(ctx, outOrig.absolutePath)
        }
    }

    fun listTargets(ctx: Context): List<TargetInfo> {
        ensurePrepared(ctx)

        val out = ArrayList<TargetInfo>()

        // Extracted targets
        val dir = targetsDir(ctx)
        (dir.listFiles() ?: emptyArray()).filter { it.isFile }.forEach { f ->
            out.add(TargetInfo(
                name = f.name,
                path = f.absolutePath,
                size = f.length(),
                sha256 = sha256File(f)
            ))
        }

        // Also expose current app native lib (typically "mine" build)
        try {
            val nativeDir = File(ctx.applicationInfo.nativeLibraryDir)
            val appLib = File(nativeDir, "liblwplocal.so")
            if (appLib.exists()) {
                out.add(TargetInfo(
                    name = "app_native_liblwplocal.so",
                    path = appLib.absolutePath,
                    size = appLib.length(),
                    sha256 = sha256File(appLib)
                ))
            }
        } catch (_: Throwable) {}

        // Sort for stable output
        return out.sortedWith(compareBy({ it.name }, { it.path }))
    }

    fun getTargetPath(ctx: Context): String {
        ensurePrepared(ctx)
        return realPathFile(ctx).readTextSafe().trim()
    }

    fun setTargetPath(ctx: Context, absPath: String) {
        ensurePrepared(ctx)
        val f = realPathFile(ctx)
        try {
            f.writeText(absPath.trim() + "\n")
        } catch (t: Throwable) {
            Log.e(TAG, "setTargetPath failed: ${t.message}", t)
            throw t
        }
    }

    private fun extractAssetIfDifferent(ctx: Context, assetName: String, outFile: File) {
        try {
            ctx.assets.open(assetName).use { ins ->
                val shaIn = sha256Stream(ins)
                val need = if (!outFile.exists()) true else {
                    val shaOut = sha256File(outFile)
                    shaOut != shaIn
                }
                if (!need) return
            }
            // Re-open for actual copy (we consumed stream for hash)
            ctx.assets.open(assetName).use { ins ->
                FileOutputStream(outFile).use { fos ->
                    copy(ins, fos)
                }
            }
            Log.i(TAG, "asset extracted: $assetName -> ${outFile.absolutePath} (${outFile.length()} bytes)")
        } catch (t: Throwable) {
            Log.e(TAG, "extractAssetIfDifferent failed: $assetName : ${t.message}", t)
            // Best-effort: do not crash the harness on devices with weird asset managers.
        }
    }

    private fun copy(ins: InputStream, fos: FileOutputStream) {
        val buf = ByteArray(128 * 1024)
        while (true) {
            val r = ins.read(buf)
            if (r <= 0) break
            fos.write(buf, 0, r)
        }
        fos.flush()
    }

    private fun sha256Stream(ins: InputStream): String {
        val md = MessageDigest.getInstance("SHA-256")
        val buf = ByteArray(64 * 1024)
        while (true) {
            val r = ins.read(buf)
            if (r <= 0) break
            md.update(buf, 0, r)
        }
        return md.digest().joinToString("") { "%02x".format(it) }
    }

    private fun sha256File(f: File): String {
        val md = MessageDigest.getInstance("SHA-256")
        f.inputStream().use { ins ->
            val buf = ByteArray(64 * 1024)
            while (true) {
                val r = ins.read(buf)
                if (r <= 0) break
                md.update(buf, 0, r)
            }
        }
        return md.digest().joinToString("") { "%02x".format(it) }
    }

    private fun File.readTextSafe(): String {
        return try { this.readText() } catch (_: Throwable) { "" }
    }
}
