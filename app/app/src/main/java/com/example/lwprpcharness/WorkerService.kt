package com.example.lwprpcharness

import android.app.Notification
import android.app.NotificationChannel
import android.app.NotificationManager
import android.app.Service
import android.content.Context
import android.content.Intent
import android.os.Build
import android.os.IBinder
import android.util.Log
import androidx.core.app.NotificationCompat

class WorkerService : Service() {

    companion object {
        const val ACTION_START = "com.example.lwprpcharness.action.START"
        const val ACTION_STOP = "com.example.lwprpcharness.action.STOP"

        private const val NOTIF_CHANNEL_ID = "lwprpcharness"
        private const val NOTIF_CHANNEL_NAME = "LWP RPC Harness"
        private const val NOTIF_ID = 31337

        private const val TAG = "WorkerService"
    }

    private var started = false
    private var rpcServer: RpcServer? = null
    private var logWriter: LogWriter? = null
    private val session: NativeSession = NativeSession()

    override fun onBind(intent: Intent?): IBinder? = null

    override fun onCreate() {
        super.onCreate()
        ensureForeground()
    }

    override fun onStartCommand(intent: Intent?, flags: Int, startId: Int): Int {
        val action = intent?.action ?: ACTION_START
        return when (action) {
            ACTION_STOP -> {
                stopNow("ACTION_STOP")
                START_NOT_STICKY
            }
            else -> {
                ensureForeground()
                ensureStarted()
                // Keep it running; this is a harness and should survive process churn.
                START_STICKY
            }
        }
    }

    override fun onDestroy() {
        stopNow("onDestroy")
        super.onDestroy()
    }

    private fun ensureForeground() {
        try {
            val nm = getSystemService(Context.NOTIFICATION_SERVICE) as NotificationManager

            if (Build.VERSION.SDK_INT >= 26) {
                val ch = NotificationChannel(
                    NOTIF_CHANNEL_ID,
                    NOTIF_CHANNEL_NAME,
                    NotificationManager.IMPORTANCE_MIN
                )
                ch.setShowBadge(false)
                nm.createNotificationChannel(ch)
            }

            val notif: Notification = NotificationCompat.Builder(this, NOTIF_CHANNEL_ID)
                .setSmallIcon(android.R.drawable.stat_notify_sync)
                .setContentTitle("LWP RPC Harness")
                .setContentText("RPC server is running (tcp:31337)")
                .setOngoing(true)
                .setCategory(NotificationCompat.CATEGORY_SERVICE)
                .setPriority(NotificationCompat.PRIORITY_MIN)
                .build()

            // MUST be called quickly after startForegroundService on Android O+.
            startForeground(NOTIF_ID, notif)
        } catch (t: Throwable) {
            Log.e(TAG, "ensureForeground failed", t)
            // If foreground fails, we still try to start (useful on very old devices).
        }
    }

    @Synchronized
    private fun ensureStarted() {
        if (started) return
        started = true

        try {
            // Prepare target libraries (extract asset originals and set default target path)
            Targets.ensurePrepared(applicationContext)

            val logsDir = HarnessPaths.logsDir(applicationContext)
            if (!logsDir.exists()) logsDir.mkdirs()

            val lw = LogWriter(logsDir)
            logWriter = lw

            rpcServer = RpcServer(
                31337,
                lw,
                session,
                applicationContext
            ).also { it.start() }

            Log.i(TAG, "RPC server started")
        } catch (t: Throwable) {
            Log.e(TAG, "Failed to start RPC server", t)
        }
    }

    @Synchronized
    private fun stopNow(reason: String) {
        try {
            rpcServer?.stop()
            rpcServer = null
        } catch (t: Throwable) {
            Log.e(TAG, "stopNow: rpc stop failed", t)
        }

        logWriter = null

        started = false

        try {
            // minSdk=21 のため stopForeground(boolean) を使用
            @Suppress("DEPRECATION")
            stopForeground(true)
        } catch (_: Throwable) {
        }

        Log.i(TAG, "WorkerService stopped ($reason)")
    }
}
