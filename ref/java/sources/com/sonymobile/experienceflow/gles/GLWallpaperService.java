package com.sonymobile.experienceflow.gles;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.service.wallpaper.WallpaperService;
import android.view.SurfaceHolder;

public abstract class GLWallpaperService extends WallpaperService {

    public abstract class GLEngine extends WallpaperService.Engine {
        protected WallpaperGLSurfaceView mGLSurfaceView;
        private GLSurfaceView.Renderer mRenderer;

        public abstract WallpaperGLSurfaceView createGLSurfaceView();

        public GLEngine() {
            super(GLWallpaperService.this);
            setTouchEventsEnabled(true);
        }

        public void onCreate(SurfaceHolder surfaceHolder) {
            super.onCreate(surfaceHolder);
            this.mGLSurfaceView = createGLSurfaceView();
        }

        public void onVisibilityChanged(boolean visible) {
            super.onVisibilityChanged(visible);
            if (this.mGLSurfaceView != null && this.mRenderer != null) {
                if (visible) {
                    this.mGLSurfaceView.onResume();
                } else {
                    this.mGLSurfaceView.onPause();
                }
            }
        }

        public void onDestroy() {
            super.onDestroy();
            if (this.mGLSurfaceView != null) {
                this.mGLSurfaceView.onDestroy();
            }
        }

        /* access modifiers changed from: protected */
        public void setRenderer(GLSurfaceView.Renderer renderer) {
            this.mRenderer = renderer;
            if (this.mGLSurfaceView != null) {
                this.mGLSurfaceView.setRenderer(renderer);
                this.mGLSurfaceView.onResume();
            }
        }

        /* access modifiers changed from: protected */
        public GLSurfaceView.Renderer getRenderer() {
            return this.mRenderer;
        }

        public abstract class WallpaperGLSurfaceView extends GLSurfaceView {
            protected GLSurfaceView.Renderer mRenderer;

            public abstract GLSurfaceView.Renderer createRenderer(Context context, GLSurfaceView gLSurfaceView);

            public WallpaperGLSurfaceView(Context context) {
                super(context);
                setEGLContextClientVersion(2);
                setEGLConfigChooser(8, 8, 8, 0, 0, 0);
                getHolder().setFormat(3);
                setPreserveEGLContextOnPause(true);
                this.mRenderer = createRenderer(GLWallpaperService.this.getBaseContext(), this);
                setRenderer(this.mRenderer);
                setRenderMode(0);
            }

            public SurfaceHolder getHolder() {
                return GLEngine.this.getSurfaceHolder();
            }

            public void onDestroy() {
                super.onDetachedFromWindow();
            }
        }
    }
}
