// Copyright 2026, Datadog, Inc

package com.datadoghq.native.tasks

import com.datadoghq.native.util.PlatformUtils
import org.gradle.api.DefaultTask
import org.gradle.api.file.ConfigurableFileCollection
import org.gradle.api.file.RegularFileProperty
import org.gradle.api.provider.ListProperty
import org.gradle.api.provider.Property
import org.gradle.api.tasks.*
import org.gradle.process.ExecOperations
import java.io.ByteArrayOutputStream
import javax.inject.Inject

/**
 * Kotlin-based shared library linking task that directly invokes the linker.
 *
 * Simplified from the Groovy SimpleLinkShared to focus on core functionality:
 * - Linking object files into shared libraries
 * - Library path and library flag management
 * - Platform-specific flag handling (soname vs install_name)
 * - Symbol stripping (optional)
 */
abstract class NativeLinkTask @Inject constructor(
    private val execOperations: ExecOperations
) : DefaultTask() {

    /**
     * The linker executable (usually same as compiler: 'g++', 'clang++').
     */
    @get:Input
    abstract val linker: Property<String>

    /**
     * Linker arguments (flags and libraries).
     */
    @get:Input
    abstract val linkerArgs: ListProperty<String>

    /**
     * The object files to link.
     */
    @get:InputFiles
    @get:SkipWhenEmpty
    abstract val objectFiles: ConfigurableFileCollection

    /**
     * The output shared library file.
     */
    @get:OutputFile
    abstract val outputFile: RegularFileProperty

    /**
     * Library search paths (-L).
     */
    @get:Input
    @get:Optional
    abstract val libraryPaths: ListProperty<String>

    /**
     * Libraries to link against (-l).
     */
    @get:Input
    @get:Optional
    abstract val libraries: ListProperty<String>

    /**
     * SO name for Linux (-Wl,-soname).
     */
    @get:Input
    @get:Optional
    abstract val soname: Property<String>

    /**
     * Install name for macOS (-Wl,-install_name).
     */
    @get:Input
    @get:Optional
    abstract val installName: Property<String>

    /**
     * Strip symbols after linking.
     */
    @get:Input
    @get:Optional
    abstract val stripSymbols: Property<Boolean>

    /**
     * Show detailed linking output.
     */
    @get:Input
    @get:Optional
    abstract val verbose: Property<Boolean>

    init {
        libraryPaths.convention(emptyList())
        libraries.convention(emptyList())
        stripSymbols.convention(false)
        verbose.convention(false)
        group = "build"
        description = "Links object files into a shared library"
    }

    fun lib(vararg libs: String) {
        libraries.addAll(*libs)
    }

    fun libPath(vararg paths: String) {
        libraryPaths.addAll(*paths)
    }

    @TaskAction
    fun link() {
        val outFile = outputFile.get().asFile
        outFile.parentFile.mkdirs()

        val objectPaths = objectFiles.files.map { it.absolutePath }

        // Determine shared library flag based on platform
        val sharedFlag = when (PlatformUtils.currentPlatform) {
            com.datadoghq.native.model.Platform.MACOS -> "-dynamiclib"
            com.datadoghq.native.model.Platform.LINUX -> "-shared"
        }

        // Build command line
        val cmdLine = mutableListOf<String>().apply {
            add(linker.get())
            add(sharedFlag)
            addAll(objectPaths)
            addAll(linkerArgs.get())

            // Add library search paths (-L)
            libraryPaths.get().forEach { path ->
                add("-L$path")
            }

            // Add libraries (-l)
            libraries.get().forEach { lib ->
                add("-l$lib")
            }

            // Add soname/install_name based on platform
            when (PlatformUtils.currentPlatform) {
                com.datadoghq.native.model.Platform.LINUX -> {
                    if (soname.isPresent) {
                        add("-Wl,-soname,${soname.get()}")
                    }
                }
                com.datadoghq.native.model.Platform.MACOS -> {
                    if (installName.isPresent) {
                        add("-Wl,-install_name,${installName.get()}")
                    }
                }
            }

            // Add output file
            add("-o")
            add(outFile.absolutePath)
        }

        logger.lifecycle("Linking shared library: ${outFile.name}")

        if (verbose.get()) {
            logger.lifecycle("  ${cmdLine.joinToString(" ")}")
        }

        // Execute linking
        val stdout = ByteArrayOutputStream()
        val stderr = ByteArrayOutputStream()

        val result = execOperations.exec {
            commandLine(cmdLine)
            standardOutput = stdout
            errorOutput = stderr
            isIgnoreExitValue = true
        }

        if (result.exitValue != 0) {
            val allOutput = (stdout.toString() + stderr.toString()).trim()
            val errorMsg = buildString {
                append("Failed to link shared library: exit code ${result.exitValue}")
                if (allOutput.isNotEmpty()) {
                    appendLine()
                    append(allOutput)
                }
            }
            throw RuntimeException(errorMsg)
        }

        // Strip symbols if requested
        if (stripSymbols.get()) {
            stripLibrary(outFile)
        }

        val sizeKB = outFile.length() / 1024
        logger.lifecycle("Successfully linked ${outFile.name} (${sizeKB}KB)")
    }

    private fun stripLibrary(libFile: java.io.File) {
        logger.lifecycle("Stripping symbols from ${libFile.name}...")

        val stripCmd = when (PlatformUtils.currentPlatform) {
            com.datadoghq.native.model.Platform.LINUX -> listOf("strip", "--strip-debug", libFile.absolutePath)
            com.datadoghq.native.model.Platform.MACOS -> listOf("strip", "-S", libFile.absolutePath)
        }

        val result = execOperations.exec {
            commandLine(stripCmd)
            isIgnoreExitValue = true
        }

        if (result.exitValue != 0) {
            logger.warn("Failed to strip symbols (exit code ${result.exitValue}), continuing...")
        }
    }
}
