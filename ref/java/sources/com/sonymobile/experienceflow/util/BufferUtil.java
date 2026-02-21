package com.sonymobile.experienceflow.util;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.nio.ShortBuffer;

public class BufferUtil {
    public static final int BYTES_PER_FLOAT = 4;
    public static final int BYTES_PER_SHORT = 2;

    public static FloatBuffer createFloatBuffer(float[] floats) {
        FloatBuffer floatBuffer = ByteBuffer.allocateDirect(floats.length * 4).order(ByteOrder.nativeOrder()).asFloatBuffer();
        floatBuffer.put(floats).position(0);
        return floatBuffer;
    }

    public static ShortBuffer createShortBuffer(float[] floats) {
        ShortBuffer shortBuffer = ByteBuffer.allocateDirect(floats.length * 2).order(ByteOrder.nativeOrder()).asShortBuffer();
        for (float f : floats) {
            shortBuffer.put(FastMath.convertFloatToHalf(f));
        }
        shortBuffer.position(0);
        return shortBuffer;
    }
}
