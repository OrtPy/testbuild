package com.sonymobile.experienceflow.renderer;

import android.content.res.AssetManager;

public class CurveRendererImpl extends CurveRenderer {
    int id;
    protected RenderListener renderListener;

    public interface RenderListener {
        void pleaseRender();
    }

    /*  JADX ERROR: IndexOutOfBoundsException in pass: RegionMakerVisitor
        java.lang.IndexOutOfBoundsException: Index: 0, Size: 0
        	at java.util.ArrayList.rangeCheck(ArrayList.java:659)
        	at java.util.ArrayList.get(ArrayList.java:435)
        	at jadx.core.dex.nodes.InsnNode.getArg(InsnNode.java:101)
        	at jadx.core.dex.visitors.regions.RegionMaker.traverseMonitorExits(RegionMaker.java:611)
        	at jadx.core.dex.visitors.regions.RegionMaker.traverseMonitorExits(RegionMaker.java:619)
        	at jadx.core.dex.visitors.regions.RegionMaker.traverseMonitorExits(RegionMaker.java:619)
        	at jadx.core.dex.visitors.regions.RegionMaker.traverseMonitorExits(RegionMaker.java:619)
        	at jadx.core.dex.visitors.regions.RegionMaker.processMonitorEnter(RegionMaker.java:561)
        	at jadx.core.dex.visitors.regions.RegionMaker.traverse(RegionMaker.java:133)
        	at jadx.core.dex.visitors.regions.RegionMaker.makeRegion(RegionMaker.java:86)
        	at jadx.core.dex.visitors.regions.RegionMaker.processIf(RegionMaker.java:693)
        	at jadx.core.dex.visitors.regions.RegionMaker.traverse(RegionMaker.java:123)
        	at jadx.core.dex.visitors.regions.RegionMaker.makeRegion(RegionMaker.java:86)
        	at jadx.core.dex.visitors.regions.RegionMaker.processMonitorEnter(RegionMaker.java:598)
        	at jadx.core.dex.visitors.regions.RegionMaker.traverse(RegionMaker.java:133)
        	at jadx.core.dex.visitors.regions.RegionMaker.makeRegion(RegionMaker.java:86)
        	at jadx.core.dex.visitors.regions.RegionMakerVisitor.visit(RegionMakerVisitor.java:49)
        */
    protected synchronized void pleaseRender() {
        /*
            r1 = this;
            monitor-enter(r1)
            com.sonymobile.experienceflow.renderer.CurveRendererImpl$RenderListener r0 = r1.renderListener     // Catch:{ all -> 0x0011 }
            if (r0 == 0) goto L_0x000c
            monitor-enter(r1)     // Catch:{ all -> 0x0011 }
            com.sonymobile.experienceflow.renderer.CurveRendererImpl$RenderListener r0 = r1.renderListener     // Catch:{ all -> 0x000e }
            r0.pleaseRender()     // Catch:{ all -> 0x000e }
            monitor-exit(r1)     // Catch:{ all -> 0x000e }
        L_0x000c:
            monitor-exit(r1)
            return
        L_0x000e:
            r0 = move-exception
            monitor-exit(r1)     // Catch:{ all -> 0x000e }
            throw r0     // Catch:{ all -> 0x0011 }
        L_0x0011:
            r0 = move-exception
            monitor-exit(r1)
            throw r0
        */
        throw new UnsupportedOperationException("Method not decompiled: com.sonymobile.experienceflow.renderer.CurveRendererImpl.pleaseRender():void");
    }

    public CurveRendererImpl(AssetManager am) {
        this.id = init(am);
    }

    public synchronized void updateScreenLayout(int x, int y, int w, int h, int sw, int sh) {
        super.updateScreenLayout(this.id, x, y, w, h, sw, sh);
    }

    public synchronized void requestColors(AssetManager am, int theme) {
        super.requestColors(this.id, am, theme);
        pleaseRender();
    }

    public synchronized void touchDown(float x, float y) {
        super.touchDown(this.id, x, y);
        pleaseRender();
    }

    public synchronized void touch(float x, float y) {
        super.touch(this.id, x, y);
        pleaseRender();
    }

    public synchronized void touchUp(float x, float y) {
        super.touchUp(this.id, x, y);
        pleaseRender();
    }

    public synchronized void activate() {
        super.activate(this.id);
        pleaseRender();
    }

    public synchronized void deactivate() {
        super.deactivate(this.id);
        pleaseRender();
    }

    public synchronized void setOnRenderListener(RenderListener l) {
        this.renderListener = l;
    }

    public synchronized void render(AssetManager am) {
        super.render(this.id, am);
    }

    public synchronized int getSleepRecommendation() {
        return super.getSleepRecommendation(this.id);
    }
}
