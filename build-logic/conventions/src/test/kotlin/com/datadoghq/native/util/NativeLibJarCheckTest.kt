// Copyright 2026, Datadog, Inc.

package com.datadoghq.native.util

import org.gradle.api.GradleException
import org.junit.jupiter.api.Assertions.assertTrue
import org.junit.jupiter.api.Test
import org.junit.jupiter.api.assertDoesNotThrow
import org.junit.jupiter.api.assertThrows
import org.junit.jupiter.api.io.TempDir
import java.io.ByteArrayOutputStream
import java.io.File
import java.util.zip.ZipEntry
import java.util.zip.ZipOutputStream

class NativeLibJarCheckTest {

    @TempDir
    lateinit var tmp: File

    private fun jar(vararg names: String): File {
        val bytes = ByteArrayOutputStream()
        ZipOutputStream(bytes).use { zip ->
            names.forEach { name ->
                zip.putNextEntry(ZipEntry(name))
                zip.write(name.toByteArray())
                zip.closeEntry()
            }
        }
        return File(tmp, "test.jar").apply { writeBytes(bytes.toByteArray()) }
    }

    // ZipOutputStream rejects duplicate names, but jmhJar's INCLUDE duplicates strategy writes them.
    // Write a same-length placeholder name, then rename it in place: offsets and CRCs stay valid.
    private fun jarWithDuplicate(name: String, vararg others: String): File {
        val placeholder = name.dropLast(1) + "_"
        val file = jar(*others, name, placeholder)
        val text = String(file.readBytes(), Charsets.ISO_8859_1).replace(placeholder, name)
        file.writeBytes(text.toByteArray(Charsets.ISO_8859_1))
        return file
    }

    @Test
    fun `one library per platform passes and debug symbols are ignored`() {
        val file = jar(
            "META-INF/native-libs/linux-x64/libjavaProfiler.so",
            "META-INF/native-libs/linux-x64/libjavaProfiler.so.debug",
            "META-INF/native-libs/macos-arm64/libjavaProfiler.dylib",
            "META-INF/native-libs/macos-arm64/libjavaProfiler.dylib.dSYM/Contents/Resources/DWARF/libjavaProfiler.dylib",
        )
        assertDoesNotThrow { NativeLibJarCheck.verifyOneLibPerPlatform(file) }
    }

    @Test
    fun `jar with only debug symbols has no library`() {
        val file = jar(
            "META-INF/native-libs/linux-x64/libjavaProfiler.so.debug",
            "META-INF/native-libs/macos-arm64/libjavaProfiler.dylib.dSYM/Contents/Resources/DWARF/libjavaProfiler.dylib",
        )
        val e = assertThrows<GradleException> { NativeLibJarCheck.verifyOneLibPerPlatform(file) }
        assertTrue(e.message!!.startsWith("No libjavaProfiler found"), e.message)
    }

    @Test
    fun `duplicate library entry in one platform directory fails`() {
        val file = jarWithDuplicate("META-INF/native-libs/linux-x64/libjavaProfiler.so")
        val e = assertThrows<GradleException> { NativeLibJarCheck.verifyOneLibPerPlatform(file) }
        assertTrue(e.message!!.contains("META-INF/native-libs/linux-x64 "), e.message)
        assertTrue(e.message!!.endsWith("found 2"), e.message)
    }

    @Test
    fun `duplicate in a later platform directory fails after a valid one`() {
        val file = jarWithDuplicate(
            "META-INF/native-libs/linux-x64/libjavaProfiler.so",
            "META-INF/native-libs/linux-arm64/libjavaProfiler.so",
        )
        val e = assertThrows<GradleException> { NativeLibJarCheck.verifyOneLibPerPlatform(file) }
        assertTrue(e.message!!.contains("META-INF/native-libs/linux-x64 "), e.message)
    }
}
