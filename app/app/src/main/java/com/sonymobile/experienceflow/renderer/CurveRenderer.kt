package com.sonymobile.experienceflow.renderer

import android.content.res.AssetManager

/**
 * Minimal stub matching the original Sony package/class so that ART can bind the
 * existing exported JNI symbols in liblwplocal.so.
 *
 * Signatures are taken from the decompiled Xperia live wallpaper app.
 */
abstract class CurveRenderer {

    protected external fun init(assetManager: AssetManager): Int
    protected external fun activate(i: Int)
    protected external fun deactivate(i: Int)
    protected external fun requestColors(i: Int, assetManager: AssetManager, i2: Int)
    // Original Sony Java signature (Xperia Live Wallpaper 3.1.A.0.1):
    //   updateScreenLayout(int id, int x, int y, int w, int h, int sw, int sh)
    protected external fun updateScreenLayout(i: Int, i2: Int, i3: Int, i4: Int, i5: Int, i6: Int, i7: Int)
    protected external fun render(i: Int, assetManager: AssetManager)
    protected external fun touchDown(i: Int, f: Float, f2: Float)
    protected external fun touch(i: Int, f: Float, f2: Float)
    protected external fun touchUp(i: Int, f: Float, f2: Float)
    protected external fun getSleepRecommendation(i: Int): Int
}
