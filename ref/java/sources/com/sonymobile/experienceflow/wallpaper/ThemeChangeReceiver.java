package com.sonymobile.experienceflow.wallpaper;

import android.app.IntentService;
import android.app.WallpaperInfo;
import android.app.WallpaperManager;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import com.sonymobile.experienceflow2.R;
import com.sonymobile.runtimeskinning.RuntimeSkinningUtil;

public class ThemeChangeReceiver extends BroadcastReceiver {
    public static final boolean DEBUG = false;
    public static final String LOG_TAG = "ThemeChangeReceiver";

    public void onReceive(Context context, Intent intent) {
        WallpaperManager wallpaperMgr;
        WallpaperInfo wallpaperInfo;
        try {
            if (RuntimeSkinningUtil.isLiveWallpaperUsed(intent) && !RuntimeSkinningUtil.isInitialSetup(intent) && (wallpaperMgr = WallpaperManager.getInstance(context)) != null && (wallpaperInfo = wallpaperMgr.getWallpaperInfo()) != null && wallpaperInfo.getPackageName().contentEquals(context.getPackageName())) {
                context.startService(new Intent(context, ApplyAccentColorService.class));
            }
        } catch (IllegalArgumentException e) {
        }
    }

    protected static int getThemeWallpaperColor(Context context) {
        int preferencesColorIndex = context.getResources().getInteger(R.integer.config_wallpaperPaletteID);
        if (preferencesColorIndex >= ColorPicker.getDefaultLiveWallpaperIndex(context)) {
            context.getSharedPreferences(ExperienceFlowPreferencesActivity.SHARED_PREFS_NAME, 0).edit().putInt(ExperienceFlowPreferencesActivity.PREFS_KEY_COLOR, preferencesColorIndex).apply();
        } else {
            Log.w(LOG_TAG, "Theme wallpaper color is NOT valid: " + preferencesColorIndex);
        }
        return preferencesColorIndex;
    }

    public static final class ApplyAccentColorService extends IntentService {
        public ApplyAccentColorService() {
            super("applyAccentColorService");
        }

        /* access modifiers changed from: protected */
        public void onHandleIntent(Intent intent) {
            ThemeChangeReceiver.getThemeWallpaperColor(getApplicationContext());
        }
    }
}
