// Copyright 2026, Datadog, Inc

package com.datadoghq.native.tasks

import com.datadoghq.native.model.LogLevel
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
 * Kotlin-based executable linking task that directly invokes the linker.
 *
 * Used for linking test executables (gtest) and other standalone binaries.
 */
abstract class NativeLinkExecutableTask @Inject constructor(
    private val execOperations: ExecOperations
) : DefaultTask() {

    /**
     * The linker executable (usually same as compiler: 'g++', 'clang++').
     */
    @get:Input
    abstract val linker: Property<String>

    /**
     * Linker arguments (flags).
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
     * The output executable file.
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
     * Runtime library search paths (-Wl,-rpath).
     */
    @get:Input
    @get:Optional
    abstract val runtimePaths: ListProperty<String>

    /**
     * Logging verbosity level.
     */
    @get:Input
    @get:Optional
    abstract val logLevel: Property<LogLevel>

    /**
     * Show full command line.
     */
    @get:Input
    @get:Optional
    abstract val showCommandLine: Property<Boolean>

    init {
        libraryPaths.convention(emptyList())
        libraries.convention(emptyList())
        runtimePaths.convention(emptyList())
        logLevel.convention(LogLevel.NORMAL)
        showCommandLine.convention(false)
        group = "build"
        description = "Links object files into an executable"
    }

    /**
     * Add libraries to link against.
     */
    fun lib(vararg libs: String) {
        libraries.addAll(*libs)
    }

    /**
     * Add library search paths.
     */
    fun libPath(vararg paths: String) {
        libraryPaths.addAll(*paths)
    }

    /**
     * Add runtime library search paths.
     */
    fun runtimePath(vararg paths: String) {
        runtimePaths.addAll(*paths)
    }

    private fun logNormal(message: String) {
        if (logLevel.get() >= LogLevel.NORMAL) {
            logger.lifecycle(message)
        }
    }

    private fun logDebug(message: String) {
        if (logLevel.get() == LogLevel.DEBUG) {
            logger.lifecycle(message)
        }
    }

    @TaskAction
    fun link() {
        val outFile = outputFile.get().asFile
        outFile.parentFile.mkdirs()

        val objectPaths = objectFiles.files.map { it.absolutePath }

        // Build command line
        val cmdLine = mutableListOf<String>().apply {
            add(linker.get())
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

            // Add runtime search paths (-rpath)
            runtimePaths.get().forEach { path ->
                when (PlatformUtils.currentPlatform) {
                    com.datadoghq.native.model.Platform.LINUX -> add("-Wl,-rpath,$path")
                    com.datadoghq.native.model.Platform.MACOS -> add("-Wl,-rpath,$path")
                }
            }

            // Add output file
            add("-o")
            add(outFile.absolutePath)
        }

        logNormal("Linking executable: ${outFile.name}")

        if (showCommandLine.get() || logLevel.get() == LogLevel.DEBUG) {
            logDebug("  ${cmdLine.joinToString(" ")}")
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
                append("Failed to link executable: exit code ${result.exitValue}")
                if (allOutput.isNotEmpty()) {
                    appendLine()
                    append(allOutput)
                }
            }
            throw RuntimeException(errorMsg)
        }

        // Make executable
        outFile.setExecutable(true)

        val sizeKB = outFile.length() / 1024
        logNormal("Successfully linked ${outFile.name} (${sizeKB}KB)")
    }
}
