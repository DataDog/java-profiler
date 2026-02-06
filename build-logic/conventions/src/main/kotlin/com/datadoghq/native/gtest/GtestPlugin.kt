// Copyright 2026, Datadog, Inc

package com.datadoghq.native.gtest

import com.datadoghq.native.NativeBuildExtension
import com.datadoghq.native.model.BuildConfiguration
import com.datadoghq.native.model.Platform
import com.datadoghq.native.tasks.NativeCompileTask
import com.datadoghq.native.tasks.NativeLinkExecutableTask
import com.datadoghq.native.util.PlatformUtils
import org.gradle.api.Plugin
import org.gradle.api.Project
import org.gradle.api.tasks.Exec
import java.io.File

/**
 * Gradle plugin for Google Test integration in C++ projects.
 *
 * This plugin automatically creates compilation, linking, and execution tasks for Google Test
 * tests across multiple build configurations. It handles platform-specific differences (macOS, Linux)
 * and integrates with the NativeBuildPlugin's BuildConfiguration model.
 *
 * For each test file in the test source directory, the plugin creates:
 * - compileGtest{Config}_{TestName} - Compile all main sources + test file
 * - linkGtest{Config}_{TestName} - Link test executable with gtest libraries
 * - gtest{Config}_{TestName} - Execute the test
 *
 * Aggregation tasks:
 * - gtest{Config} - Run all tests for a specific configuration (e.g., gtestDebug)
 * - gtest - Run all tests across all configurations
 *
 * Usage:
 * ```kotlin
 * plugins {
 *     id("com.datadoghq.native-build")
 *     id("com.datadoghq.gtest")
 * }
 *
 * gtest {
 *     testSourceDir.set(layout.projectDirectory.dir("src/test/cpp"))
 *     mainSourceDir.set(layout.projectDirectory.dir("src/main/cpp"))
 *     includes.from("src/main/cpp", "${javaHome}/include")
 * }
 * ```
 */
class GtestPlugin : Plugin<Project> {

    override fun apply(project: Project) {
        // Create extension
        val extension = project.extensions.create("gtest", GtestExtension::class.java)

        // Register tasks after project evaluation
        project.afterEvaluate {
            // Check if testSourceDir is set
            if (!extension.testSourceDir.isPresent) {
                project.logger.warn("WARNING: gtest.testSourceDir not configured - skipping Google Test tasks")
                return@afterEvaluate
            }

            // Get configurations from NativeBuildExtension
            val nativeBuildExtension = project.extensions.findByType(NativeBuildExtension::class.java)
            if (nativeBuildExtension == null) {
                project.logger.warn("WARNING: NativeBuildExtension not found - apply com.datadoghq.native-build plugin first")
                return@afterEvaluate
            }

            val activeConfigs = nativeBuildExtension.getActiveConfigurations(
                PlatformUtils.currentPlatform,
                PlatformUtils.currentArchitecture
            )

            if (activeConfigs.isEmpty()) {
                project.logger.warn("WARNING: No active build configurations - skipping Google Test tasks")
                return@afterEvaluate
            }

            // Check if gtest is available
            val hasGtest = checkGtestAvailable()
            if (!hasGtest) {
                project.logger.warn("WARNING: Google Test not found - skipping native tests")
            }

            // Create buildNativeLibs task (Linux only)
            if (extension.buildNativeLibs.get()) {
                createBuildNativeLibsTask(project, extension, hasGtest)
            }

            // Create master aggregation task
            val gtestAll = createMasterAggregationTask(project, hasGtest)

            // Create tasks for each active configuration
            activeConfigs.forEach { config ->
                createConfigTasks(project, extension, config, hasGtest, gtestAll)
            }
        }
    }

    private fun checkGtestAvailable(): Boolean {
        // Check common gtest locations
        val locations = when (PlatformUtils.currentPlatform) {
            Platform.MACOS -> listOf(
                "/opt/homebrew/opt/googletest",
                "/usr/local/opt/googletest"
            )
            Platform.LINUX -> listOf(
                "/usr/include/gtest",
                "/usr/local/include/gtest"
            )
        }
        return locations.any { File(it).exists() }
    }

    private fun createBuildNativeLibsTask(project: Project, extension: GtestExtension, hasGtest: Boolean) {
        project.tasks.register("buildNativeLibs") {
            group = "build"
            description = "Build the native libs for the Google Tests"

            onlyIf {
                hasGtest &&
                !project.hasProperty("skip-native") &&
                !project.hasProperty("skip-gtest") &&
                PlatformUtils.currentPlatform == Platform.LINUX &&
                extension.nativeLibsSourceDir.isPresent &&
                extension.nativeLibsOutputDir.isPresent
            }

            val srcDir = if (extension.nativeLibsSourceDir.isPresent) {
                extension.nativeLibsSourceDir.get().asFile
            } else {
                project.file("src/test/resources/native-libs")
            }
            val targetDir = if (extension.nativeLibsOutputDir.isPresent) {
                extension.nativeLibsOutputDir.get().asFile
            } else {
                project.file("build/test/resources/native-libs")
            }

            doLast {
                if (!srcDir.exists()) {
                    project.logger.info("Native libs source directory does not exist: $srcDir")
                    return@doLast
                }

                srcDir.listFiles()?.filter { it.isDirectory }?.forEach { dir ->
                    val libName = dir.name
                    val libDir = File("$targetDir/$libName")
                    val libSrcDir = File("$srcDir/$libName")

                    project.exec {
                        commandLine("sh", "-c", """
                            echo "Processing library: $libName @ $libSrcDir"
                            mkdir -p $libDir
                            cd $libSrcDir
                            make TARGET_DIR=$libDir
                        """.trimIndent())
                    }
                }
            }

            inputs.files(project.fileTree(srcDir))
            outputs.dir(targetDir)
        }
    }

    private fun createMasterAggregationTask(project: Project, hasGtest: Boolean): org.gradle.api.tasks.TaskProvider<*> {
        return project.tasks.register("gtest") {
            group = "verification"
            description = "Run all Google Tests for all build configurations of the library"

            onlyIf {
                hasGtest &&
                !project.hasProperty("skip-tests") &&
                !project.hasProperty("skip-native") &&
                !project.hasProperty("skip-gtest")
            }
        }
    }

    private fun createConfigTasks(
        project: Project,
        extension: GtestExtension,
        config: BuildConfiguration,
        hasGtest: Boolean,
        gtestAll: org.gradle.api.tasks.TaskProvider<*>
    ) {
        // Find compiler
        val compiler = findCompiler(project)

        // Build include paths - combine extension includes with gtest-specific includes
        val includeFiles = extension.includes.plus(project.files(getGtestIncludes(extension)))

        // Adjust compiler args
        val gtestCompilerArgs = adjustCompilerArgs(config.compilerArgs.get(), extension)

        // Adjust linker args
        val gtestLinkerArgs = adjustLinkerArgs(config)

        // Create per-config aggregation task
        val configName = config.name.replaceFirstChar { it.uppercase() }
        val gtestConfigTask = project.tasks.register("gtest$configName") {
            group = "verification"
            description = "Run all Google Tests for the ${config.name} build of the library"
        }

        // Discover and create tasks for each test file
        val testDir = extension.testSourceDir.get().asFile
        if (!testDir.exists()) {
            project.logger.info("Test source directory does not exist: $testDir")
            return
        }

        testDir.listFiles()?.filter { it.name.endsWith(".cpp") }?.forEach { testFile ->
            val testName = testFile.nameWithoutExtension

            // Create compile task
            val compileTask = createCompileTask(
                project, extension, config, testFile, testName,
                compiler, gtestCompilerArgs, includeFiles, hasGtest
            )

            // Create link task
            val linkTask = createLinkTask(
                project, config, testName, compiler, gtestLinkerArgs,
                compileTask, hasGtest, extension
            )

            // Create execute task
            val executeTask = createExecuteTask(
                project, extension, config, testName, linkTask, hasGtest
            )

            // Wire up dependencies
            gtestConfigTask.configure { dependsOn(executeTask) }
            gtestAll.configure { dependsOn(executeTask) }
        }
    }

    private fun createCompileTask(
        project: Project,
        extension: GtestExtension,
        config: BuildConfiguration,
        testFile: File,
        testName: String,
        compiler: String,
        compilerArgs: List<String>,
        includeFiles: org.gradle.api.file.FileCollection,
        hasGtest: Boolean
    ): org.gradle.api.tasks.TaskProvider<NativeCompileTask> {
        val configName = config.name.replaceFirstChar { it.uppercase() }

        return project.tasks.register("compileGtest${configName}_$testName", NativeCompileTask::class.java) {
            onlyIf {
                hasGtest &&
                !project.hasProperty("skip-tests") &&
                !project.hasProperty("skip-native") &&
                !project.hasProperty("skip-gtest")
            }
            group = "build"
            description = "Compile the Google Test $testName for the ${config.name} build of the library"

            this.compiler.set(compiler)
            this.compilerArgs.set(compilerArgs)

            // Combine main sources and test file
            sources.from(
                project.fileTree(extension.mainSourceDir.get()) { include("**/*.cpp") },
                testFile
            )

            includes.from(includeFiles)
            objectFileDir.set(project.file("${project.layout.buildDirectory.get()}/obj/gtest/${config.name}/$testName"))
        }
    }

    private fun createLinkTask(
        project: Project,
        config: BuildConfiguration,
        testName: String,
        compiler: String,
        linkerArgs: List<String>,
        compileTask: org.gradle.api.tasks.TaskProvider<NativeCompileTask>,
        hasGtest: Boolean,
        extension: GtestExtension
    ): org.gradle.api.tasks.TaskProvider<NativeLinkExecutableTask> {
        val configName = config.name.replaceFirstChar { it.uppercase() }
        val binary = project.file("${project.layout.buildDirectory.get()}/bin/gtest/${config.name}_$testName/$testName")

        return project.tasks.register("linkGtest${configName}_$testName", NativeLinkExecutableTask::class.java) {
            onlyIf {
                hasGtest &&
                !project.hasProperty("skip-tests") &&
                !project.hasProperty("skip-native") &&
                !project.hasProperty("skip-gtest")
            }
            dependsOn(compileTask)
            group = "build"
            description = "Link the Google Test $testName for the ${config.name} build of the library"

            linker.set(compiler)
            this.linkerArgs.set(linkerArgs)
            objectFiles.from(
                project.fileTree("${project.layout.buildDirectory.get()}/obj/gtest/${config.name}/$testName") {
                    include("*.o")
                }
            )
            outputFile.set(binary)

            // Add gtest library paths
            when (PlatformUtils.currentPlatform) {
                Platform.MACOS -> {
                    val gtestPath = if (extension.googleTestHome.isPresent) {
                        extension.googleTestHome.get().asFile.absolutePath
                    } else {
                        "/opt/homebrew/opt/googletest"
                    }
                    libPath("$gtestPath/lib")
                }
                Platform.LINUX -> {
                    // Use system paths
                }
            }

            // Add gtest libraries
            lib("gtest", "gtest_main", "gmock", "gmock_main", "dl", "pthread", "m")
            if (PlatformUtils.currentPlatform == Platform.LINUX) {
                lib("rt")
            }
        }
    }

    private fun createExecuteTask(
        project: Project,
        extension: GtestExtension,
        config: BuildConfiguration,
        testName: String,
        linkTask: org.gradle.api.tasks.TaskProvider<NativeLinkExecutableTask>,
        hasGtest: Boolean
    ): org.gradle.api.tasks.TaskProvider<Exec> {
        val configName = config.name.replaceFirstChar { it.uppercase() }
        val binary = project.file("${project.layout.buildDirectory.get()}/bin/gtest/${config.name}_$testName/$testName")

        return project.tasks.register("gtest${configName}_$testName", Exec::class.java) {
            onlyIf {
                hasGtest &&
                !project.hasProperty("skip-tests") &&
                !project.hasProperty("skip-native") &&
                !project.hasProperty("skip-gtest")
            }
            dependsOn(linkTask)

            // Add dependency on buildNativeLibs if it exists (Linux only)
            if (PlatformUtils.currentPlatform == Platform.LINUX && extension.buildNativeLibs.get()) {
                val buildNativeLibsTask = project.tasks.findByName("buildNativeLibs")
                if (buildNativeLibsTask != null) {
                    dependsOn(buildNativeLibsTask)
                }
            }

            group = "verification"
            description = "Run the Google Test $testName for the ${config.name} build of the library"

            executable = binary.absolutePath

            // Set test environment variables from configuration
            config.testEnvironment.get().forEach { (key, value) ->
                environment(key, value)
            }

            inputs.files(binary)

            // Always re-run tests if configured
            if (extension.alwaysRun.get()) {
                outputs.upToDateWhen { false }
            }

            // When failFast is enabled, stop build on test failures (don't ignore exit value)
            isIgnoreExitValue = !extension.failFast.get()
        }
    }

    private fun findCompiler(project: Project): String = PlatformUtils.findCompiler(project)

    private fun getGtestIncludes(extension: GtestExtension): List<File> {
        return when (PlatformUtils.currentPlatform) {
            Platform.MACOS -> {
                val gtestPath = if (extension.googleTestHome.isPresent) {
                    extension.googleTestHome.get().asFile.absolutePath
                } else {
                    "/opt/homebrew/opt/googletest"
                }
                listOf(File("$gtestPath/include"))
            }
            Platform.LINUX -> emptyList() // System includes
        }
    }

    private fun adjustCompilerArgs(baseArgs: List<String>, extension: GtestExtension): List<String> {
        val args = baseArgs.toMutableList()

        // Remove -std=c++17 so we can re-add it consistently
        args.removeAll { it.startsWith("-std=") }

        // Remove -DNDEBUG if assertions are enabled
        if (extension.enableAssertions.get()) {
            args.removeAll { it == "-DNDEBUG" }
        }

        // Re-add C++17 standard
        args.add("-std=c++17")

        // Add musl define if needed
        if (PlatformUtils.currentPlatform == Platform.LINUX && PlatformUtils.isMusl()) {
            args.add("-D__musl__")
        }

        return args
    }

    private fun adjustLinkerArgs(config: BuildConfiguration): List<String> {
        val args = mutableListOf<String>()

        // Add base linker args
        args.addAll(config.linkerArgs.get())

        return args
    }
}
