/*
 * Copyright 2026, Datadog, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import org.gradle.api.file.ConfigurableFileCollection
import org.gradle.api.file.DirectoryProperty
import org.gradle.api.model.ObjectFactory
import org.gradle.api.provider.ListProperty
import org.gradle.api.provider.MapProperty
import org.gradle.api.provider.Property

import javax.inject.Inject

/**
 * Extension for configuring Google Test integration in C++ projects.
 *
 * <p>Provides a declarative DSL for setting up Google Test compilation, linking, and execution
 * across multiple build configurations (debug, release, asan, tsan).
 *
 * <p>Usage example:</p>
 * <pre>
 * gtest {
 *     testSourceDir = file('src/test/cpp')
 *     mainSourceDir = file('src/main/cpp')
 *     includes = files(
 *         'src/main/cpp',
 *         "${System.env.JAVA_HOME}/include"
 *     )
 *     configurations = [debug, release, asan, tsan]
 *     googleTestHome = file('/opt/homebrew/opt/googletest')
 * }
 * </pre>
 */
class GtestExtension {

    // === Source Directories ===

    /**
     * Directory containing test source files (.cpp).
     * Default: src/test/cpp
     */
    final DirectoryProperty testSourceDir

    /**
     * Directory containing main source files to compile with tests.
     * Default: src/main/cpp
     */
    final DirectoryProperty mainSourceDir

    /**
     * Optional Google Test installation directory.
     * Used for include and library paths on macOS.
     * Default: null (uses system paths or /opt/homebrew/opt/googletest on macOS)
     */
    final DirectoryProperty googleTestHome

    // === Compiler/Linker Configuration ===

    /**
     * Include directories for compilation.
     * Should include main source, JNI headers, and any dependencies.
     */
    final ConfigurableFileCollection includes

    /**
     * Build configurations to create tests for.
     * Each config should have: name, compiler, compilerArgs, linkerArgs, active, testEnv
     */
    final ListProperty<Object> configurations

    // === Test Behavior ===

    /**
     * Enable assertions by removing -DNDEBUG from compiler args.
     * Default: true
     */
    final Property<Boolean> enableAssertions

    /**
     * Keep symbols in release builds (skip minimizing linker flags).
     * Default: true
     */
    final Property<Boolean> keepSymbols

    /**
     * Stop on first test failure (fail-fast).
     * Default: false (collect all failures)
     */
    final Property<Boolean> failFast

    /**
     * Always re-run tests (ignore up-to-date checks).
     * Default: true
     */
    final Property<Boolean> alwaysRun

    // === Platform-Specific ===

    /**
     * Custom Google Test library paths per platform.
     * Example: ['macos': '/opt/homebrew/opt/googletest/lib']
     */
    final MapProperty<String, String> gtestLibPaths

    /**
     * Custom Google Test include paths per platform.
     * Example: ['macos': '/opt/homebrew/opt/googletest/include']
     */
    final MapProperty<String, String> gtestIncludePaths

    // === Build Native Libs Task ===

    /**
     * Enable building native test support libraries (Linux only).
     * Default: true
     */
    final Property<Boolean> buildNativeLibs

    /**
     * Directory containing native test library sources.
     * Default: src/test/resources/native-libs
     */
    final DirectoryProperty nativeLibsSourceDir

    /**
     * Output directory for built native test libraries.
     * Default: build/test/resources/native-libs
     */
    final DirectoryProperty nativeLibsOutputDir

    @Inject
    GtestExtension(ObjectFactory objects) {
        // Source directories
        testSourceDir = objects.directoryProperty()
        mainSourceDir = objects.directoryProperty()
        googleTestHome = objects.directoryProperty()

        // Compiler/linker
        includes = objects.fileCollection()
        configurations = objects.listProperty(Object).convention([])

        // Test behavior
        enableAssertions = objects.property(Boolean).convention(true)
        keepSymbols = objects.property(Boolean).convention(true)
        failFast = objects.property(Boolean).convention(false)
        alwaysRun = objects.property(Boolean).convention(true)

        // Platform-specific
        gtestLibPaths = objects.mapProperty(String, String).convention([:])
        gtestIncludePaths = objects.mapProperty(String, String).convention([:])

        // Build native libs
        buildNativeLibs = objects.property(Boolean).convention(true)
        nativeLibsSourceDir = objects.directoryProperty()
        nativeLibsOutputDir = objects.directoryProperty()
    }
}
