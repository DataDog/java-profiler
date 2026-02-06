// Copyright 2026, Datadog, Inc

package com.datadoghq.native.model

import org.gradle.api.Named
import org.gradle.api.provider.ListProperty
import org.gradle.api.provider.MapProperty
import org.gradle.api.provider.Property
import javax.inject.Inject

abstract class BuildConfiguration @Inject constructor(
    private val configName: String
) : Named {
    abstract val platform: Property<Platform>
    abstract val architecture: Property<Architecture>
    abstract val compilerArgs: ListProperty<String>
    abstract val linkerArgs: ListProperty<String>
    abstract val testEnvironment: MapProperty<String, String>
    abstract val active: Property<Boolean>

    override fun getName(): String = configName

    init {
        // Default to active unless overridden
        active.convention(true)
        testEnvironment.convention(emptyMap())
    }

    fun isActiveFor(targetPlatform: Platform, targetArch: Architecture): Boolean {
        return active.get() &&
               platform.get() == targetPlatform &&
               architecture.get() == targetArch
    }

    /**
     * Returns a unique identifier for this configuration combining name, platform, and architecture.
     * Example: "releaseLinuxX64"
     */
    fun identifier(): String {
        val platformStr = platform.get().toString()
        val archStr = architecture.get().toString()
        return "$configName${platformStr.replaceFirstChar { it.titlecase() }}${archStr.replaceFirstChar { it.titlecase() }}"
    }

    /**
     * Returns the capitalized name for task generation.
     * Example: "Release" for name "release"
     */
    fun capitalizedName(): String = configName.replaceFirstChar { it.titlecase() }
}
