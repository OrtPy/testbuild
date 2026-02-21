package com.sonymobile.experienceflow.renderer;

import android.opengl.GLSurfaceView;

public final class ProxyFramerateController extends FramerateControllerBase {
    CurveRendererImpl curveRenderer;

    public ProxyFramerateController(int maxFps, GLSurfaceView surfaceView, CurveRendererImpl curveRenderer2) {
        super(maxFps, surfaceView);
        this.curveRenderer = curveRenderer2;
    }

    /* access modifiers changed from: protected */
    public int getFrameDelay(long deltaTime) {
        return this.curveRenderer.getSleepRecommendation() - ((int) deltaTime);
    }
}
