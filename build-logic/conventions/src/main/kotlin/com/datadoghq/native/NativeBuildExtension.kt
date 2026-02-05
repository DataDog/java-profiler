// Copyright 2026, Datadog, Inc

package com.datadoghq.native

import com.datadoghq.native.model.Architecture
import com.datadoghq.native.model.BuildConfiguration
import com.datadoghq.native.model.Platform
import org.gradle.api.Action
import org.gradle.api.NamedDomainObjectContainer
import org.gradle.api.Project
import org.gradle.api.model.ObjectFactory
import org.gradle.api.provider.ListProperty
import org.gradle.api.provider.Property
import javax.inject.Inject

abstract class NativeBuildExtension @Inject constructor(
    private val project: Project,
    private val objects: ObjectFactory
) {
    /**
     * Container for build configurations (release, debug, asan, tsan, etc.)
     */
    val buildConfigurations: NamedDomainObjectContainer<BuildConfiguration> =
        objects.domainObjectContainer(BuildConfiguration::class.java)

    /**
     * Project version to embed in binaries
     */
    abstract val version: Property<String>

    /**
     * Source directories for C++ code
     */
    abstract val cppSourceDirs: ListProperty<String>

    /**
     * Include directories for compilation
     */
    abstract val includeDirectories: ListProperty<String>

    init {
        version.convention(project.version.toString())
        cppSourceDirs.convention(listOf("src/main/cpp"))
        includeDirectories.convention(emptyList())
    }

    /**
     * Configure build configurations using a DSL block
     */
    fun buildConfigurations(action: Action<NamedDomainObjectContainer<BuildConfiguration>>) {
        action.execute(buildConfigurations)
    }

    /**
     * Get all configurations that are active for the current platform and architecture
     */
    fun getActiveConfigurations(platform: Platform, architecture: Architecture): List<BuildConfiguration> {
        return buildConfigurations.filter { it.isActiveFor(platform, architecture) }
    }

    /**
     * Convenience method to define common compiler args for all configurations
     */
    fun commonCompilerArgs(vararg args: String) {
        buildConfigurations.configureEach {
            compilerArgs.addAll(*args)
        }
    }

    /**
     * Convenience method to define common linker args for all configurations
     */
    fun commonLinkerArgs(vararg args: String) {
        buildConfigurations.configureEach {
            linkerArgs.addAll(*args)
        }
    }
}
