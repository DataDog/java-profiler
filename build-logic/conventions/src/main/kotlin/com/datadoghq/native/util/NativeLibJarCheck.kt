/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.native.util

import org.gradle.api.GradleException
import java.io.File
import java.util.zip.ZipFile

/** Checks the `libjavaProfiler` entries bundled under `META-INF/native-libs` in a jar. */
object NativeLibJarCheck {
    // Exact library files only: -Pwith-libs also copies *.debug files and .dSYM bundles next to them.
    private val NATIVE_LIB = Regex("META-INF/native-libs/[^/]+/libjavaProfiler\\.(so|dylib)")

    /**
     * Throws [GradleException] if [jar] holds no `libjavaProfiler`, or more than one in a platform
     * directory, duplicate entries with the same name included. It counts libraries only and does
     * not tell a release build from a debug one.
     */
    fun verifyOneLibPerPlatform(jar: File) {
        val perDir = ZipFile(jar).use { zip ->
            zip.entries().asSequence()
                .map { it.name }
                .filter { NATIVE_LIB.matches(it) }
                .groupBy { it.substringBeforeLast('/') }
        }
        if (perDir.isEmpty()) {
            throw GradleException("No libjavaProfiler found in $jar")
        }
        perDir.forEach { (dir, entries) ->
            if (entries.size != 1) {
                throw GradleException("Expected one libjavaProfiler in $dir of $jar, found ${entries.size}")
            }
        }
    }
}
