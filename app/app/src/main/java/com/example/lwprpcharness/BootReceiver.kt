package com.example.lwprpcharness

import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.os.Build

/**
 * Starts the RPC harness service after boot / package replacement.
 *
 * The desktop tool talks to localhost:31337 forwarded via ADB.
 * If the service is not running, ADB will accept the connection but the device side closes immediately,
 * which looks like "no response from server" on the PC.
 */
class BootReceiver : BroadcastReceiver() {
    override fun onReceive(context: Context, intent: Intent?) {
        val action = intent?.action ?: return
        if (action != Intent.ACTION_BOOT_COMPLETED &&
            action != Intent.ACTION_MY_PACKAGE_REPLACED &&
            action != Intent.ACTION_PACKAGE_REPLACED) {
            return
        }

        val svc = Intent(context, WorkerService::class.java).apply {
            this.action = WorkerService.ACTION_START
        }

        try {
            if (Build.VERSION.SDK_INT >= 26) {
                context.startForegroundService(svc)
            } else {
                context.startService(svc)
            }
        } catch (_: Throwable) {
            // best-effort
        }
    }
}
