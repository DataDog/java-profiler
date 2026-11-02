/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.native.gtest

import org.gradle.testkit.runner.GradleRunner
import org.gradle.testkit.runner.TaskOutcome
import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Assertions.assertTrue
import org.junit.jupiter.api.Test
import org.junit.jupiter.api.condition.EnabledOnOs
import org.junit.jupiter.api.condition.OS
import org.junit.jupiter.api.io.TempDir
import java.io.File

/** Exercises the Linux helper task through real Gradle and Make invocations. */
@EnabledOnOs(OS.LINUX)
class GtestPluginTest {
    @TempDir
    lateinit var projectDir: File

    @Test
    fun `helpers use the selected compiler without sanitizer flags and rebuild when it changes`() {
        projectDir.resolve("settings.gradle").writeText("rootProject.name = 'helper-compiler-test'\n")
        projectDir.resolve("build.gradle.kts").writeText("""
            import com.datadoghq.native.NativeBuildExtension
            import com.datadoghq.native.gtest.GtestExtension
            import com.datadoghq.native.model.Platform
            import com.datadoghq.native.util.PlatformUtils

            plugins { id("com.datadoghq.gtest") }

            val nativeBuild = extensions.create(
                "nativeBuild", NativeBuildExtension::class.java, project, objects
            )
            nativeBuild.buildConfigurations.create("asan") {
                platform.set(Platform.LINUX)
                architecture.set(PlatformUtils.currentArchitecture)
                compilerArgs.set(listOf("-fsanitize=address"))
                linkerArgs.set(listOf("-fsanitize=address"))
            }
            extensions.configure<GtestExtension>("gtest") {
                testSourceDir.set(layout.projectDirectory.dir("src/test/cpp"))
                mainSourceDir.set(layout.projectDirectory.dir("src/main/cpp"))
                nativeLibsSourceDir.set(layout.projectDirectory.dir("native-libs"))
                nativeLibsOutputDir.set(layout.buildDirectory.dir("native-libs"))
            }
            // The fixture only records Make arguments; it does not link Google Test.
            afterEvaluate {
                tasks.named("buildNativeLibs") { setOnlyIf { true } }
            }
        """.trimIndent())
        val helper = projectDir.resolve("native-libs/probe")
        assertTrue(helper.mkdirs())
        helper.resolve("Makefile").writeText(
            ".PHONY: all\nall:\n" +
                "\t@printf '%s\\n' '$(CXX)' > '$(TARGET_DIR)/compiler.txt'\n" +
                "\t@printf '%s\\n' '$(CXXFLAGS)$(LDFLAGS)' > '$(TARGET_DIR)/flags.txt'\n"
        )
        val firstCompiler = compiler("first-c++")
        val secondCompiler = compiler("second-c++")
        val output = projectDir.resolve("build/native-libs/probe")

        assertEquals(TaskOutcome.SUCCESS, build(firstCompiler))
        assertEquals(firstCompiler.absolutePath, output.resolve("compiler.txt").readText().trim())
        assertEquals("", output.resolve("flags.txt").readText().trim())
        assertEquals(TaskOutcome.UP_TO_DATE, build(firstCompiler))

        assertEquals(TaskOutcome.SUCCESS, build(secondCompiler))
        assertEquals(secondCompiler.absolutePath, output.resolve("compiler.txt").readText().trim())
        assertEquals("", output.resolve("flags.txt").readText().trim())
    }

    /** A version-only compiler fixture makes the selected executable distinguishable from Make's default. */
    private fun compiler(name: String): File = projectDir.resolve(name).apply {
        writeText("#!/bin/sh\nprintf '%s\\n' 'compiler fixture'\n")
        assertTrue(setExecutable(true))
    }

    /** Runs the real helper task without unrelated flags inherited from the test runner. */
    private fun build(compiler: File): TaskOutcome? = GradleRunner.create()
        .withProjectDir(projectDir)
        .withPluginClasspath()
        .withEnvironment(System.getenv() + mapOf("CXXFLAGS" to "", "LDFLAGS" to ""))
        .withArguments("buildNativeLibs", "-Pnative.forceCompiler=${compiler.absolutePath}", "--offline")
        .build()
        .task(":buildNativeLibs")?.outcome
}
