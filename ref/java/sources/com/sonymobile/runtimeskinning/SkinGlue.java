package com.sonymobile.runtimeskinning;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.res.Resources;
import android.os.RemoteException;

interface SkinGlue {
    public static final SkinGlue DISABLED = new GlueStub();

    String getSkin(Context context, int i) throws RemoteException;

    boolean isApplicable(Context context);

    boolean isResourceOverlaid(Context context, Resources resources, int i, int i2) throws RemoteException;

    boolean isSkin(Context context, PackageInfo packageInfo, int i) throws RemoteException;

    boolean isSkinConfigurationChanged(Context context, int i) throws RemoteException;

    boolean isTrusted(Context context, PackageInfo packageInfo, int i) throws RemoteException;

    boolean isVerified(Context context, PackageInfo packageInfo, int i) throws RemoteException;

    int myUserId(Context context);

    boolean setSkin(Context context, PackageInfo packageInfo, int i) throws RemoteException;

    boolean supportsInstallableSkins(Context context);

    public static final class GlueStub implements SkinGlue {
        private GlueStub() {
        }

        public int myUserId(Context context) {
            return 0;
        }

        public boolean isApplicable(Context context) {
            return false;
        }

        public boolean isSkin(Context context, PackageInfo pinf, int userId) {
            return false;
        }

        public boolean isVerified(Context context, PackageInfo pinf, int userId) {
            return false;
        }

        public boolean isTrusted(Context context, PackageInfo pinf, int userId) throws RemoteException {
            return false;
        }

        public boolean isResourceOverlaid(Context context, Resources res, int referenceResId, int resId) {
            return false;
        }

        public boolean isSkinConfigurationChanged(Context context, int diff) {
            return false;
        }

        public boolean setSkin(Context context, PackageInfo pinf, int userId) {
            return false;
        }

        public String getSkin(Context context, int userId) {
            return null;
        }

        public boolean supportsInstallableSkins(Context context) {
            return false;
        }
    }
}
