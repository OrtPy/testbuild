package com.example.lwprpcharness

import java.io.File

/**
 * Minimal /proc/self/maps parser.
 */
object ProcMaps {

    data class Mapping(
        val start: Long,
        val end: Long,
        val perms: String,
        val offset: Long,
        val dev: String,
        val inode: Long,
        val path: String
    )

    fun parseSelf(): List<Mapping> {
        val lines = try {
            File("/proc/self/maps").readLines()
        } catch (_: Throwable) {
            return emptyList()
        }
        val out = ArrayList<Mapping>(lines.size)
        for (ln in lines) {
            val m = parseLine(ln) ?: continue
            out.add(m)
        }
        return out
    }

    private fun parseLine(line: String): Mapping? {
        // Format:
        // start-end perms offset dev inode [pathname]
        // Example:
        // 12c00000-12c21000 r--p 00000000 fc:00 12345 /path/lib.so
        val parts = line.trim().split(Regex("\\s+"))
        if (parts.size < 5) return null

        val range = parts[0].split('-')
        if (range.size != 2) return null

        val start = range[0].toLongOrNull(16) ?: return null
        val end = range[1].toLongOrNull(16) ?: return null
        val perms = parts[1]
        val offset = parts[2].toLongOrNull(16) ?: 0L
        val dev = parts[3]
        val inode = parts[4].toLongOrNull() ?: 0L
        val path = if (parts.size >= 6) {
            // Keep spaces (rare) by slicing original string after inode
            line.substringAfter(parts[4], "").trimStart()
        } else {
            ""
        }
        return Mapping(start, end, perms, offset, dev, inode, path)
    }

    fun findModuleMappings(pathSubstring: String): List<Mapping> {
        val maps = parseSelf()
        return maps.filter { it.path.contains(pathSubstring) }
    }

    fun findModuleBase(pathSubstring: String): Long? {
        return findModuleMappings(pathSubstring).firstOrNull()?.start
    }

    fun findEntryContaining(addr: Long): Mapping? {
        return parseSelf().firstOrNull { addr >= it.start && addr < it.end }
    }

    /**
     * Helper for callers that already have a parsed maps list.
     */
    fun findMappingContaining(addr: Long, maps: List<Mapping>): Mapping? {
        return maps.firstOrNull { addr >= it.start && addr < it.end }
    }
}
