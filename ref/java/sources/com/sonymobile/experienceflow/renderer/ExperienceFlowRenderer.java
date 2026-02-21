package com.sonymobile.experienceflow.renderer;

import android.content.Context;
import android.content.SharedPreferences;
import android.graphics.Point;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.view.WindowManager;
import com.sonymobile.experienceflow.renderer.CurveRendererImpl;
import com.sonymobile.experienceflow.wallpaper.ColorPicker;
import com.sonymobile.experienceflow.wallpaper.ExperienceFlowPreferencesActivity;
import com.sonymobile.experienceflow.wallpaper.SwipeData;
import java.util.StringTokenizer;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class ExperienceFlowRenderer implements GLSurfaceView.Renderer {
    float ax;
    float ay;
    protected CurveRendererImpl curveRenderer;
    boolean doReset = false;
    int[] location = new int[2];
    /* access modifiers changed from: private */
    public final Context mContext;
    private FramerateControllerBase mFramerateController;
    private int mHeight;
    private GLSurfaceView mSurfaceView;
    private int mWidth;

    /* access modifiers changed from: private */
    public void updateColor(SharedPreferences sharedPreferences) {
        this.curveRenderer.requestColors(this.mContext.getAssets(), sharedPreferences.getInt(ExperienceFlowPreferencesActivity.PREFS_KEY_COLOR, ColorPicker.getDefaultLiveWallpaperIndex(this.mContext)));
    }

    public ExperienceFlowRenderer(Context context, GLSurfaceView surfaceView) {
        this.mContext = context;
        this.mSurfaceView = surfaceView;
        this.curveRenderer = new CurveRendererImpl(this.mContext.getAssets());
        this.curveRenderer.activate();
        context.getSharedPreferences(ExperienceFlowPreferencesActivity.SHARED_PREFS_NAME, 0).registerOnSharedPreferenceChangeListener(new SharedPreferences.OnSharedPreferenceChangeListener() {
            public void onSharedPreferenceChanged(SharedPreferences sharedPreferences, String key) {
                ExperienceFlowRenderer.this.updateColor(sharedPreferences);
            }
        });
        getFramerateController().addRenderModeListener(new RenderModeListener() {
            public void onStopRendering() {
                ExperienceFlowRenderer.this.doReset = true;
            }

            public void onStartRendering() {
                ExperienceFlowRenderer.this.doReset = true;
                ExperienceFlowRenderer.this.updateColor(ExperienceFlowRenderer.this.mContext.getSharedPreferences(ExperienceFlowPreferencesActivity.SHARED_PREFS_NAME, 0));
            }
        });
    }

    public void onSurfaceCreated(GL10 glUnused, EGLConfig config) {
        this.curveRenderer.setOnRenderListener(new CurveRendererImpl.RenderListener() {
            public void pleaseRender() {
                ExperienceFlowRenderer.this.getFramerateController().continueFrame();
            }
        });
        this.doReset = true;
    }

    public void onSurfaceChanged(GL10 glUnused, int width, int height) {
        this.mWidth = width;
        this.mHeight = height;
        this.doReset = true;
    }

    public void onDrawFrame(GL10 glUnused) {
        getFramerateController().onFrame();
        if (this.doReset) {
            this.curveRenderer.deactivate();
            this.curveRenderer.activate();
            this.doReset = false;
        }
        Point outSize = new Point();
        WindowManager systemService = (WindowManager) this.mContext.getSystemService("window");
        if (systemService.getDefaultDisplay() != null) {
            systemService.getDefaultDisplay().getRealSize(outSize);
            this.mSurfaceView.getLocationOnScreen(this.location);
            this.curveRenderer.updateScreenLayout(this.location[0], this.location[1], this.mWidth, this.mHeight, outSize.x, outSize.y);
        }
        this.curveRenderer.render(this.mContext.getAssets());
    }

    public void pushTouchUp() {
        touchUp(this.ax, this.ay);
    }

    public Capabilities getCapabilities() {
        Capabilities c = new Capabilities();
        StringTokenizer st = new StringTokenizer(GLES20.glGetString(7939));
        int length = st.countTokens();
        String[] extArray = new String[length];
        for (int i = 0; i < length; i++) {
            extArray[i] = st.nextToken();
        }
        c.setExtensions(extArray);
        return c;
    }

    public void touchDown(float x, float y) {
        this.curveRenderer.touchDown(x, y);
        this.ax = x;
        this.ay = y;
        getFramerateController().continueFrame();
    }

    public void touch(float x, float y) {
        this.curveRenderer.touch(x, y);
        this.ax = x;
        this.ay = y;
        getFramerateController().continueFrame();
    }

    public void touchUp(float x, float y) {
        this.curveRenderer.touchUp(x, y);
        this.ax = x;
        this.ay = y;
        getFramerateController().continueFrame();
    }

    public void poke() {
        getFramerateController().continueFrame();
    }

    public void handleSwipe(SwipeData dc) {
        getFramerateController().continueFrame();
    }

    public void accelerate(float value) {
        getFramerateController().continueFrame();
    }

    public FramerateControllerBase getFramerateController() {
        if (this.mFramerateController == null) {
            this.mFramerateController = new ProxyFramerateController(30, this.mSurfaceView, this.curveRenderer);
        }
        return this.mFramerateController;
    }
}
