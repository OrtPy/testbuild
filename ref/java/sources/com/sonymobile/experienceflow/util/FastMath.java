package com.sonymobile.experienceflow.util;

public final class FastMath {
    private FastMath() {
    }

    public static short convertFloatToHalf(float flt) {
        if (Float.isNaN(flt)) {
            throw new UnsupportedOperationException("NaN to half conversion not supported!");
        } else if (flt == Float.POSITIVE_INFINITY) {
            return 31744;
        } else {
            if (flt == Float.NEGATIVE_INFINITY) {
                return -1024;
            }
            if (flt == 0.0f) {
                return 0;
            }
            if (flt == -0.0f) {
                return Short.MIN_VALUE;
            }
            if (flt > 65504.0f) {
                return 31743;
            }
            if (flt < -65504.0f) {
                return -1025;
            }
            if (flt > 0.0f && flt < 5.96046E-8f) {
                return 1;
            }
            if (flt < 0.0f && flt > -5.96046E-8f) {
                return -32767;
            }
            int f = Float.floatToIntBits(flt);
            return (short) (((f >> 16) & 32768) | ((((2139095040 & f) - 939524096) >> 13) & 31744) | ((f >> 13) & 1023));
        }
    }
}
