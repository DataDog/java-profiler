
package com.datadoghq.java.versionedsources

import org.gradle.api.Action
import org.gradle.api.JavaVersion
import org.gradle.api.NamedDomainObjectContainer
import org.gradle.api.Project
import org.gradle.api.model.ObjectFactory
import org.gradle.api.tasks.SourceSetContainer
import org.gradle.jvm.tasks.Jar
import javax.inject.Inject

/**
 * Extension for configuring versioned source sets.
 *
 * This plugin helps manage Java version-specific source directories where code
 * requires different Java versions to compile (e.g., VarHandle in Java 9+).
 * Classes are compiled separately and merged into the JAR root for runtime
 * selection via Class.forName().
 *
 * Usage:
 * ```kotlin
 * versionedSources {
 *     versions {
 *         register("java9") {
 *             release.set(9)
 *             minToolchainVersion.set(11)
 *         }
 *         register("java11") {
 *             release.set(11)
 *         }
 *     }
 * }
 * ```
 */
abstract class VersionedSourcesExtension @Inject constructor(
    private val project: Project,
    objects: ObjectFactory
) {
    /**
     * Container for versioned source set configurations.
     */
    val versions: NamedDomainObjectContainer<VersionedSourceSet> =
        objects.domainObjectContainer(VersionedSourceSet::class.java)

    /**
     * Configure versioned source sets using a DSL block.
     */
    fun versions(action: Action<NamedDomainObjectContainer<VersionedSourceSet>>) {
        action.execute(versions)
    }

    /**
     * Get all versioned source sets that can be compiled with the current JDK.
     */
    fun getCompilableVersions(): List<VersionedSourceSet> {
        val available = JavaVersion.current().majorVersion.toInt()
        return versions.filter { version ->
            val required = version.minToolchainVersion.orNull ?: version.release.get()
            required <= available
        }
    }

    /**
     * Configures a JAR task to include all versioned classes at the JAR root.
     *
     * This adds the classes compiled from version-specific source sets to the JAR root,
     * alongside the main source set classes. This is useful when the application uses
     * runtime class loading (Class.forName) to select the appropriate implementation
     * based on Java version.
     *
     * Usage:
     * ```kotlin
     * tasks.register("myJar", Jar::class) {
     *     from(sourceSets.main.get().output)
     *     versionedSources.configureJar(this)
     * }
     * ```
     */
    fun configureJar(jar: Jar) {
        val sourceSets = project.extensions.getByType(SourceSetContainer::class.java)

        versions.forEach { version ->
            val sourceSet = sourceSets.findByName(version.name) ?: return@forEach
            jar.from(sourceSet.output.classesDirs)
            jar.dependsOn(version.compileTaskName)
        }
    }

    /**
     * Configures a source JAR task to include all versioned source files.
     *
     * Usage:
     * ```kotlin
     * val sourcesJar by tasks.registering(Jar::class) {
     *     from(sourceSets.main.get().allJava)
     *     versionedSources.configureSourceJar(this)
     * }
     * ```
     */
    fun configureSourceJar(jar: Jar) {
        val sourceSets = project.extensions.getByType(SourceSetContainer::class.java)

        versions.forEach { version ->
            val sourceSet = sourceSets.findByName(version.name) ?: return@forEach
            jar.from(sourceSet.allJava)
        }
    }
}
