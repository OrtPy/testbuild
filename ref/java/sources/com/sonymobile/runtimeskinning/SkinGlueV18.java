package com.sonymobile.runtimeskinning;

import android.app.AppGlobals;
import android.content.Context;
import android.content.pm.ActivityInfo;
import android.content.pm.IPackageManager;
import android.content.pm.PackageInfo;
import android.content.res.Resources;
import android.os.Build;
import android.os.RemoteException;
import android.os.UserHandle;
import android.text.TextUtils;
import android.util.TypedValue;
import java.lang.reflect.Field;
import java.lang.reflect.Method;

public class SkinGlueV18 implements SkinGlue {
    private Field mFieldConfigSkinPackage;
    private Field mFieldIsSkin;
    private Field mFieldIsVerifiedSkin;
    private Method mMethodGetRuntimeSkin;
    private Method mMethodSetRuntimeSkin;

    public boolean isApplicable(Context context) {
        return Build.VERSION.SDK_INT > 17 && init();
    }

    public boolean isSkin(Context context, PackageInfo pinf, int userId) {
        if (!init()) {
            return false;
        }
        return ((Boolean) ReflectionUtils.readField(this.mFieldIsSkin, pinf, Boolean.class)).booleanValue() && !TextUtils.isEmpty(pinf.packageName);
    }

    public boolean isVerified(Context context, PackageInfo pinf, int userId) {
        if (!init()) {
            return false;
        }
        return isSkin(context, pinf, userId) && ((Boolean) ReflectionUtils.readField(this.mFieldIsVerifiedSkin, pinf, Boolean.class)).booleanValue();
    }

    public boolean isTrusted(Context context, PackageInfo pinf, int userId) {
        boolean systemApp;
        boolean z = true;
        if (!init() || !isVerified(context, pinf, userId)) {
            return false;
        }
        if ((pinf.applicationInfo.flags & 1) != 0) {
            systemApp = true;
        } else {
            systemApp = false;
        }
        if (systemApp) {
            return true;
        }
        if (context.getPackageManager().checkSignatures(pinf.packageName, "android") != 0) {
            z = false;
        }
        return z;
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
        if (!init()) {
            return false;
        }
        ExceptionHandler eh = new ExceptionHandler();
        IPackageManager ipm = AppGlobals.getPackageManager();
        Method method = this.mMethodSetRuntimeSkin;
        Class cls = Boolean.class;
        Object[] objArr = new Object[2];
        objArr[0] = Integer.valueOf(userId);
        objArr[1] = pinf == null ? null : pinf.packageName;
        Boolean result = (Boolean) ReflectionUtils.invokeMethod(method, ipm, eh, cls, objArr);
        eh.reThrow();
        return result == null ? false : result.booleanValue();
    }

    public String getSkin(Context context, int userId) throws RemoteException {
        if (!init()) {
            return null;
        }
        ExceptionHandler eh = new ExceptionHandler();
        String str = (String) ReflectionUtils.invokeMethod(this.mMethodGetRuntimeSkin, AppGlobals.getPackageManager(), eh, String.class, Integer.valueOf(userId));
        eh.reThrow();
        return str;
    }

    public int myUserId(Context context) {
        return UserHandle.myUserId();
    }

    public boolean supportsInstallableSkins(Context context) {
        return true;
    }

    private synchronized boolean init() {
        boolean z = true;
        synchronized (this) {
            if (this.mFieldIsSkin == null) {
                this.mFieldIsSkin = ReflectionUtils.getField(PackageInfo.class, "isSkin", Boolean.TYPE);
            }
            if (this.mFieldIsVerifiedSkin == null) {
                this.mFieldIsVerifiedSkin = ReflectionUtils.getField(PackageInfo.class, "isVerifiedSkin", Boolean.TYPE);
            }
            if (this.mFieldConfigSkinPackage == null) {
                this.mFieldConfigSkinPackage = ReflectionUtils.getField(ActivityInfo.class, "CONFIG_SKIN_PACKAGE", Integer.TYPE);
            }
            if (this.mMethodGetRuntimeSkin == null) {
                this.mMethodGetRuntimeSkin = ReflectionUtils.getMethod(IPackageManager.class, "getRuntimeSkin", String.class, Integer.TYPE);
            }
            if (this.mMethodSetRuntimeSkin == null) {
                this.mMethodSetRuntimeSkin = ReflectionUtils.getMethod(IPackageManager.class, "setRuntimeSkin", Boolean.TYPE, Integer.TYPE, String.class);
            }
            if (this.mFieldIsSkin == null || this.mFieldIsVerifiedSkin == null || this.mFieldConfigSkinPackage == null || this.mMethodGetRuntimeSkin == null || this.mMethodSetRuntimeSkin == null) {
                z = false;
            }
        }
        return z;
    }
}
