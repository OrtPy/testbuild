package com.example.lwprpcharness

class NativeSession(
    @Volatile var handle: Long = 0L,
    @Volatile var loadedPath: String? = null
)
