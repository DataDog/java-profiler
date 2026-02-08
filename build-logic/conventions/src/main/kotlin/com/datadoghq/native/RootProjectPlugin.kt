// Copyright 2026, Datadog, Inc

package com.datadoghq.native

import com.datadoghq.native.config.ConfigurationPresets
import com.datadoghq.native.util.PlatformUtils
import org.gradle.api.GradleException
import org.gradle.api.Plugin
import org.gradle.api.Project

/**
 * Gradle plugin that provides native build configuration access to the root project.
 *
 * This plugin creates a `nativeBuild` extension on the root project that exposes
 * standard build configurations (release, debug, asan, tsan, fuzzer) to all subprojects.
 * This allows subprojects to query and access build configurations in a type-safe manner.
 *
 * Usage example:
 * ```
 * // In root build.gradle.kts
 * plugins {
 *     id("com.datadoghq.native-root")
 * }
 *
 * // In subproject build.gradle.kts
 * val nativeBuildExt = rootProject.extensions.getByType(NativeBuildExtension::class.java)
 * val activeConfigs = nativeBuildExt.getActiveConfigurations(currentPlatform, currentArch)
 * ```
 */
class RootProjectPlugin : Plugin<Project> {
    override fun apply(project: Project) {
        // Only apply to root project
        if (project != project.rootProject) {
            throw GradleException("RootProjectPlugin must be applied to root project only")
        }

        // Create nativeBuild extension on root
        val extension = project.extensions.create(
            "nativeBuild",
            NativeBuildExtension::class.java,
            project,
            project.objects
        )

        // Setup standard configurations after project evaluation
        project.afterEvaluate {
            setupStandardConfigurationsIfNeeded(project, extension)
        }
    }

    private fun setupStandardConfigurationsIfNeeded(project: Project, extension: NativeBuildExtension) {
        // Only create configurations if none are explicitly defined
        if (extension.buildConfigurations.isEmpty()) {
            val currentPlatform = PlatformUtils.currentPlatform
            val currentArch = PlatformUtils.currentArchitecture
            val version = extension.version.get()
            val rootDir = project.rootDir
            val compiler = PlatformUtils.findCompiler(project)

            project.logger.lifecycle("Setting up standard build configurations for $currentPlatform-$currentArch")
            project.logger.lifecycle("Using compiler: $compiler")

            // Create standard configurations for current platform
            extension.buildConfigurations.apply {
                register("release") {
                    ConfigurationPresets.configureRelease(this, currentPlatform, currentArch, version)
                }
                register("debug") {
                    ConfigurationPresets.configureDebug(this, currentPlatform, currentArch, version)
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

            val activeConfigs = extension.getActiveConfigurations(currentPlatform, currentArch)
            project.logger.lifecycle("Active configurations: ${activeConfigs.map { it.name }.joinToString(", ")}")
        }
    }
}
