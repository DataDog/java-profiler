
package com.datadoghq.native.scanbuild

import com.datadoghq.native.model.Platform
import com.datadoghq.native.util.PlatformUtils
import org.gradle.api.Plugin
import org.gradle.api.Project
import org.gradle.api.tasks.Exec

/**
 * Gradle plugin that provides clang static analysis via scan-build.
 *
 * This plugin creates a `scanBuild` task that runs the clang static analyzer
 * on the C++ codebase using a Makefile-based build.
 *
 * Usage:
 * ```kotlin
 * plugins {
 *     id("com.datadoghq.scanbuild")
 * }
 *
 * scanBuild {
 *     makefileDir.set(layout.projectDirectory.dir("src/test/make"))
 *     outputDir.set(layout.buildDirectory.dir("reports/scan-build"))
 *     analyzer.set("/usr/bin/clang++")
 *     parallelJobs.set(4)
 * }
 * ```
 */
class ScanBuildPlugin : Plugin<Project> {
    override fun apply(project: Project) {
        // Create the extension
        val extension = project.extensions.create(
            "scanBuild",
            ScanBuildExtension::class.java,
            project
        )

        // Create the task after project evaluation
        project.afterEvaluate {
            createScanBuildTask(project, extension)
        }
    }

    private fun createScanBuildTask(project: Project, extension: ScanBuildExtension) {
        // Only create the task on Linux (scan-build is typically Linux-only in CI)
        if (PlatformUtils.currentPlatform != Platform.LINUX) {
            project.logger.info("Skipping scanBuild task - only available on Linux")
            return
        }

        // Check if scan-build is available
        if (!isScanBuildAvailable()) {
            project.logger.warn("scan-build not found in PATH - scanBuild task will fail if executed")
        }

        val makefileDir = extension.makefileDir.get().asFile
        val outputDir = extension.outputDir.get().asFile
        val analyzer = extension.analyzer.get()
        val parallelJobs = extension.parallelJobs.get()
        val makeTargets = extension.makeTargets.get()

        val scanBuildTask = project.tasks.register("scanBuild", Exec::class.java)
        scanBuildTask.configure {
            group = "verification"
            description = "Run clang static analyzer via scan-build"

            workingDir(makefileDir)

            // Build command line as a single list to avoid vararg ambiguity
            val command = mutableListOf(
                "scan-build",
                "-o", outputDir.absolutePath,
                "--force-analyze-debug-code",
                "--use-analyzer", analyzer,
                "make", "-j$parallelJobs"
            )
            command.addAll(makeTargets)
            commandLine(command)

            // Ensure output directory exists
            doFirst {
                outputDir.mkdirs()
            }
        }
    }

    private fun isScanBuildAvailable(): Boolean {
        return try {
            val process = ProcessBuilder("which", "scan-build")
                .redirectErrorStream(true)
                .start()
            process.waitFor() == 0
        } catch (e: Exception) {
            false
        }
    }
}
