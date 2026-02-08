
package com.datadoghq.profiler

import org.gradle.api.Plugin
import org.gradle.api.Project
import org.gradle.api.tasks.compile.JavaCompile

/**
 * Convention plugin for Java compilation settings.
 *
 * Applies standard Java compilation options across all subprojects:
 * - Java 8 release target for broad JVM compatibility
 *
 * Requires JDK 9+ for building (uses --release flag).
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
        val javaVersion = System.getProperty("java.specification.version")?.toDoubleOrNull() ?: 0.0

        project.tasks.withType(JavaCompile::class.java).configureEach {
            if (javaVersion >= 9) {
                // JDK 9+ supports --release flag which handles source, target, and boot classpath
                options.compilerArgs.addAll(listOf("--release", "8"))
            } else {
                // Fallback for JDK 8 (not recommended for building)
                sourceCompatibility = "8"
                targetCompatibility = "8"
                project.logger.warn("Building with JDK 8 is not recommended. Use JDK 11+ with --release 8 for better compatibility.")
            }
        }
    }
}
