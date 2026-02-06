// Copyright 2026, Datadog, Inc

package com.datadoghq.native

import com.datadoghq.native.config.ConfigurationPresets
import com.datadoghq.native.model.Architecture
import com.datadoghq.native.model.Platform
import com.datadoghq.native.util.PlatformUtils
import org.gradle.api.Plugin
import org.gradle.api.Project

/**
 * Gradle plugin that provides native C++ build configuration management.
 *
 * This plugin:
 * 1. Creates a `nativeBuild` extension for configuring build configurations
 * 2. Automatically generates compile, link, and assemble tasks for each configuration
 * 3. Provides standard configuration presets (release, debug, asan, tsan, fuzzer)
 * 4. Handles platform-specific compiler and linker flags
 *
 * Usage example:
 * ```
 * plugins {
 *     id("com.datadoghq.native-build")
 * }
 *
 * nativeBuild {
 *     buildConfigurations {
 *         register("release") {
 *             platform.set(Platform.LINUX)
 *             architecture.set(Architecture.X64)
 *             compilerArgs.set(listOf("-O3", "-DNDEBUG"))
 *         }
 *     }
 * }
 * ```
 */
class NativeBuildPlugin : Plugin<Project> {
    override fun apply(project: Project) {
        // Create the extension
        val extension = project.extensions.create(
            "nativeBuild",
            NativeBuildExtension::class.java,
            project,
            project.objects
        )

        // Setup standard configurations after project evaluation
        project.afterEvaluate {
            setupStandardConfigurations(project, extension)
            createTasks(project, extension)
        }
    }

    private fun setupStandardConfigurations(project: Project, extension: NativeBuildExtension) {
        val currentPlatform = PlatformUtils.currentPlatform
        val currentArch = PlatformUtils.currentArchitecture
        val version = extension.version.get()
        val rootDir = project.rootDir
        val compiler = findCompiler(project)

        // Only create configurations if none are explicitly defined
        if (extension.buildConfigurations.isEmpty()) {
            project.logger.lifecycle("Setting up standard build configurations for $currentPlatform-$currentArch")
            project.logger.lifecycle("Using compiler: $compiler")

            // Create standard configurations for current platform
            extension.buildConfigurations.apply {
                register("release") {
                    ConfigurationPresets.configureRelease(this, currentPlatform, currentArch, version, rootDir)
                }
                register("debug") {
                    ConfigurationPresets.configureDebug(this, currentPlatform, currentArch, version, rootDir)
                }
                register("asan") {
                    ConfigurationPresets.configureAsan(this, currentPlatform, currentArch, version, rootDir, compiler)
                }
                register("tsan") {
                    ConfigurationPresets.configureTsan(this, currentPlatform, currentArch, version, rootDir, compiler)
                }
                register("fuzzer") {
                    ConfigurationPresets.configureFuzzer(this, currentPlatform, currentArch, version, rootDir)
                }
            }
        }
    }

    private fun createTasks(project: Project, extension: NativeBuildExtension) {
        val currentPlatform = PlatformUtils.currentPlatform
        val currentArch = PlatformUtils.currentArchitecture

        // Get active configurations for current platform
        val activeConfigs = extension.getActiveConfigurations(currentPlatform, currentArch)

        project.logger.lifecycle("Active configurations: ${activeConfigs.map { it.name }.joinToString(", ")}")

        // Create tasks for each active configuration
        activeConfigs.forEach { config ->
            createConfigurationTasks(project, extension, config)
        }

        // Create aggregation tasks
        createAggregationTasks(project, activeConfigs)
    }

    private fun createConfigurationTasks(
        project: Project,
        extension: NativeBuildExtension,
        config: com.datadoghq.native.model.BuildConfiguration
    ) {
        val configName = config.capitalizedName()
        val platform = config.platform.get()
        val arch = config.architecture.get()

        // Define paths
        val objDir = project.file("build/obj/main/${config.name}")
        val libDir = project.file("build/lib/main/${config.name}/$platform/$arch")
        val libName = "libjavaProfiler.${PlatformUtils.sharedLibExtension()}"
        val outputLib = project.file("$libDir/$libName")

        // Create compile task
        val compileTask = project.tasks.register("compile$configName", com.datadoghq.native.tasks.NativeCompileTask::class.java) {
            group = "build"
            description = "Compiles C++ sources for ${config.name} configuration"

            // Find compiler
            val compilerPath = findCompiler(project)
            compiler.set(compilerPath)
            compilerArgs.set(config.compilerArgs.get())

            // Set sources - default to src/main/cpp
            val srcDirs = extension.cppSourceDirs.get()
            sources.from(srcDirs.map { dir ->
                project.fileTree(dir) {
                    include("**/*.cpp", "**/*.cc", "**/*.c")
                }
            })

            // Set includes - default + JNI
            val includeList = extension.includeDirectories.get().toMutableList()
            includeList.addAll(PlatformUtils.jniIncludePaths())
            includes.from(includeList)

            objectFileDir.set(objDir)
        }

        // Create link task
        val linkTask = project.tasks.register("link$configName", com.datadoghq.native.tasks.NativeLinkTask::class.java) {
            group = "build"
            description = "Links ${config.name} shared library"
            dependsOn(compileTask)

            val compilerPath = findCompiler(project)
            linker.set(compilerPath)
            linkerArgs.set(config.linkerArgs.get())
            objectFiles.from(project.fileTree(objDir) {
                include("*.o")
            })
            outputFile.set(outputLib)

            // Enable debug symbol extraction for release builds
            if (config.name == "release") {
                extractDebugSymbols.set(true)
                stripSymbols.set(true)
                debugSymbolsDir.set(project.file("$libDir/debug"))
            }
        }

        // Create assemble task
        val assembleTask = project.tasks.register("assemble$configName") {
            group = "build"
            description = "Assembles ${config.name} configuration"
            dependsOn(linkTask)
        }

        project.logger.debug("Created tasks for configuration: ${config.name}")
    }

    private fun findCompiler(project: Project): String {
        // Check for forced compiler override via Gradle property (-Pnative.forceCompiler=clang++)
        val forcedCompiler = project.findProperty("native.forceCompiler") as? String
        if (forcedCompiler != null) {
            project.logger.lifecycle("Using forced compiler from -Pnative.forceCompiler: $forcedCompiler")
            // Verify the forced compiler is available
            if (PlatformUtils.isCompilerAvailable(forcedCompiler)) {
                return forcedCompiler
            } else {
                throw org.gradle.api.GradleException(
                    "Forced compiler '$forcedCompiler' is not available. " +
                    "Please install it or remove the -Pnative.forceCompiler property."
                )
            }
        }

        // Auto-detect: Try to find clang++ or g++ on PATH
        val compilers = listOf("clang++", "g++", "c++")
        for (compiler in compilers) {
            if (PlatformUtils.isCompilerAvailable(compiler)) {
                project.logger.lifecycle("Auto-detected compiler: $compiler")
                return compiler
            }
        }

        // No compiler found
        throw org.gradle.api.GradleException(
            "No C++ compiler found. Please install clang++ or g++, " +
            "or specify one with -Pnative.forceCompiler=/path/to/compiler"
        )
    }

    private fun createAggregationTasks(
        project: Project,
        activeConfigs: List<com.datadoghq.native.model.BuildConfiguration>
    ) {
        // Create assembleAll task that depends on all assemble tasks
        project.tasks.register("assembleAll") {
            group = "build"
            description = "Assembles all active build configurations"
            // Depend on all individual assemble tasks
            activeConfigs.forEach { config ->
                val configName = config.capitalizedName()
                dependsOn("assemble$configName")
            }
        }

        project.logger.lifecycle("Created assembleAll task")
    }
}
