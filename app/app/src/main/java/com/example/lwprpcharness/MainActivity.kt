package com.example.lwprpcharness

import android.content.ClipData
import android.content.ClipboardManager
import android.content.Context
import android.content.Intent
import android.os.Build
import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import java.net.InetSocketAddress
import java.net.Socket

class MainActivity : AppCompatActivity() {

    private fun startHarnessService() {
        val i = Intent(this, WorkerService::class.java).setAction(WorkerService.ACTION_START)
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            startForegroundService(i)
        } else {
            startService(i)
        }
    }

    private fun stopHarnessService() {
        stopService(Intent(this, WorkerService::class.java))
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val txt = findViewById<TextView>(R.id.status)
        val btnStart = findViewById<Button>(R.id.btnStart)
        val btnStop = findViewById<Button>(R.id.btnStop)
        val btnCopy = findViewById<Button>(R.id.btnCopyForward)
        val btnOpenLogDir = findViewById<Button>(R.id.btnOpenLogDir)
        val txtLogPath = findViewById<TextView>(R.id.logPath)

        fun setStatus(s: String) {
            runOnUiThread { txt.text = s }
        }

        // Start on launch (so you can immediately ADB-forward and use the PC tool)
        startHarnessService()

        btnStart.setOnClickListener {
            startHarnessService()
        }

        btnStop.setOnClickListener {
            stopHarnessService()
        }

        val logsDir = HarnessPaths.logsDir(this)
        txtLogPath.text = "Log: ${logsDir.absolutePath}"

        btnCopy.setOnClickListener {
            val cm = getSystemService(Context.CLIPBOARD_SERVICE) as ClipboardManager
            val clip = ClipData.newPlainText("rpc", "adb forward tcp:31337 tcp:31337")
            cm.setPrimaryClip(clip)
            setStatus("Copied: adb forward tcp:31337 tcp:31337")
        }

        btnOpenLogDir.setOnClickListener {
            // Android 11+ ではアプリ専用外部領域をファイルマネージャで直接開けない端末もあるため、
            // まずは「ログの場所 / adb pull コマンド」をクリップボードに出しておく。
            try {
                val latest = HarnessPaths.latestLogFile(logsDir)
                val msg = if (latest != null) {
                    val pkg = packageName
                    val adbPull = "adb pull \"/sdcard/Android/data/$pkg/files/${HarnessPaths.LOG_DIR_NAME}/${latest.name}\" ."
                    "Latest log: ${latest.absolutePath}\n$adbPull"
                } else {
                    "Log dir: ${logsDir.absolutePath}"
                }

                val cm = getSystemService(Context.CLIPBOARD_SERVICE) as ClipboardManager
                cm.setPrimaryClip(ClipData.newPlainText("log", msg))
                setStatus("Copied log path / adb pull command")
            } catch (t: Throwable) {
                setStatus("Open log failed: ${t.javaClass.simpleName}: ${t.message}")
            }
        }

        // Simple local probe to help confirm the service is listening
        Thread {
            try {
                Socket().use { s ->
                    s.connect(InetSocketAddress("127.0.0.1", 31337), 700)
                }
                setStatus("RPC server seems to be listening on 127.0.0.1:31337")
            } catch (t: Throwable) {
                setStatus("RPC server not responding yet (open the app and tap START).\n${t.javaClass.simpleName}: ${t.message}")
            }
        }.start()
    }
}
