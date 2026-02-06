// Copyright 2026, Datadog, Inc

package com.datadoghq.native.gtest

import org.gradle.api.file.ConfigurableFileCollection
import org.gradle.api.file.DirectoryProperty
import org.gradle.api.model.ObjectFactory
import org.gradle.api.provider.Property
import javax.inject.Inject

/**
 * Extension for configuring Google Test integration in C++ projects.
 *
 * Provides a declarative DSL for setting up Google Test compilation, linking, and execution
 * across multiple build configurations (debug, release, asan, tsan).
 *
 * Usage example:
 * ```kotlin
 * gtest {
 *     testSourceDir.set(layout.projectDirectory.dir("src/test/cpp"))
 *     mainSourceDir.set(layout.projectDirectory.dir("src/main/cpp"))
 *     includes.from("src/main/cpp", "${javaHome}/include")
 * }
 * ```
 */
abstract class GtestExtension @Inject constructor(objects: ObjectFactory) {

    // === Source Directories ===

    /**
     * Directory containing test source files (.cpp).
     * Required - must be set explicitly.
     */
    abstract val testSourceDir: DirectoryProperty

    /**
     * Directory containing main source files to compile with tests.
     * Required - must be set explicitly.
     */
    abstract val mainSourceDir: DirectoryProperty

    /**
     * Optional Google Test installation directory.
     * Used for include and library paths on macOS.
     * Default: /opt/homebrew/opt/googletest on macOS
     */
    abstract val googleTestHome: DirectoryProperty

    // === Compiler/Linker Configuration ===

    /**
     * Include directories for compilation.
     * Should include main source, JNI headers, and any dependencies.
     */
    abstract val includes: ConfigurableFileCollection

    // === Test Behavior ===

    /**
     * Enable assertions by removing -DNDEBUG from compiler args.
     * Default: true
     */
    abstract val enableAssertions: Property<Boolean>

    /**
     * Keep symbols in release builds (skip minimizing linker flags).
     * Default: true
     */
    abstract val keepSymbols: Property<Boolean>

    /**
     * Stop on first test failure (fail-fast).
     * Default: false (collect all failures)
     */
    abstract val failFast: Property<Boolean>

    /**
     * Always re-run tests (ignore up-to-date checks).
     * Default: true
     */
    abstract val alwaysRun: Property<Boolean>

    // === Build Native Libs Task ===

    /**
     * Enable building native test support libraries (Linux only).
     * Default: true
     */
    abstract val buildNativeLibs: Property<Boolean>

    /**
     * Directory containing native test library sources.
     * Default: src/test/resources/native-libs
     */
    abstract val nativeLibsSourceDir: DirectoryProperty

    /**
     * Output directory for built native test libraries.
     * Default: build/test/resources/native-libs
     */
    abstract val nativeLibsOutputDir: DirectoryProperty

    init {
        // Set default conventions
        enableAssertions.convention(true)
        keepSymbols.convention(true)
        failFast.convention(false)
        alwaysRun.convention(true)
        buildNativeLibs.convention(true)
    }
}
