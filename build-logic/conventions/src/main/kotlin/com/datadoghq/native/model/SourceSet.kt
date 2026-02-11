
package com.datadoghq.native.model

import org.gradle.api.Named
import org.gradle.api.file.ConfigurableFileCollection
import org.gradle.api.provider.ListProperty
import org.gradle.api.tasks.Input
import org.gradle.api.tasks.InputFiles
import org.gradle.api.tasks.Internal
import org.gradle.api.tasks.Optional
import javax.inject.Inject

/**
 * Represents a named set of source files with optional per-set compiler flags.
 * Allows different parts of the codebase to have different compilation settings.
 *
 * Example usage:
 * sourceSets { main { sources.from(fileTree("src/main/cpp")) } }
 */
abstract class SourceSet @Inject constructor(
    private val name: String
) : Named {

    /**
     * Source files for this source set.
     */
    @get:InputFiles
    abstract val sources: ConfigurableFileCollection

    /**
     * Include patterns for filtering source files (Ant-style).
     * Default: all C++ source files (.cpp, .c, .cc)
     */
    @get:Input
    @get:Optional
    abstract val includes: ListProperty<String>

    /**
     * Exclude patterns for filtering source files (Ant-style).
     */
    @get:Input
    @get:Optional
    abstract val excludes: ListProperty<String>

    /**
     * Additional compiler arguments specific to this source set.
     * These are added to the base compiler arguments.
     */
    @get:Input
    @get:Optional
    abstract val compilerArgs: ListProperty<String>

    init {
        includes.convention(listOf("**/*.cpp", "**/*.c", "**/*.cc"))
        excludes.convention(emptyList())
        compilerArgs.convention(emptyList())
    }

    @Internal
    override fun getName(): String = name

    /**
     * Convenience method to set source directory.
     */
    fun from(vararg sources: Any) {
        this.sources.from(*sources)
    }

    /**
     * Convenience method to add include patterns.
     */
    fun include(vararg patterns: String) {
        includes.addAll(*patterns)
    }

    /**
     * Convenience method to add exclude patterns.
     */
    fun exclude(vararg patterns: String) {
        excludes.addAll(*patterns)
    }

    /**
     * Convenience method to add compiler args.
     */
    fun compileWith(vararg args: String) {
        compilerArgs.addAll(*args)
    }

    override fun toString(): String {
        return "SourceSet[name=$name, sources=${sources.files.size} files]"
    }
}
