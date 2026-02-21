package com.sonymobile.experienceflow.renderer;

public class Capabilities {
    public static final String CAP_VERTEX_HALF_FLOAT = "GL_OES_vertex_half_float";
    private static final boolean DEBUG = false;
    private String[] extensions;
    private int mMaxTextureSize;

    /* access modifiers changed from: package-private */
    public void setExtensions(String[] extensions2) {
        this.extensions = extensions2;
    }

    /* access modifiers changed from: package-private */
    public void setMaxTextureSize(int maxTexSize) {
        this.mMaxTextureSize = maxTexSize;
    }

    public boolean checkExtension(String extension) {
        for (String equals : this.extensions) {
            if (equals.equals(extension)) {
                return true;
            }
        }
        return false;
    }

    public boolean hasVertextHalfFloat() {
        return checkExtension(CAP_VERTEX_HALF_FLOAT);
    }

    public int getMaxTextureSize() {
        return this.mMaxTextureSize;
    }
}
