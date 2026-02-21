package com.sonymobile.experienceflow.wallpaper;

import android.app.IntentService;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

public class MasterResetReceiver extends BroadcastReceiver {
    private static final String ACTION_MASTERRESET = "com.sonyericsson.settings.MASTERRESET";
    public static final boolean DEBUG = false;
    public static final String LOG_TAG = "MasterResetReceiver";

    public void onReceive(Context context, Intent intent) {
        if (ACTION_MASTERRESET.equals(intent.getAction())) {
            context.startService(new Intent(context, ResetPreferencesService.class));
        }
    }

    public static final class ResetPreferencesService extends IntentService {
        public ResetPreferencesService() {
            super("resetPrefsService");
        }

        /* access modifiers changed from: protected */
        public void onHandleIntent(Intent intent) {
            getSharedPreferences(ExperienceFlowPreferencesActivity.SHARED_PREFS_NAME, 0).edit().clear().apply();
        }
    }
}
