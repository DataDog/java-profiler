// Copyright 2026, Datadog, Inc

package com.datadoghq.native.gtest

import com.datadoghq.native.model.BuildConfiguration
import com.datadoghq.native.model.Platform
import com.datadoghq.native.tasks.NativeCompileTask
import com.datadoghq.native.tasks.NativeLinkExecutableTask
import com.datadoghq.native.util.PlatformUtils
import org.gradle.api.Project
import org.gradle.api.file.FileCollection
import org.gradle.api.tasks.Exec
import org.gradle.api.tasks.TaskProvider
import java.io.File

/**
 * Builder for creating Google Test compile, link, and execute tasks.
 *
 * Groups related configuration and provides a fluent API for task creation.
 *
 * Usage:
 * ```kotlin
 * GtestTaskBuilder(project, extension, config)
 *     .forTest(testFile)
 *     .withCompiler(compiler)
 *     .withIncludes(includeFiles)
 *     .onlyIf { hasGtest }
 *     .build()
 * ```
 */
class GtestTaskBuilder(
    private val project: Project,
    private val extension: GtestExtension,
    private val config: BuildConfiguration
) {
    private lateinit var testFile: File
    private lateinit var testName: String
    private lateinit var compiler: String
    private lateinit var includeFiles: FileCollection
    private var hasGtest: Boolean = true

    private val configName: String get() = config.capitalizedName()

    /**
     * Set the test file to build tasks for.
     */
    fun forTest(file: File): GtestTaskBuilder {
        testFile = file
        testName = file.nameWithoutExtension
        return this
    }

    /**
     * Set the compiler to use.
     */
    fun withCompiler(comp: String): GtestTaskBuilder {
        compiler = comp
        return this
    }

    /**
     * Set include directories.
     */
    fun withIncludes(includes: FileCollection): GtestTaskBuilder {
        includeFiles = includes
        return this
    }

    /**
     * Set whether gtest is available.
     */
    fun onlyIfGtest(available: Boolean): GtestTaskBuilder {
        hasGtest = available
        return this
    }

    /**
     * Build all tasks (compile, link, execute) and return the execute task provider.
     */
    fun build(): TaskProvider<Exec> {
        val compileTask = buildCompileTask()
        val linkTask = buildLinkTask(compileTask)
        return buildExecuteTask(linkTask)
    }

    private fun buildCompileTask(): TaskProvider<NativeCompileTask> {
        val compilerArgs = adjustCompilerArgs()
        val objDir = project.file("${project.layout.buildDirectory.get()}/obj/gtest/${config.name}/$testName")

        return project.tasks.register("compileGtest${configName}_$testName", NativeCompileTask::class.java) {
            onlyIf { hasGtest && !skipConditions() }
            group = "build"
            description = "Compile the Google Test $testName for the ${config.name} build"

            this.compiler.set(this@GtestTaskBuilder.compiler)
            this.compilerArgs.set(compilerArgs)

            sources.from(
                project.fileTree(extension.mainSourceDir.get()) { include("**/*.cpp") },
                testFile
            )
            includes.from(includeFiles)
            objectFileDir.set(objDir)
        }
    }

    private fun buildLinkTask(compileTask: TaskProvider<NativeCompileTask>): TaskProvider<NativeLinkExecutableTask> {
        val linkerArgs = config.linkerArgs.get()
        val objDir = project.file("${project.layout.buildDirectory.get()}/obj/gtest/${config.name}/$testName")
        val binary = project.file("${project.layout.buildDirectory.get()}/bin/gtest/${config.name}_$testName/$testName")

        return project.tasks.register("linkGtest${configName}_$testName", NativeLinkExecutableTask::class.java) {
            onlyIf { hasGtest && !skipConditions() }
            dependsOn(compileTask)
            group = "build"
            description = "Link the Google Test $testName for the ${config.name} build"

            linker.set(compiler)
            this.linkerArgs.set(linkerArgs)
            objectFiles.from(project.fileTree(objDir) { include("*.o") })
            outputFile.set(binary)

            // Add gtest library paths
            when (PlatformUtils.currentPlatform) {
                Platform.MACOS -> {
                    val gtestPath = gtestHomePath()
                    libPath("$gtestPath/lib")
                }
                Platform.LINUX -> { /* System paths */ }
            }

            // Add gtest libraries
            lib("gtest", "gtest_main", "gmock", "gmock_main", "dl", "pthread", "m")
            if (PlatformUtils.currentPlatform == Platform.LINUX) {
                lib("rt")
            }
        }
    }

    private fun buildExecuteTask(linkTask: TaskProvider<NativeLinkExecutableTask>): TaskProvider<Exec> {
        val binary = project.file("${project.layout.buildDirectory.get()}/bin/gtest/${config.name}_$testName/$testName")

        return project.tasks.register("gtest${configName}_$testName", Exec::class.java) {
            onlyIf { hasGtest && !skipConditions() }
            dependsOn(linkTask)

            // Add dependency on buildNativeLibs if it exists (Linux only)
            if (PlatformUtils.currentPlatform == Platform.LINUX && extension.buildNativeLibs.get()) {
                project.tasks.findByName("buildNativeLibs")?.let { dependsOn(it) }
            }

            group = "verification"
            description = "Run the Google Test $testName for the ${config.name} build"

            executable = binary.absolutePath

            // Set test environment variables from configuration
            config.testEnvironment.get().forEach { (key, value) ->
                environment(key, value)
            }

            inputs.files(binary)

            if (extension.alwaysRun.get()) {
                outputs.upToDateWhen { false }
            }

            isIgnoreExitValue = !extension.failFast.get()
        }
    }

    private fun skipConditions(): Boolean {
        return project.hasProperty("skip-tests") ||
               project.hasProperty("skip-native") ||
               project.hasProperty("skip-gtest")
    }

    private fun gtestHomePath(): String {
        return if (extension.googleTestHome.isPresent) {
            extension.googleTestHome.get().asFile.absolutePath
        } else {
            "/opt/homebrew/opt/googletest"
        }
    }

    private fun adjustCompilerArgs(): List<String> {
        val args = config.compilerArgs.get().toMutableList()

        // Remove -std= so we can re-add it consistently
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
}
