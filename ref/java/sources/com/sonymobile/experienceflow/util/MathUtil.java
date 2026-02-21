package com.sonymobile.experienceflow.util;

import android.graphics.PointF;

public class MathUtil {
    public static final PointF scaleToFit(float srcW, float srcH, float dstW, float dstH) {
        float scale = Math.min(dstW / srcW, dstH / srcH);
        return new PointF(srcW * scale, srcH * scale);
    }

    public static final PointF scaleToMatch(float srcW, float srcH, float dstW, float dstH) {
        float scale = Math.max(dstW / srcW, dstH / srcH);
        return new PointF(srcW * scale, srcH * scale);
    }
}
