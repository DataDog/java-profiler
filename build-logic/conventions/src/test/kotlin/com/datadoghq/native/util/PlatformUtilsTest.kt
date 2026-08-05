package com.datadoghq.native.util

import com.datadoghq.native.model.Architecture
import com.datadoghq.native.model.Platform
import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Test

class PlatformUtilsTest {

    @Test
    fun `gcc driver on macOS gets no arch flag`() {
        assertEquals(
            emptyList<String>(),
            PlatformUtils.macosArchitectureArgsFor(Platform.MACOS, Architecture.X64, "gcc")
        )
    }

    @Test
    fun `versioned g++ driver on macOS gets no arch flag`() {
        assertEquals(
            emptyList<String>(),
            PlatformUtils.macosArchitectureArgsFor(Platform.MACOS, Architecture.ARM64, "g++-13")
        )
    }

    @Test
    fun `clang++ driver on macOS gets x86_64 arch flag`() {
        assertEquals(
            listOf("-arch", "x86_64"),
            PlatformUtils.macosArchitectureArgsFor(Platform.MACOS, Architecture.X64, "clang++")
        )
    }

    @Test
    fun `cc driver on macOS gets arm64 arch flag`() {
        assertEquals(
            listOf("-arch", "arm64"),
            PlatformUtils.macosArchitectureArgsFor(Platform.MACOS, Architecture.ARM64, "cc")
        )
    }

    @Test
    fun `clang-like driver on linux gets no arch flag`() {
        assertEquals(
            emptyList<String>(),
            PlatformUtils.macosArchitectureArgsFor(Platform.LINUX, Architecture.X64, "clang++")
        )
    }

    @Test
    fun `gcc driver on linux gets no arch flag`() {
        assertEquals(
            emptyList<String>(),
            PlatformUtils.macosArchitectureArgsFor(Platform.LINUX, Architecture.X64, "gcc")
        )
    }
}
