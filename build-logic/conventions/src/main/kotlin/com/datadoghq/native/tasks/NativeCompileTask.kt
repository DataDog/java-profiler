// Copyright 2026, Datadog, Inc

package com.datadoghq.native.tasks

import org.gradle.api.DefaultTask
import org.gradle.api.file.ConfigurableFileCollection
import org.gradle.api.file.DirectoryProperty
import org.gradle.api.provider.ListProperty
import org.gradle.api.provider.Property
import org.gradle.api.tasks.*
import org.gradle.process.ExecOperations
import java.io.ByteArrayOutputStream
import java.io.File
import java.util.concurrent.ConcurrentLinkedQueue
import java.util.concurrent.atomic.AtomicInteger
import javax.inject.Inject

/**
 * Kotlin-based C++ compilation task that directly invokes gcc/clang.
 *
 * Simplified from the Groovy SimpleCppCompile to focus on core functionality:
 * - Parallel compilation
 * - Error collection and reporting
 * - Include directory handling
 * - Compiler flag management
 */
abstract class NativeCompileTask @Inject constructor(
    private val execOperations: ExecOperations
) : DefaultTask() {

    /**
     * The C++ compiler executable (e.g., 'g++', 'clang++', or full path).
     */
    @get:Input
    abstract val compiler: Property<String>

    /**
     * Compiler arguments (flags) to pass to the compiler.
     */
    @get:Input
    abstract val compilerArgs: ListProperty<String>

    /**
     * The C++ source files to compile.
     */
    @get:InputFiles
    @get:SkipWhenEmpty
    abstract val sources: ConfigurableFileCollection

    /**
     * Include directories for header file lookup.
     */
    @get:InputFiles
    @get:Optional
    abstract val includes: ConfigurableFileCollection

    /**
     * Output directory for object files.
     */
    @get:OutputDirectory
    abstract val objectFileDir: DirectoryProperty

    /**
     * Number of parallel compilation jobs.
     */
    @get:Input
    @get:Optional
    abstract val parallelJobs: Property<Int>

    /**
     * Show detailed compilation output.
     */
    @get:Input
    @get:Optional
    abstract val verbose: Property<Boolean>

    init {
        parallelJobs.convention(Runtime.getRuntime().availableProcessors())
        verbose.convention(false)
        group = "build"
        description = "Compiles C++ source files"
    }

    @TaskAction
    fun compile() {
        val objDir = objectFileDir.get().asFile
        objDir.mkdirs()

        val sourceFiles = sources.files.toList()
        if (sourceFiles.isEmpty()) {
            logger.lifecycle("No source files to compile")
            return
        }

        val baseArgs = compilerArgs.get().toMutableList()
        val includeArgs = mutableListOf<String>()

        // Build include arguments
        includes.files.forEach { dir ->
            if (dir.exists()) {
                includeArgs.add("-I")
                includeArgs.add(dir.absolutePath)
            }
        }

        val errors = ConcurrentLinkedQueue<String>()
        val compiled = AtomicInteger(0)
        val total = sourceFiles.size

        logger.lifecycle("Compiling $total C++ source file${if (total == 1) "" else "s"} with ${compiler.get()}...")

        // Compile files in parallel
        sourceFiles.parallelStream().forEach { sourceFile ->
            try {
                compileFile(sourceFile, objDir, baseArgs, includeArgs, compiled, total, errors)
            } catch (e: Exception) {
                errors.add("Exception compiling ${sourceFile.name}: ${e.message}")
            }
        }

        // Report errors if any
        if (errors.isNotEmpty()) {
            val errorMsg = buildString {
                appendLine("Compilation failed with ${errors.size} error(s):")
                errors.take(10).forEach { error ->
                    appendLine("  - $error")
                }
                if (errors.size > 10) {
                    appendLine("  ... and ${errors.size - 10} more error(s)")
                }
            }
            throw RuntimeException(errorMsg)
        }

        logger.lifecycle("Successfully compiled $total file${if (total == 1) "" else "s"}")
    }

    private fun compileFile(
        sourceFile: File,
        objDir: File,
        baseArgs: List<String>,
        includeArgs: List<String>,
        compiled: AtomicInteger,
        total: Int,
        errors: ConcurrentLinkedQueue<String>
    ) {
        // Determine object file name
        val baseName = sourceFile.nameWithoutExtension
        val objectFile = File(objDir, "$baseName.o")

        // Build full command line
        val cmdLine = mutableListOf<String>().apply {
            add(compiler.get())
            addAll(baseArgs)
            addAll(includeArgs)
            add("-c")
            add(sourceFile.absolutePath)
            add("-o")
            add(objectFile.absolutePath)
        }

        if (verbose.get()) {
            logger.lifecycle("  ${cmdLine.joinToString(" ")}")
        }

        // Execute compilation
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
                append("Failed to compile ${sourceFile.name}: exit code ${result.exitValue}")
                if (allOutput.isNotEmpty()) {
                    appendLine()
                    append(allOutput)
                }
            }
            errors.add(errorMsg)
        } else {
            val count = compiled.incrementAndGet()
            if (verbose.get() && (count % 10 == 0 || count == total)) {
                logger.lifecycle("  Compiled $count/$total files...")
            }
        }
    }
}
