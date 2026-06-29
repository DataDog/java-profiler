
package com.datadoghq.native

import com.datadoghq.native.config.ConfigurationPresets
import com.datadoghq.native.model.Architecture
import com.datadoghq.native.model.BuildConfiguration
import com.datadoghq.native.model.Platform
import com.datadoghq.native.tasks.NativeCompileTask
import com.datadoghq.native.tasks.NativeLinkTask
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

        // Step 3.2.2: read the monolithic Gradle property
        val monolithic = project.hasProperty("monolithic")
        extension.monolithicBuild.set(monolithic)

        // Setup standard configurations after project evaluation
        project.afterEvaluate {
            setupStandardConfigurations(project, extension)
            createTasks(project, extension)
        }
    }

    private fun setupStandardConfigurations(project: Project, extension: NativeBuildExtension) {
        ConfigurationPresets.setupStandardConfigurations(extension, project)
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
        config: BuildConfiguration
    ) {
        val configName = config.capitalizedName()

        // Step 3.2.3: create two compile+link pairs when split mode is active
        val linkTaskNames: List<String>
        if (extension.monolithicBuild.get() || extension.supportCppSourceDirs.get().isEmpty()) {
            linkTaskNames = listOf(
                createCompileLinkPair(project, extension, config, extension.cppSourceDirs.get(), "")
            )
        } else {
            val supportDirs = extension.supportCppSourceDirs.get()
            val allDirs = extension.cppSourceDirs.get()
            val profilerDirs = allDirs.filter { it !in supportDirs }
            val supportLinkName = createCompileLinkPair(project, extension, config, supportDirs, "Support")
            val profilerLinkName = createCompileLinkPair(
                project, extension, config, profilerDirs, "Profiler",
                linkAgainst = "libJavaSupport"
            )
            // Profiler link depends on support library being built first
            project.tasks.named(profilerLinkName, NativeLinkTask::class.java) {
                dependsOn(supportLinkName)
            }
            linkTaskNames = listOf(supportLinkName, profilerLinkName)
        }

        // Create assemble task depending on all link tasks for this config
        project.tasks.register("assemble$configName") {
            group = "build"
            description = "Assembles ${config.name} configuration"
            linkTaskNames.forEach { dependsOn(it) }
        }

        project.logger.debug("Created tasks for configuration: ${config.name}")
    }

    /**
     * Creates a compile + link task pair for the given source directories and suffix.
     *
     * @param suffix  "" for monolithic/default, "Support" or "Profiler" in split mode
     * @param linkAgainst  "libXxx" library name to add as a link-time dependency (with rpath)
     * @return the name of the created link task
     */
    private fun createCompileLinkPair(
        project: Project,
        extension: NativeBuildExtension,
        config: BuildConfiguration,
        sourceDirs: List<String>,
        suffix: String,
        linkAgainst: String? = null
    ): String {
        val configName = config.capitalizedName()
        val platform = config.platform.get()
        val arch = config.architecture.get()

        val libBaseName = if (suffix == "Support") "JavaSupport" else "javaProfiler"
        val libName = "lib$libBaseName.${PlatformUtils.sharedLibExtension()}"

        val objSubDir = if (suffix.isEmpty()) "" else "/${suffix.lowercase()}"
        val objDir = project.file("build/obj/main/${config.name}$objSubDir")
        val libDir = project.file("build/lib/main/${config.name}/$platform/$arch")
        val outputLib = project.file("$libDir/$libName")

        val compileTaskName = "compile${suffix}${configName}"
        val compileTask = project.tasks.register(compileTaskName, NativeCompileTask::class.java) {
            group = "build"
            description = "Compiles C++ sources for ${config.name}${if (suffix.isNotEmpty()) " $suffix" else ""}"

            compiler.set(findCompiler(project))
            compilerArgs.set(config.compilerArgs.get())

            sources.from(sourceDirs.map { dir ->
                project.fileTree(dir) {
                    include("**/*.cpp", "**/*.cc", "**/*.c")
                }
            })

            val includeList = extension.includeDirectories.get().toMutableList()
            includeList.addAll(PlatformUtils.jniIncludePaths())
            includes.from(includeList)

            objectFileDir.set(objDir)
        }

        val linkTaskName = "link${suffix}${configName}"
        project.tasks.register(linkTaskName, NativeLinkTask::class.java) {
            group = "build"
            description = "Links ${config.name}${if (suffix.isNotEmpty()) " $suffix" else ""} shared library"
            dependsOn(compileTask)

            linker.set(findCompiler(project))
            linkerArgs.set(config.linkerArgs.get())
            objectFiles.from(project.fileTree(objDir) { include("*.o") })
            outputFile.set(outputLib)

            if (linkAgainst != null) {
                val libFlag = linkAgainst.removePrefix("lib")
                libraryPaths.add(libDir.absolutePath)
                libraries.add(libFlag)
                when (PlatformUtils.currentPlatform) {
                    Platform.LINUX -> runtimePaths.add("\$ORIGIN")
                    Platform.MACOS -> runtimePaths.add("@loader_path")
                }
            }

            if (config.name == "release") {
                extractDebugSymbols.set(true)
                stripSymbols.set(true)
                debugSymbolsDir.set(project.file("$libDir/debug"))
            }
        }

        return linkTaskName
    }

    private fun findCompiler(project: Project): String = PlatformUtils.findCompiler(project)

    private fun createAggregationTasks(
        project: Project,
        activeConfigs: List<BuildConfiguration>
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
