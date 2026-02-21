
package com.datadoghq.profiler

import org.gradle.api.Plugin
import org.gradle.api.Project
import org.gradle.api.artifacts.VersionCatalogsExtension
import org.gradle.api.tasks.compile.JavaCompile

/**
 * Convention plugin for Java compilation settings.
 *
 * Applies standard Java compilation options across all subprojects:
 * - Java 8 release target for broad JVM compatibility
 * - Suppresses JDK 21+ deprecation warnings for --release 8
 * - Redirects org.lz4:lz4-java to at.yawk.lz4:lz4-java (community fork)
 *
 * Requires JDK 21+ for building (Gradle 9 requirement).
 * The compiled bytecode targets Java 8 runtime.
 *
 * Usage:
 * ```kotlin
 * plugins {
 *   id("com.datadoghq.java-conventions")
 * }
 * ```
 */
class JavaConventionsPlugin : Plugin<Project> {
    override fun apply(project: Project) {
        project.tasks.withType(JavaCompile::class.java).configureEach {
            // JDK 21+ deprecated --release 8 with warnings; suppress with -Xlint:-options
            // The deprecation is informational - Java 8 targeting still works
            options.compilerArgs.addAll(listOf("--release", "8", "-Xlint:-options"))
        }

        // Redirect org.lz4:lz4-java → at.yawk.lz4:lz4-java (community fork)
        // JMC flightrecorder transitively depends on the old coordinates
        val libs = project.extensions.getByType(VersionCatalogsExtension::class.java).named("libs")
        val lz4Version = libs.findVersion("lz4").orElseThrow().requiredVersion
        project.configurations.all {
            resolutionStrategy.dependencySubstitution {
                substitute(module("org.lz4:lz4-java"))
                    .using(module("at.yawk.lz4:lz4-java:$lz4Version"))
            }
        }
    }
}
