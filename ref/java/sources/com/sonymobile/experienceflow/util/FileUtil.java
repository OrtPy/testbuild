package com.sonymobile.experienceflow.util;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Log;
import java.io.Closeable;
import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.Charset;

public class FileUtil {
    public static String readStringFromfile(String fileName) {
        String result = null;
        InputStream stream = null;
        ClassLoader cl = FileUtil.class.getClassLoader();
        if (cl == null) {
            return null;
        }
        try {
            InputStream stream2 = cl.getResourceAsStream(fileName);
            if (stream2 != null) {
                int bytesRead = 0;
                int bytesToRead = stream2.available();
                byte[] buffer = new byte[bytesToRead];
                while (bytesRead < bytesToRead) {
                    int read = stream2.read(buffer, bytesRead, bytesToRead - bytesRead);
                    if (read == -1) {
                        break;
                    }
                    bytesRead += read;
                }
                result = new String(buffer, Charset.forName("UTF-8"));
            }
            if (stream2 != null) {
                try {
                    stream2.close();
                } catch (IOException e) {
                    Log.w(Constants.TAG, "Couldn't close  " + fileName, e);
                }
            }
        } catch (IOException e2) {
            Log.w(Constants.TAG, "Couldn't find " + fileName, e2);
            if (stream != null) {
                try {
                    stream.close();
                } catch (IOException e3) {
                    Log.w(Constants.TAG, "Couldn't close  " + fileName, e3);
                }
            }
        } catch (Throwable th) {
            if (stream != null) {
                try {
                    stream.close();
                } catch (IOException e4) {
                    Log.w(Constants.TAG, "Couldn't close  " + fileName, e4);
                }
            }
            throw th;
        }
        return result;
    }

    public static Bitmap readBitmapFromfile(String fileName) {
        ClassLoader cl = FileUtil.class.getClassLoader();
        if (cl == null) {
            return null;
        }
        return BitmapFactory.decodeStream(cl.getResourceAsStream(fileName));
    }

    public static void closeStream(Closeable inputStream) {
        if (inputStream != null) {
            try {
                inputStream.close();
            } catch (IOException e) {
                Log.w(Constants.TAG, "Error closing stream.", e);
            }
        }
    }
}
