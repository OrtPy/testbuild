package com.example.lwprpcharness

object NativeBridge {

    const val RTLD_LAZY = 1
    const val RTLD_NOW = 2
    const val RTLD_LOCAL = 0
    const val RTLD_GLOBAL = 0x100

    init {
        System.loadLibrary("lwpbridge")
    }

    external fun dlopen(path: String, flags: Int): Long
    external fun dlclose(handle: Long)
    external fun dlsym(handle: Long, name: String): Long
    external fun dlerrorString(): String

    /**
     * dladdr() wrapper. Returns [fname, sname, fbase_hex, saddr_hex].
     * Empty array when not resolved.
     */
    external fun dladdr(ptr: Long): Array<String>

    external fun listExports(path: String, filter: String?): Array<String>

    /**
     * ARM32 AAPCS: args = 32bit words.
     * returns longArrayOf(r0_u32, r1_u32)
     */
    external fun callWords(fnPtr: Long, args: IntArray): LongArray

    external fun malloc(size: Int): Long
    external fun free(ptr: Long)
    external fun writeMem(ptr: Long, data: ByteArray): Boolean
    external fun readMem(ptr: Long, size: Int): ByteArray
}
