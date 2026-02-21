package com.sonymobile.experienceflow.util;

import android.util.Log;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.List;

public class FreeList<K> {
    private int mFreeSize = this.mMaxSize;
    private int[] mIndexList;
    private int mMaxSize;
    private K[] mPool;
    private final Class<K> mProtoType;

    public FreeList(Class<K> clazz, int maxSize) {
        this.mProtoType = clazz;
        this.mMaxSize = maxSize;
        init();
    }

    private void init() {
        synchronized (this) {
            this.mIndexList = new int[this.mMaxSize];
        }
        for (int i = 0; i < this.mMaxSize; i++) {
            synchronized (this) {
                this.mIndexList[i] = i;
            }
        }
        ArrayList<K> tmp = new ArrayList<>();
        int i2 = 0;
        while (i2 < this.mMaxSize) {
            try {
                tmp.add(createContents(this.mProtoType));
                i2++;
            } catch (InstantiationException e) {
                Log.w(Constants.TAG, "Failed to create object in FreeList.", e);
            } catch (IllegalAccessException e2) {
                Log.w(Constants.TAG, "Failed to create object in FreeList.", e2);
            }
        }
        synchronized (this) {
            this.mPool = convertToArray(tmp, this.mProtoType);
        }
    }

    private K createContents(Class<K> clazz) throws InstantiationException, IllegalAccessException {
        return clazz.newInstance();
    }

    private static <K> K[] convertToArray(List<K> list, Class<K> clazz) {
        return list.toArray((Object[]) ((Object[]) Array.newInstance(clazz, list.size())));
    }

    public synchronized K checkOut() {
        K k;
        if (this.mFreeSize <= 0) {
            k = null;
        } else {
            this.mFreeSize--;
            k = this.mPool[this.mIndexList[0]];
            int temp = this.mIndexList[0];
            this.mIndexList[0] = this.mIndexList[this.mFreeSize];
            this.mIndexList[this.mFreeSize] = temp;
        }
        return k;
    }

    public synchronized void checkIn(K k) {
        if (this.mFreeSize < this.mMaxSize) {
            K[] kArr = this.mPool;
            int[] iArr = this.mIndexList;
            int i = this.mFreeSize;
            this.mFreeSize = i + 1;
            kArr[iArr[i]] = k;
        }
    }

    public synchronized int getCapacity() {
        return this.mMaxSize;
    }

    public synchronized int getNumOfFreeObjects() {
        return this.mFreeSize;
    }

    public synchronized boolean isEmpty() {
        return this.mFreeSize == 0;
    }
}
