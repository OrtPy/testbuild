package com.sonymobile.experienceflow.renderer;

import android.opengl.GLSurfaceView;
import android.os.Handler;
import android.os.Looper;
import android.os.SystemClock;
import java.util.ArrayList;
import java.util.concurrent.atomic.AtomicBoolean;

public abstract class FramerateControllerBase implements FramerateController {
    private static final long INITIAL_MAX_TIME_BETWEEN_RENDER_REQUESTS = 10;
    private static final long RENDER_DELAY_REQUESTS_MULTIPLICATOR = 10;
    private boolean mCapFrameRate = true;
    /* access modifiers changed from: private */
    public AtomicBoolean mForceSingleFrame = new AtomicBoolean(false);
    /* access modifiers changed from: private */
    public GLSurfaceView mGLSurfaceView;
    private Handler mHandler;
    private int mMaxFps;
    private long mMaxTimeBetweenRenderRequest = 10;
    private ArrayList<RenderModeListener> mRenderModeListeners = new ArrayList<>();
    private final RenderRequest mRenderRequest = new RenderRequest();
    /* access modifiers changed from: private */
    public volatile int mRendering = 0;
    /* access modifiers changed from: private */
    public long mStartTime = 0;

    /* access modifiers changed from: protected */
    public abstract int getFrameDelay(long j);

    public FramerateControllerBase(int maxFps, GLSurfaceView surfaceView) {
        this.mMaxFps = maxFps;
        this.mHandler = new Handler(Looper.getMainLooper());
        setSurfaceView(surfaceView);
    }

    public int getMaxFps() {
        return this.mMaxFps;
    }

    public void setMaxFps(int maxFps) {
        this.mMaxFps = maxFps;
    }

    public long onFrame() {
        this.mHandler.removeCallbacks(this.mRenderRequest);
        long deltaTime = SystemClock.elapsedRealtime() - this.mStartTime;
        long delay = (long) getFrameDelay(deltaTime);
        long baseDelay = ((long) (1000 / this.mMaxFps)) - deltaTime;
        if (baseDelay > delay) {
            delay = baseDelay;
        }
        if (delay >= 1) {
            long actualDelay = delay;
            if (this.mMaxTimeBetweenRenderRequest < actualDelay) {
                actualDelay = this.mMaxTimeBetweenRenderRequest;
                this.mMaxTimeBetweenRenderRequest *= 10;
            }
            this.mHandler.postDelayed(this.mRenderRequest, actualDelay);
        } else {
            this.mHandler.post(this.mRenderRequest);
        }
        return deltaTime;
    }

    public void continueFrame() {
        this.mHandler.removeCallbacks(this.mRenderRequest);
        long delay = ((long) (1000 / this.mMaxFps)) - (SystemClock.elapsedRealtime() - this.mStartTime);
        if (!this.mCapFrameRate || ((double) delay) <= 1.0d) {
            this.mRenderRequest.run();
        } else {
            this.mHandler.postDelayed(this.mRenderRequest, delay);
        }
    }

    public void setCapFrameRate(boolean cap) {
        this.mCapFrameRate = cap;
    }

    public boolean getCapFrameRate() {
        return this.mCapFrameRate;
    }

    public void setSurfaceView(GLSurfaceView surfaceView) {
        this.mGLSurfaceView = surfaceView;
        this.mHandler.removeCallbacks(this.mRenderRequest);
        this.mHandler.post(this.mRenderRequest);
    }

    /* JADX WARNING: Code restructure failed: missing block: B:10:0x0015, code lost:
        monitor-enter(r3);
     */
    /* JADX WARNING: Code restructure failed: missing block: B:12:?, code lost:
        r0 = r4.mRenderModeListeners.iterator();
     */
    /* JADX WARNING: Code restructure failed: missing block: B:14:0x0020, code lost:
        if (r0.hasNext() == false) goto L_0x0032;
     */
    /* JADX WARNING: Code restructure failed: missing block: B:15:0x0022, code lost:
        r0.next().onStartRendering();
     */
    /* JADX WARNING: Code restructure failed: missing block: B:24:?, code lost:
        monitor-exit(r3);
     */
    /* JADX WARNING: Code restructure failed: missing block: B:25:0x0033, code lost:
        r4.mHandler.removeCallbacks(r4.mRenderRequest);
        r4.mHandler.post(r4.mRenderRequest);
        r4.mMaxTimeBetweenRenderRequest = 10;
     */
    /* JADX WARNING: Code restructure failed: missing block: B:30:?, code lost:
        return;
     */
    /* JADX WARNING: Code restructure failed: missing block: B:9:0x0013, code lost:
        r3 = r4.mRenderModeListeners;
     */
    /* Code decompiled incorrectly, please refer to instructions dump. */
    public void startRendering() {
        /*
            r4 = this;
            monitor-enter(r4)
            int r2 = r4.mRendering     // Catch:{ all -> 0x002f }
            if (r2 >= 0) goto L_0x0008
            r2 = 0
            r4.mRendering = r2     // Catch:{ all -> 0x002f }
        L_0x0008:
            int r2 = r4.mRendering     // Catch:{ all -> 0x002f }
            int r3 = r2 + 1
            r4.mRendering = r3     // Catch:{ all -> 0x002f }
            if (r2 == 0) goto L_0x0012
            monitor-exit(r4)     // Catch:{ all -> 0x002f }
        L_0x0011:
            return
        L_0x0012:
            monitor-exit(r4)     // Catch:{ all -> 0x002f }
            java.util.ArrayList<com.sonymobile.experienceflow.renderer.RenderModeListener> r3 = r4.mRenderModeListeners
            monitor-enter(r3)
            java.util.ArrayList<com.sonymobile.experienceflow.renderer.RenderModeListener> r2 = r4.mRenderModeListeners     // Catch:{ all -> 0x002c }
            java.util.Iterator r0 = r2.iterator()     // Catch:{ all -> 0x002c }
        L_0x001c:
            boolean r2 = r0.hasNext()     // Catch:{ all -> 0x002c }
            if (r2 == 0) goto L_0x0032
            java.lang.Object r1 = r0.next()     // Catch:{ all -> 0x002c }
            com.sonymobile.experienceflow.renderer.RenderModeListener r1 = (com.sonymobile.experienceflow.renderer.RenderModeListener) r1     // Catch:{ all -> 0x002c }
            r1.onStartRendering()     // Catch:{ all -> 0x002c }
            goto L_0x001c
        L_0x002c:
            r2 = move-exception
            monitor-exit(r3)     // Catch:{ all -> 0x002c }
            throw r2
        L_0x002f:
            r2 = move-exception
            monitor-exit(r4)     // Catch:{ all -> 0x002f }
            throw r2
        L_0x0032:
            monitor-exit(r3)     // Catch:{ all -> 0x002c }
            android.os.Handler r2 = r4.mHandler
            com.sonymobile.experienceflow.renderer.FramerateControllerBase$RenderRequest r3 = r4.mRenderRequest
            r2.removeCallbacks(r3)
            android.os.Handler r2 = r4.mHandler
            com.sonymobile.experienceflow.renderer.FramerateControllerBase$RenderRequest r3 = r4.mRenderRequest
            r2.post(r3)
            r2 = 10
            r4.mMaxTimeBetweenRenderRequest = r2
            goto L_0x0011
        */
        throw new UnsupportedOperationException("Method not decompiled: com.sonymobile.experienceflow.renderer.FramerateControllerBase.startRendering():void");
    }

    /* JADX WARNING: Code restructure failed: missing block: B:10:0x0015, code lost:
        monitor-enter(r3);
     */
    /* JADX WARNING: Code restructure failed: missing block: B:12:?, code lost:
        r0 = r4.mRenderModeListeners.iterator();
     */
    /* JADX WARNING: Code restructure failed: missing block: B:14:0x0020, code lost:
        if (r0.hasNext() == false) goto L_0x0032;
     */
    /* JADX WARNING: Code restructure failed: missing block: B:15:0x0022, code lost:
        r0.next().onStopRendering();
     */
    /* JADX WARNING: Code restructure failed: missing block: B:24:?, code lost:
        monitor-exit(r3);
     */
    /* JADX WARNING: Code restructure failed: missing block: B:25:0x0033, code lost:
        r4.mHandler.removeCallbacks(r4.mRenderRequest);
     */
    /* JADX WARNING: Code restructure failed: missing block: B:29:?, code lost:
        return;
     */
    /* JADX WARNING: Code restructure failed: missing block: B:30:?, code lost:
        return;
     */
    /* JADX WARNING: Code restructure failed: missing block: B:9:0x0013, code lost:
        r3 = r4.mRenderModeListeners;
     */
    /* Code decompiled incorrectly, please refer to instructions dump. */
    public void stopRendering() {
        /*
            r4 = this;
            monitor-enter(r4)
            int r2 = r4.mRendering     // Catch:{ all -> 0x002f }
            int r2 = r2 + -1
            r4.mRendering = r2     // Catch:{ all -> 0x002f }
            if (r2 == 0) goto L_0x0012
            int r2 = r4.mRendering     // Catch:{ all -> 0x002f }
            if (r2 >= 0) goto L_0x0010
            r2 = 0
            r4.mRendering = r2     // Catch:{ all -> 0x002f }
        L_0x0010:
            monitor-exit(r4)     // Catch:{ all -> 0x002f }
        L_0x0011:
            return
        L_0x0012:
            monitor-exit(r4)     // Catch:{ all -> 0x002f }
            java.util.ArrayList<com.sonymobile.experienceflow.renderer.RenderModeListener> r3 = r4.mRenderModeListeners
            monitor-enter(r3)
            java.util.ArrayList<com.sonymobile.experienceflow.renderer.RenderModeListener> r2 = r4.mRenderModeListeners     // Catch:{ all -> 0x002c }
            java.util.Iterator r0 = r2.iterator()     // Catch:{ all -> 0x002c }
        L_0x001c:
            boolean r2 = r0.hasNext()     // Catch:{ all -> 0x002c }
            if (r2 == 0) goto L_0x0032
            java.lang.Object r1 = r0.next()     // Catch:{ all -> 0x002c }
            com.sonymobile.experienceflow.renderer.RenderModeListener r1 = (com.sonymobile.experienceflow.renderer.RenderModeListener) r1     // Catch:{ all -> 0x002c }
            r1.onStopRendering()     // Catch:{ all -> 0x002c }
            goto L_0x001c
        L_0x002c:
            r2 = move-exception
            monitor-exit(r3)     // Catch:{ all -> 0x002c }
            throw r2
        L_0x002f:
            r2 = move-exception
            monitor-exit(r4)     // Catch:{ all -> 0x002f }
            throw r2
        L_0x0032:
            monitor-exit(r3)     // Catch:{ all -> 0x002c }
            android.os.Handler r2 = r4.mHandler
            com.sonymobile.experienceflow.renderer.FramerateControllerBase$RenderRequest r3 = r4.mRenderRequest
            r2.removeCallbacks(r3)
            goto L_0x0011
        */
        throw new UnsupportedOperationException("Method not decompiled: com.sonymobile.experienceflow.renderer.FramerateControllerBase.stopRendering():void");
    }

    public void forceSingleFrameRender() {
        this.mForceSingleFrame.set(true);
        this.mHandler.removeCallbacks(this.mRenderRequest);
        this.mHandler.postAtFrontOfQueue(this.mRenderRequest);
    }

    public void addRenderModeListener(RenderModeListener renderModeListener) {
        synchronized (this.mRenderModeListeners) {
            this.mRenderModeListeners.add(renderModeListener);
        }
    }

    public void removeRenderModeListener(RenderModeListener renderModeListener) {
        synchronized (this.mRenderModeListeners) {
            this.mRenderModeListeners.remove(renderModeListener);
        }
    }

    private final class RenderRequest implements Runnable {
        private RenderRequest() {
        }

        public void run() {
            if (FramerateControllerBase.this.mGLSurfaceView == null) {
                return;
            }
            if (FramerateControllerBase.this.mRendering > 0 || FramerateControllerBase.this.mForceSingleFrame.getAndSet(false)) {
                long unused = FramerateControllerBase.this.mStartTime = SystemClock.elapsedRealtime();
                FramerateControllerBase.this.mGLSurfaceView.requestRender();
            }
        }
    }
}
