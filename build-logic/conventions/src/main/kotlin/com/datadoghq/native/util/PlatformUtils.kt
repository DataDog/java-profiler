// Copyright 2026, Datadog, Inc

package com.datadoghq.native.util

import com.datadoghq.native.model.Architecture
import com.datadoghq.native.model.Platform
import org.gradle.api.Project
import java.io.File

object PlatformUtils {
    val currentPlatform: Platform by lazy { Platform.current() }
    val currentArchitecture: Architecture by lazy { Architecture.current() }

    fun isMusl(): Boolean {
        if (currentPlatform != Platform.LINUX) {
            return false
        }

        // Check if running on musl libc by scanning /lib/ld-musl-*.so.1
        return File("/lib").listFiles()?.any {
            it.name.startsWith("ld-musl-") && it.name.endsWith(".so.1")
        } ?: false
    }

    fun javaHome(): String {
        return System.getenv("JAVA_HOME")
            ?: System.getProperty("java.home")
            ?: throw IllegalStateException("JAVA_HOME not set")
    }

    fun jniIncludePaths(): List<String> {
        val javaHome = javaHome()
        val platform = when (currentPlatform) {
            Platform.LINUX -> "linux"
            Platform.MACOS -> "darwin"
        }
        return listOf(
            "$javaHome/include",
            "$javaHome/include/$platform"
        )
    }

    /**
     * Locate a library using gcc -print-file-name
     */
    fun locateLibrary(libName: String): String? {
        if (currentPlatform != Platform.LINUX) {
            return null
        }

        return try {
            val process = ProcessBuilder("gcc", "-print-file-name=$libName.so")
                .redirectErrorStream(true)
                .start()

            val output = process.inputStream.bufferedReader().readText().trim()
            process.waitFor()

            if (process.exitValue() == 0 && !output.endsWith("$libName.so")) {
                output
            } else {
                null
            }
        } catch (e: Exception) {
            null
        }
    }

    fun locateLibasan(): String? = locateLibrary("libasan")

    fun locateLibtsan(): String? = locateLibrary("libtsan")

    fun checkFuzzerSupport(): Boolean {
        return try {
            val testFile = createTempFile("fuzzer_check", ".cpp")
            try {
                testFile.writeText("extern \"C\" int LLVMFuzzerTestOneInput(const char*, long) { return 0; }")

                val process = ProcessBuilder(
                    "clang++",
                    "-fsanitize=fuzzer",
                    "-c",
                    testFile.absolutePath,
                    "-o",
                    "/dev/null"
                ).redirectErrorStream(true).start()

                process.waitFor()
                process.exitValue() == 0
            } finally {
                testFile.delete()
            }
        } catch (e: Exception) {
            false
        }
    }

    fun hasAsan(): Boolean {
        return !isMusl() && locateLibasan() != null
    }

    fun hasTsan(): Boolean {
        return !isMusl() && locateLibtsan() != null
    }

    fun hasFuzzer(): Boolean {
        return !isMusl() && checkFuzzerSupport()
    }

    fun sharedLibExtension(): String = when (currentPlatform) {
        Platform.LINUX -> "so"
        Platform.MACOS -> "dylib"
    }
}
