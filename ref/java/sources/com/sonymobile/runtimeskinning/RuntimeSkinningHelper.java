package com.sonymobile.runtimeskinning;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.os.RemoteException;
import android.text.TextUtils;

public class RuntimeSkinningHelper {
    private static final SkinGlue[] IMPLEMENTATIONS = {new SkinGlueV18(), new SkinGlueV17(), new SkinGlueV16()};
    private SkinGlue mSkinGlue;

    public RuntimeSkinningHelper() {
    }

    RuntimeSkinningHelper(SkinGlue glue) {
        this.mSkinGlue = glue;
    }

    public boolean isSkin(Context context, PackageInfo skinPackage) throws RemoteException, NullPointerException {
        if (context == null || skinPackage == null) {
            throw new NullPointerException();
        }
        SkinGlue glue = getSkinGlue(context);
        return glue.isSkin(context, skinPackage, glue.myUserId(context));
    }

    public PackageInfo getCurrentSkin(Context context) throws RemoteException, NullPointerException {
        if (context == null) {
            throw new NullPointerException();
        }
        SkinGlue glue = getSkinGlue(context);
        String packageName = glue.getSkin(context, glue.myUserId(context));
        if (TextUtils.isEmpty(packageName)) {
            return null;
        }
        try {
            return context.getPackageManager().getPackageInfo(packageName, 0);
        } catch (PackageManager.NameNotFoundException e) {
            return null;
        }
    }

    public boolean isSkinConfigurationChanged(Context context, int diff) throws RemoteException {
        if (context != null) {
            return getSkinGlue(context).isSkinConfigurationChanged(context, diff);
        }
        throw new NullPointerException();
    }

    /* access modifiers changed from: package-private */
    public final synchronized SkinGlue getSkinGlue(Context context) {
        SkinGlue skinGlue;
        if (this.mSkinGlue == null) {
            SkinGlue[] arr$ = IMPLEMENTATIONS;
            int len$ = arr$.length;
            int i$ = 0;
            while (true) {
                if (i$ >= len$) {
                    break;
                }
                SkinGlue glue = arr$[i$];
                if (glue.isApplicable(context)) {
                    this.mSkinGlue = glue;
                    break;
                }
                i$++;
            }
        }
        if (this.mSkinGlue != null) {
            skinGlue = this.mSkinGlue;
        } else {
            skinGlue = SkinGlue.DISABLED;
        }
        return skinGlue;
    }
}
