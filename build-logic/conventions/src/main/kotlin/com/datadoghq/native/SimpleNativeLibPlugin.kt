// Copyright 2026, Datadog, Inc

package com.datadoghq.native

import com.datadoghq.native.model.Platform
import com.datadoghq.native.tasks.NativeCompileTask
import com.datadoghq.native.tasks.NativeLinkTask
import com.datadoghq.native.util.PlatformUtils
import org.gradle.api.Plugin
import org.gradle.api.Project
import org.gradle.api.file.DirectoryProperty
import org.gradle.api.provider.ListProperty
import org.gradle.api.provider.Property
import javax.inject.Inject

/**
 * Simplified plugin for single-output native library projects.
 *
 * Creates standard compile and link tasks with sensible defaults:
 * - compileLib: Compiles C/C++ sources
 * - linkLib: Links shared library
 * - Wires linkLib into assemble lifecycle
 *
 * Usage:
 * ```kotlin
 * plugins {
 *   id("com.datadoghq.simple-native-lib")
 * }
 *
 * simpleNativeLib {
 *   libraryName.set("mylib")
 *   sourceDir.set(file("src/main/cpp"))
 *   compilerArgs.set(listOf("-O3", "-fPIC"))
 * }
 * ```
 */
class SimpleNativeLibPlugin : Plugin<Project> {
    override fun apply(project: Project) {
        val extension = project.extensions.create(
            "simpleNativeLib",
            SimpleNativeLibExtension::class.java,
            project
        )

        project.afterEvaluate {
            if (!extension.enabled.get()) {
                return@afterEvaluate
            }

            val compiler = extension.compiler.getOrElse(PlatformUtils.findCompiler(project))
            val linker = extension.linker.getOrElse(compiler)
            val libraryName = extension.libraryName.get()
            val objectDir = extension.objectDir.get().asFile
            val outputLib = extension.outputDir.get().asFile.resolve(
                "lib$libraryName.${PlatformUtils.sharedLibExtension()}"
            )

            // Compile task
            val compileTask = project.tasks.register("compileLib", NativeCompileTask::class.java) {
                onlyIf { extension.enabled.get() && !project.hasProperty("skip-native") }
                group = "build"
                description = "Compile the $libraryName library"

                this.compiler.set(compiler)
                this.compilerArgs.set(extension.compilerArgs.get())
                sources.from(extension.sourceDir.map { dir ->
                    project.fileTree(dir) {
                        include("**/*.cpp", "**/*.cc", "**/*.c")
                    }
                })
                if (extension.includeJni.get()) {
                    includes.from(PlatformUtils.jniIncludePaths())
                }
                includes.from(extension.includeDirs.get())
                objectFileDir.set(objectDir)
            }

            // Link task
            val linkTask = project.tasks.register("linkLib", NativeLinkTask::class.java) {
                onlyIf { extension.enabled.get() && !project.hasProperty("skip-native") }
                dependsOn(compileTask)
                group = "build"
                description = "Link the $libraryName shared library"

                this.linker.set(linker)
                this.linkerArgs.set(extension.linkerArgs.get())
                objectFiles.from(project.fileTree(objectDir) { include("*.o") })
                outputFile.set(outputLib)
            }

            // Wire into assemble
            project.tasks.named("assemble") {
                dependsOn(linkTask)
            }

            // Create consumable configurations if requested
            if (extension.createConfigurations.get()) {
                createConsumableConfigurations(project, extension, compileTask, linkTask)
            }
        }
    }

    private fun createConsumableConfigurations(
        project: Project,
        extension: SimpleNativeLibExtension,
        compileTask: org.gradle.api.tasks.TaskProvider<NativeCompileTask>,
        linkTask: org.gradle.api.tasks.TaskProvider<NativeLinkTask>
    ) {
        // Runtime library configuration
        project.configurations.create("nativeLib") {
            isCanBeConsumed = true
            isCanBeResolved = false
            description = "Native shared library for runtime loading"
            outgoing.artifact(linkTask.flatMap { it.outputFile }) {
                type = "native-lib"
            }
        }

        // Object files configuration
        project.configurations.create("nativeObjects") {
            isCanBeConsumed = true
            isCanBeResolved = false
            description = "Object files for static linking"
            outgoing.artifact(compileTask.flatMap { it.objectFileDir }) {
                type = "native-objects"
            }
        }

        // Library directory configuration
        project.configurations.create("nativeLibDir") {
            isCanBeConsumed = true
            isCanBeResolved = false
            description = "Directory containing native library"
            outgoing.artifact(extension.outputDir) {
                type = "native-lib-dir"
            }
        }

        // Headers configuration
        project.configurations.create("nativeHeaders") {
            isCanBeConsumed = true
            isCanBeResolved = false
            description = "Header files for compilation"
            outgoing.artifact(extension.sourceDir) {
                type = "native-headers"
            }
        }
    }
}

/**
 * Extension for simple native library configuration.
 */
abstract class SimpleNativeLibExtension @Inject constructor(project: Project) {
    /**
     * Whether this native build is enabled (e.g., platform-specific builds).
     */
    val enabled: Property<Boolean> = project.objects.property(Boolean::class.java)

    /**
     * Name of the library (without lib prefix or extension).
     */
    val libraryName: Property<String> = project.objects.property(String::class.java)

    /**
     * Source directory containing C/C++ files.
     */
    val sourceDir: DirectoryProperty = project.objects.directoryProperty()

    /**
     * Output directory for compiled library.
     */
    val outputDir: DirectoryProperty = project.objects.directoryProperty()

    /**
     * Object file directory.
     */
    val objectDir: DirectoryProperty = project.objects.directoryProperty()

    /**
     * Compiler to use (auto-detected if not set).
     */
    val compiler: Property<String> = project.objects.property(String::class.java)

    /**
     * Linker to use (defaults to compiler if not set).
     */
    val linker: Property<String> = project.objects.property(String::class.java)

    /**
     * Compiler arguments.
     */
    val compilerArgs: ListProperty<String> = project.objects.listProperty(String::class.java)

    /**
     * Linker arguments.
     */
    val linkerArgs: ListProperty<String> = project.objects.listProperty(String::class.java)

    /**
     * Additional include directories.
     */
    val includeDirs: ListProperty<String> = project.objects.listProperty(String::class.java)

    /**
     * Whether to include JNI headers.
     */
    val includeJni: Property<Boolean> = project.objects.property(Boolean::class.java)

    /**
     * Whether to create consumable configurations (nativeLib, nativeObjects, etc.).
     */
    val createConfigurations: Property<Boolean> = project.objects.property(Boolean::class.java)

    init {
        enabled.convention(true)
        libraryName.convention("native")
        sourceDir.convention(project.layout.projectDirectory.dir("src/main/cpp"))
        outputDir.convention(project.layout.buildDirectory.dir("lib"))
        objectDir.convention(project.layout.buildDirectory.dir("obj"))
        compilerArgs.convention(listOf("-fPIC", "-O3"))
        linkerArgs.convention(emptyList())
        includeDirs.convention(emptyList())
        includeJni.convention(false)
        createConfigurations.convention(false)
    }
}
