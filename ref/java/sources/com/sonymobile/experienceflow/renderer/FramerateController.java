package com.sonymobile.experienceflow.renderer;

import android.opengl.GLSurfaceView;

public interface FramerateController {
    void continueFrame();

    boolean getCapFrameRate();

    int getMaxFps();

    long onFrame();

    void setCapFrameRate(boolean z);

    void setMaxFps(int i);

    void setSurfaceView(GLSurfaceView gLSurfaceView);

    void startRendering();

    void stopRendering();
}
