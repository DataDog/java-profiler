/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.native.util

import org.gradle.api.GradleException
import org.gradle.api.Project
import org.gradle.api.Task
import org.gradle.api.tasks.TaskProvider
import org.gradle.jvm.tasks.Jar
import java.io.File
import java.util.zip.ZipFile

/** Checks the `libjavaProfiler` entries bundled under `META-INF/native-libs` in a jar. */
object NativeLibJarCheck {
    // Exact library files only: -Pwith-libs also copies *.debug files and .dSYM bundles next to them.
    private val NATIVE_LIB = Regex("META-INF/native-libs/[^/]+/libjavaProfiler\\.(so|dylib)")

    /**
     * Throws [GradleException] if [jar] holds no `libjavaProfiler`, more than one in a platform
     * directory (duplicate entries with the same name included), or none in the [hostPlatform]
     * directory, the only one `LibraryLoader` reads on this host. It counts libraries only and does
     * not tell a release build from a debug one.
     */
    fun verifyOneLibPerPlatform(jar: File, hostPlatform: String) {
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
        if (!perDir.containsKey("META-INF/native-libs/$hostPlatform")) {
            throw GradleException("No libjavaProfiler for host platform $hostPlatform in $jar")
        }
    }

    /**
     * Registers `verifyJmhJarNativeLibs` for [jar] and orders it before every task named in
     * [guarded] (matched lazily, so they may be registered later). It also finalizes [jar], so a
     * jar built on its own is checked before it is run with `java -jar`.
     */
    fun register(project: Project, jar: TaskProvider<out Jar>, hostPlatform: String, vararg guarded: String): TaskProvider<Task> {
        val archive = jar.flatMap { it.archiveFile }
        val verify = project.tasks.register("verifyJmhJarNativeLibs") {
            group = "verification"
            description = "Verify the JMH jar contains exactly one libjavaProfiler per platform, including the host's"
            inputs.file(archive)
            doLast { verifyOneLibPerPlatform(archive.get().asFile, hostPlatform) }
        }
        project.tasks.matching { it.name in guarded }.configureEach { dependsOn(verify) }
        jar.configure { finalizedBy(verify) }
        return verify
    }
}
