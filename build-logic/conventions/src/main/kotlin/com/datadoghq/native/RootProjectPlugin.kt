
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
        ConfigurationPresets.setupStandardConfigurations(extension, project)
    }
}
