// Copyright 2026, Datadog, Inc

package com.datadoghq.java.versionedsources

import org.gradle.api.Named
import org.gradle.api.file.DirectoryProperty
import org.gradle.api.provider.Property
import javax.inject.Inject

/**
 * Represents a versioned source set for Java version-specific code.
 *
 * Each instance defines a Java version-specific source directory that contains
 * classes compiled with a specific Java release target. These classes are selected
 * at runtime via Class.forName() based on the running JVM version.
 *
 * @property name The source set name (e.g., "java9", "java11")
 */
abstract class VersionedSourceSet @Inject constructor(
    private val name: String
) : Named {

    /**
     * The Java release version (e.g., 9, 11, 17, 21).
     * Used with javac --release flag for compilation.
     */
    abstract val release: Property<Int>

    /**
     * Source directory for version-specific classes.
     * Default: src/main/{name} (e.g., src/main/java9)
     */
    abstract val sourceDir: DirectoryProperty

    /**
     * Minimum toolchain version required to compile this source set.
     * Must be >= release version. Defaults to the release version.
     * Use when a higher JDK is needed (e.g., compile Java 9 code with JDK 11).
     */
    abstract val minToolchainVersion: Property<Int>

    override fun getName(): String = name

    /**
     * Returns the capitalized name for task naming.
     * Example: "Java9" for name "java9"
     */
    fun capitalizedName(): String = name.replaceFirstChar { it.titlecase() }

    /**
     * The compile task name for this versioned source set.
     * Example: "compileJava9Java" for name "java9"
     */
    val compileTaskName: String get() = "compile${capitalizedName()}Java"
}
