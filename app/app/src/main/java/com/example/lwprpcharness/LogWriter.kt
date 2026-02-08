package com.example.lwprpcharness

import android.util.Log
import java.io.File
import java.text.SimpleDateFormat
import java.util.Date
import java.util.Locale

class LogWriter(private val logsDir: File) {

    private val tag = "LwpRpcLog"
    private val file: File
    private val lock = Any()

    init {
        val ts = SimpleDateFormat("yyyyMMdd_HHmmss", Locale.US).format(Date())
        file = File(logsDir, "session_${ts}.jsonl")
    }

    fun getFile(): File = file

    fun logLine(line: String) {
        val l = line.trimEnd() + "\n"
        synchronized(lock) {
            try {
                file.appendText(l, Charsets.UTF_8)
            } catch (e: Exception) {
                Log.w(tag, "append failed", e)
            }
        }
        Log.i(tag, line)
    }
}
