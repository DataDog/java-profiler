// Copyright 2026, Datadog, Inc

package com.datadoghq.java.versionedsources

import org.gradle.api.JavaVersion
import org.gradle.api.Plugin
import org.gradle.api.Project
import org.gradle.api.plugins.JavaPlugin
import org.gradle.api.tasks.SourceSetContainer
import org.gradle.api.tasks.compile.JavaCompile
import org.gradle.jvm.toolchain.JavaLanguageVersion
import org.gradle.jvm.toolchain.JavaToolchainService

/**
 * Gradle plugin for managing versioned source sets.
 *
 * This plugin simplifies compiling Java version-specific code by:
 * 1. Creating versioned source sets automatically
 * 2. Configuring compilation with correct --release flags and toolchains
 * 3. Setting up classpath dependencies (version N depends on main)
 * 4. Providing utilities for JAR task configuration
 *
 * Classes are added to the JAR root (not META-INF/versions/) for runtime
 * selection via Class.forName() based on Java version.
 *
 * Usage:
 * ```kotlin
 * plugins {
 *     java
 *     id("com.datadoghq.versioned-sources")
 * }
 *
 * versionedSources {
 *     versions {
 *         register("java9") {
 *             release.set(9)
 *             minToolchainVersion.set(11)
 *         }
 *     }
 * }
 * ```
 */
class VersionedSourcesPlugin : Plugin<Project> {

    override fun apply(project: Project) {
        // Ensure Java plugin is applied
        project.pluginManager.apply(JavaPlugin::class.java)

        // Create extension
        val extension = project.extensions.create(
            "versionedSources",
            VersionedSourcesExtension::class.java,
            project,
            project.objects
        )

        // Configure after project evaluation to access all registered versions
        project.afterEvaluate {
            configureVersionedSourceSets(project, extension)
            configureCompilationTasks(project, extension)
        }
    }

    private fun configureVersionedSourceSets(
        project: Project,
        extension: VersionedSourcesExtension
    ) {
        val sourceSets = project.extensions.getByType(SourceSetContainer::class.java)

        extension.versions.forEach { version ->
            // Create source set if it doesn't exist
            val sourceSet = sourceSets.maybeCreate(version.name)

            // Configure source directory
            val srcDir = if (version.sourceDir.isPresent) {
                version.sourceDir.get().asFile.path
            } else {
                "src/main/${version.name}"
            }

            sourceSet.java.srcDirs(srcDir)

            project.logger.info(
                "VersionedSources: Created source set '${version.name}' with source dir: $srcDir"
            )
        }
    }

    private fun configureCompilationTasks(
        project: Project,
        extension: VersionedSourcesExtension
    ) {
        val sourceSets = project.extensions.getByType(SourceSetContainer::class.java)
        val mainSourceSet = sourceSets.getByName("main")
        val javaToolchains = project.extensions.getByType(JavaToolchainService::class.java)

        extension.versions.forEach { version ->
            val compileTask = project.tasks.findByName(version.compileTaskName) as? JavaCompile
                ?: return@forEach

            val releaseVersion = version.release.get()
            val minToolchain = version.minToolchainVersion.orNull ?: releaseVersion

            // Determine actual toolchain version to use (current JDK if >= minToolchain)
            val currentJdk = JavaVersion.current().majorVersion.toInt()
            val toolchainVersion = if (currentJdk >= minToolchain) currentJdk else minToolchain

            compileTask.apply {
                // Set toolchain for compilation
                javaCompiler.set(
                    javaToolchains.compilerFor {
                        languageVersion.set(JavaLanguageVersion.of(toolchainVersion))
                    }
                )

                // Set release flag for target version
                options.release.set(releaseVersion)

                // Set classpath to include main source set output + compile dependencies
                classpath = mainSourceSet.output + project.configurations.getByName("compileClasspath")

                // Depend on main compilation
                dependsOn(project.tasks.named("compileJava"))
            }

            project.logger.info(
                "VersionedSources: Configured ${version.compileTaskName}: " +
                    "release=$releaseVersion, toolchain=$toolchainVersion"
            )
        }
    }
}
