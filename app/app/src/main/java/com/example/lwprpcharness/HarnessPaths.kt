package com.example.lwprpcharness

import android.content.Context
import java.io.File

/**
 * 端末側ログの配置規約。
 *
 * - /sdcard/Android/data/<pkg>/files/lwprpcharness_logs/ に JSONL を出力
 * - 外部領域が使えない場合は内部 filesDir をフォールバック
 */
object HarnessPaths {

    // 既存ドキュメント互換: Android/data/<pkg>/files/logs/
    const val LOG_DIR_NAME = "logs"

    fun logsDir(context: Context): File {
        val base = context.getExternalFilesDir(null) ?: context.filesDir
        return File(base, LOG_DIR_NAME)
    }

    fun latestLogFile(logsDir: File): File? {
        val files = logsDir.listFiles() ?: return null
        return files
            .filter { it.isFile }
            .maxByOrNull { it.lastModified() }
    }
}
