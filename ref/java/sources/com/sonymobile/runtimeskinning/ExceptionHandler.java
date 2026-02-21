package com.sonymobile.runtimeskinning;

import android.os.RemoteException;
import java.lang.Thread;

class ExceptionHandler implements Thread.UncaughtExceptionHandler {
    private Throwable mCause;

    ExceptionHandler() {
    }

    public void uncaughtException(Thread thread, Throwable cause) {
        this.mCause = cause;
    }

    /* access modifiers changed from: package-private */
    public void reThrow() throws RemoteException {
        RemoteException re;
        if (this.mCause != null) {
            if (this.mCause instanceof RemoteException) {
                re = (RemoteException) this.mCause;
            } else {
                re = new RemoteException();
                re.initCause(this.mCause);
            }
            throw re;
        }
    }
}
