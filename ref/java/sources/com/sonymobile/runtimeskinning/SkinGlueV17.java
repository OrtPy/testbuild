package com.sonymobile.runtimeskinning;

import android.app.ActivityManagerNative;
import android.app.AppGlobals;
import android.app.IActivityManager;
import android.content.Context;
import android.content.pm.ActivityInfo;
import android.content.pm.IPackageManager;
import android.content.pm.PackageInfo;
import android.content.res.Configuration;
import android.content.res.Resources;
import android.os.Build;
import android.os.RemoteException;
import android.os.UserHandle;
import android.text.TextUtils;
import android.util.TypedValue;
import java.lang.reflect.Field;
import java.lang.reflect.Method;

class SkinGlueV17 implements SkinGlue {
    private Field mFieldConfigSkinPackage;
    private Field mFieldIsSkin;
    private Field mFieldOverlayTarget;
    private Field mFieldSkinPackageSeq;
    private Method mMethodGetRuntimeSkin;
    private Method mMethodSetRuntimeSkin;

    SkinGlueV17() {
    }

    public int myUserId(Context context) {
        return UserHandle.myUserId();
    }

    public boolean isApplicable(Context context) {
        return Build.VERSION.SDK_INT > 16 && init();
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
        IActivityManager iam;
        Configuration cfg;
        if (!init()) {
            return false;
        }
        IPackageManager ipm = AppGlobals.getPackageManager();
        Method method = this.mMethodSetRuntimeSkin;
        Class cls = Boolean.class;
        Object[] objArr = new Object[3];
        objArr[0] = Constants.UXP_PACKAGE_NAME;
        objArr[1] = pinf == null ? null : pinf.packageName;
        objArr[2] = Integer.valueOf(userId);
        if (!((Boolean) ReflectionUtils.invokeMethod(method, ipm, cls, objArr)).booleanValue() || (cfg = iam.getConfiguration()) == null) {
            return false;
        }
        if (!ReflectionUtils.setField(this.mFieldSkinPackageSeq, cfg, Integer.valueOf(((Integer) ReflectionUtils.readField(this.mFieldSkinPackageSeq, cfg, Integer.class)).intValue() + 1))) {
            return false;
        }
        (iam = ActivityManagerNative.getDefault()).updateConfiguration(cfg);
        return true;
    }

    public String getSkin(Context context, int userId) {
        if (!init()) {
            return null;
        }
        return (String) ReflectionUtils.invokeMethod(this.mMethodGetRuntimeSkin, AppGlobals.getPackageManager(), String.class, Constants.UXP_PACKAGE_NAME, Integer.valueOf(userId));
    }

    public boolean supportsInstallableSkins(Context context) {
        return false;
    }

    private synchronized boolean init() {
        boolean z = true;
        synchronized (this) {
            if (this.mFieldIsSkin == null) {
                this.mFieldIsSkin = ReflectionUtils.getField(PackageInfo.class, "isSkin", Boolean.TYPE);
            }
            if (this.mFieldOverlayTarget == null) {
                this.mFieldOverlayTarget = ReflectionUtils.getField(PackageInfo.class, "overlayTarget", String.class);
            }
            if (this.mFieldSkinPackageSeq == null) {
                this.mFieldSkinPackageSeq = ReflectionUtils.getField(Configuration.class, "skinPackageSeq", Integer.TYPE);
            }
            if (this.mFieldConfigSkinPackage == null) {
                this.mFieldConfigSkinPackage = ReflectionUtils.getField(ActivityInfo.class, "CONFIG_SKIN_PACKAGE", Integer.TYPE);
            }
            if (this.mMethodGetRuntimeSkin == null) {
                this.mMethodGetRuntimeSkin = ReflectionUtils.getMethod(IPackageManager.class, "getRuntimeSkin", String.class, String.class, Integer.TYPE);
            }
            if (this.mMethodSetRuntimeSkin == null) {
                this.mMethodSetRuntimeSkin = ReflectionUtils.getMethod(IPackageManager.class, "setRuntimeSkin", Boolean.TYPE, String.class, String.class, Integer.TYPE);
            }
            if (this.mFieldIsSkin == null || this.mFieldOverlayTarget == null || this.mFieldSkinPackageSeq == null || this.mFieldConfigSkinPackage == null || this.mMethodGetRuntimeSkin == null || this.mMethodSetRuntimeSkin == null) {
                z = false;
            }
        }
        return z;
    }
}
