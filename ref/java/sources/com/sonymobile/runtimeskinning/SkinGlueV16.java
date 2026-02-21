package com.sonymobile.runtimeskinning;

import android.app.ActivityManagerNative;
import android.app.IActivityManager;
import android.content.Context;
import android.content.pm.ActivityInfo;
import android.content.pm.PackageInfo;
import android.content.res.Configuration;
import android.content.res.Resources;
import android.os.Build;
import android.os.RemoteException;
import android.text.TextUtils;
import android.util.TypedValue;
import java.lang.reflect.Field;

class SkinGlueV16 implements SkinGlue {
    private Field mFieldConfigSkinPackage;
    private Field mFieldIsSkin;
    private Field mFieldOverlayTarget;
    private Field mFieldSkinPackage;

    SkinGlueV16() {
    }

    public int myUserId(Context context) {
        return 0;
    }

    public boolean isApplicable(Context context) {
        return Build.VERSION.SDK_INT > 15 && init();
    }

    public boolean isSkin(Context context, PackageInfo pinf, int userId) {
        if (!init()) {
            return false;
        }
        return ((Boolean) ReflectionUtils.readField(this.mFieldIsSkin, pinf, Boolean.class)).booleanValue() && Constants.UXP_PACKAGE_NAME.equals((String) ReflectionUtils.readField(this.mFieldOverlayTarget, pinf, String.class)) && !TextUtils.isEmpty(pinf.packageName);
    }

    public boolean isVerified(Context context, PackageInfo pinf, int userId) {
        return isSkin(context, pinf, userId);
    }

    public boolean isTrusted(Context context, PackageInfo pinf, int userId) {
        return isSkin(context, pinf, userId);
    }

    public boolean isResourceOverlaid(Context context, Resources res, int referenceResId, int resId) {
        try {
            TypedValue tv = new TypedValue();
            res.getValue(referenceResId, tv, true);
            int cookie = tv.assetCookie;
            res.getValue(resId, tv, true);
            if (tv.assetCookie != cookie) {
                return true;
            }
            return false;
        } catch (Resources.NotFoundException e) {
            return false;
        }
    }

    public boolean isSkinConfigurationChanged(Context context, int diff) throws RemoteException {
        Integer flag = (Integer) ReflectionUtils.readField(this.mFieldConfigSkinPackage, (Object) null, Integer.class);
        if (flag != null && flag.intValue() != 0) {
            return (flag.intValue() & diff) == flag.intValue();
        }
        throw new RemoteException();
    }

    public boolean setSkin(Context context, PackageInfo pinf, int userId) throws RemoteException {
        IActivityManager am;
        Configuration cfg;
        if (!init() || (am = ActivityManagerNative.getDefault()) == null || (cfg = am.getConfiguration()) == null) {
            return false;
        }
        if (!ReflectionUtils.setField(this.mFieldSkinPackage, cfg, pinf == null ? null : pinf.packageName)) {
            return false;
        }
        am.updateConfiguration(cfg);
        return true;
    }

    public String getSkin(Context context, int userId) throws RemoteException {
        Configuration cfg;
        if (init() && (cfg = ActivityManagerNative.getDefault().getConfiguration()) != null) {
            return (String) ReflectionUtils.readField(this.mFieldSkinPackage, cfg, String.class);
        }
        return null;
    }

    public boolean supportsInstallableSkins(Context context) {
        return false;
    }

    private synchronized boolean init() {
        if (this.mFieldIsSkin == null) {
            this.mFieldIsSkin = ReflectionUtils.getField(PackageInfo.class, "isSkin", Boolean.TYPE);
        }
        if (this.mFieldOverlayTarget == null) {
            this.mFieldOverlayTarget = ReflectionUtils.getField(PackageInfo.class, "overlayTarget", String.class);
        }
        if (this.mFieldSkinPackage == null) {
            this.mFieldSkinPackage = ReflectionUtils.getField(Configuration.class, "skinPackage", String.class);
        }
        if (this.mFieldConfigSkinPackage == null) {
            this.mFieldConfigSkinPackage = ReflectionUtils.getField(ActivityInfo.class, "CONFIG_SKIN_PACKAGE", Integer.TYPE);
        }
        return (this.mFieldIsSkin == null || this.mFieldOverlayTarget == null || this.mFieldSkinPackage == null || this.mFieldConfigSkinPackage == null) ? false : true;
    }
}
