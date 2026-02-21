package com.sonymobile.experienceflow.renderer;

import android.content.res.AssetManager;

public abstract class CurveRenderer {
    /* access modifiers changed from: protected */
    public native synchronized void activate(int i);

    /* access modifiers changed from: protected */
    public native synchronized void deactivate(int i);

    /* access modifiers changed from: protected */
    public native synchronized int getSleepRecommendation(int i);

    /* access modifiers changed from: protected */
    public native synchronized int init(AssetManager assetManager);

    /* access modifiers changed from: protected */
    public native synchronized void render(int i, AssetManager assetManager);

    /* access modifiers changed from: protected */
    public native synchronized void requestColors(int i, AssetManager assetManager, int i2);

    /* access modifiers changed from: protected */
    public native synchronized void touch(int i, float f, float f2);

    /* access modifiers changed from: protected */
    public native synchronized void touchDown(int i, float f, float f2);

    /* access modifiers changed from: protected */
    public native synchronized void touchUp(int i, float f, float f2);

    /* access modifiers changed from: protected */
    public native synchronized void updateScreenLayout(int i, int i2, int i3, int i4, int i5, int i6, int i7);

    static {
        System.loadLibrary("lwplocal");
    }
}
