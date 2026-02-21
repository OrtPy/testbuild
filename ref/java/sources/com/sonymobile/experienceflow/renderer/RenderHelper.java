package com.sonymobile.experienceflow.renderer;

public class RenderHelper {
    CurveRendererImpl curveRenderer;
    /* access modifiers changed from: private */
    public volatile Thread thread;

    public RenderHelper(CurveRendererImpl cri) {
        this.curveRenderer = cri;
    }

    public void continueFrame() {
        this.thread.interrupt();
    }

    public void startRenderTimingLoop() {
        if (this.thread == null) {
            this.thread = new Thread(new Runnable() {
                public void run() {
                    RenderHelper.this.curveRenderer.activate();
                    while (RenderHelper.this.thread != null) {
                        RenderHelper.this.curveRenderer.pleaseRender();
                        try {
                            Thread.sleep((long) RenderHelper.this.curveRenderer.getSleepRecommendation());
                        } catch (InterruptedException e) {
                        }
                    }
                    RenderHelper.this.curveRenderer.deactivate();
                }
            });
            this.thread.start();
        }
    }

    public void stopRenderTimingLoop() {
        if (this.thread != null) {
            Thread t = this.thread;
            this.thread = null;
            t.interrupt();
            try {
                t.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
