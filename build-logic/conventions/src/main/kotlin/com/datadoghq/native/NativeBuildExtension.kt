
package com.datadoghq.native

import com.datadoghq.native.model.Architecture
import com.datadoghq.native.model.BuildConfiguration
import com.datadoghq.native.model.Platform
import com.datadoghq.native.util.PlatformUtils
import org.gradle.api.Action
import org.gradle.api.NamedDomainObjectContainer
import org.gradle.api.Project
import org.gradle.api.file.Directory
import org.gradle.api.model.ObjectFactory
import org.gradle.api.provider.ListProperty
import org.gradle.api.provider.Property
import org.gradle.api.provider.Provider
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
     * Get configuration names for the current platform/architecture
     */
    fun getActiveConfigurationNames(): List<String> {
        val platform = com.datadoghq.native.util.PlatformUtils.currentPlatform
        val arch = com.datadoghq.native.util.PlatformUtils.currentArchitecture
        return getActiveConfigurations(platform, arch).map { it.name }
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

    // ==================== Path Utilities ====================
    // These methods provide consistent path calculations for native library locations

    /**
     * Platform identifier for library paths (e.g., "LINUX-x64", "MACOS-arm64-musl")
     */
    fun platformIdentifier(): String {
        val muslSuffix = if (PlatformUtils.isMusl()) "-musl" else ""
        return "${PlatformUtils.currentPlatform}-${PlatformUtils.currentArchitecture}$muslSuffix"
    }

    /**
     * Directory where native libraries are built for a given configuration.
     * Structure: build/lib/main/{config}/{platform}/{arch}/
     */
    fun librarySourceDir(config: String): Provider<Directory> {
        return project.layout.buildDirectory.dir(
            "lib/main/$config/${PlatformUtils.currentPlatform}/${PlatformUtils.currentArchitecture}"
        )
    }

    /**
     * Directory for packaging native libraries into JAR.
     * Structure: build/native/{config}/META-INF/native-libs/{platform-arch}/
     */
    fun libraryTargetDir(config: String): Provider<Directory> {
        return project.layout.buildDirectory.dir(
            "native/$config/META-INF/native-libs/${platformIdentifier()}"
        )
    }

    /**
     * Base directory for native library packaging (without platform subdirs).
     * Structure: build/native/{config}/
     */
    fun libraryTargetBase(config: String): Provider<Directory> {
        return project.layout.buildDirectory.dir("native/$config")
    }

    /**
     * Returns the platform-appropriate shared library filename.
     * Examples: "libjavaProfiler.so" (Linux), "libjavaProfiler.dylib" (macOS)
     */
    fun sharedLibraryName(baseName: String): String {
        return "lib$baseName.${PlatformUtils.sharedLibExtension()}"
    }
}
