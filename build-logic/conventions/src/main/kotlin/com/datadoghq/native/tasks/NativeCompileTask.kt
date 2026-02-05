// Copyright 2026, Datadog, Inc

package com.datadoghq.native.tasks

import com.datadoghq.native.model.ErrorHandlingMode
import com.datadoghq.native.model.LogLevel
import com.datadoghq.native.model.SourceSet
import org.gradle.api.DefaultTask
import org.gradle.api.NamedDomainObjectContainer
import org.gradle.api.file.ConfigurableFileCollection
import org.gradle.api.file.DirectoryProperty
import org.gradle.api.model.ObjectFactory
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
 * Supports both simple mode (single sources collection) and source sets mode
 * (multiple source collections with per-set compiler flags).
 */
abstract class NativeCompileTask @Inject constructor(
    private val execOperations: ExecOperations,
    private val objects: ObjectFactory
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

    /**
     * Source sets for per-directory compiler flags.
     * When used, the simple 'sources' property is ignored.
     */
    @get:Nested
    @get:Optional
    val sourceSets: NamedDomainObjectContainer<SourceSet> = objects.domainObjectContainer(SourceSet::class.java)

    // === Logging and Verbosity ===

    /**
     * Logging verbosity level.
     * Default: NORMAL
     */
    @get:Input
    @get:Optional
    abstract val logLevel: Property<LogLevel>

    /**
     * Progress reporting interval (log every N files during compilation).
     * Default: 10
     */
    @get:Input
    @get:Optional
    abstract val progressReportInterval: Property<Int>

    /**
     * Show full command line for each file compilation.
     * Default: false (only shown at DEBUG level)
     */
    @get:Input
    @get:Optional
    abstract val showCommandLines: Property<Boolean>

    /**
     * Enable ANSI color codes in output.
     * Default: true
     */
    @get:Input
    @get:Optional
    abstract val colorOutput: Property<Boolean>

    // === Error Handling ===

    /**
     * Error handling mode.
     * FAIL_FAST: Stop on first compilation error (default)
     * COLLECT_ALL: Compile all files, collect errors, report at end
     */
    @get:Input
    @get:Optional
    abstract val errorHandling: Property<ErrorHandlingMode>

    /**
     * Maximum number of errors to show when using COLLECT_ALL mode.
     * Default: 10
     */
    @get:Input
    @get:Optional
    abstract val maxErrorsToShow: Property<Int>

    /**
     * Treat compiler warnings as errors (-Werror).
     * Default: false
     */
    @get:Input
    @get:Optional
    abstract val treatWarningsAsErrors: Property<Boolean>

    // === Convenience Properties ===

    /**
     * Compiler defines (-D flags).
     * Use define() method to add: define("DEBUG", "VERSION=\"1.0\"")
     */
    @get:Input
    @get:Optional
    abstract val defines: ListProperty<String>

    /**
     * Compiler undefines (-U flags).
     * Use undefine() method to add: undefine("NDEBUG")
     */
    @get:Input
    @get:Optional
    abstract val undefines: ListProperty<String>

    /**
     * C++ standard version (e.g., "c++17", "c++20").
     * Use standard() method to set: standard("c++20")
     */
    @get:Input
    @get:Optional
    abstract val standardVersion: Property<String>

    init {
        parallelJobs.convention(Runtime.getRuntime().availableProcessors())
        verbose.convention(false)
        logLevel.convention(LogLevel.NORMAL)
        progressReportInterval.convention(10)
        showCommandLines.convention(false)
        colorOutput.convention(true)
        errorHandling.convention(ErrorHandlingMode.FAIL_FAST)
        maxErrorsToShow.convention(10)
        treatWarningsAsErrors.convention(false)
        defines.convention(emptyList())
        undefines.convention(emptyList())
        group = "build"
        description = "Compiles C++ source files"
    }

    /**
     * Configure source sets using a DSL block.
     */
    fun sourceSets(action: org.gradle.api.Action<NamedDomainObjectContainer<SourceSet>>) {
        action.execute(sourceSets)
    }

    // === Convenience Methods ===

    /**
     * Add compiler defines (-D flags).
     * Example: define("DEBUG", "VERSION=\"1.0\"")
     */
    fun define(vararg defs: String) {
        defines.addAll(*defs)
    }

    /**
     * Add compiler undefines (-U flags).
     * Example: undefine("NDEBUG", "DEBUG")
     */
    fun undefine(vararg undefs: String) {
        undefines.addAll(*undefs)
    }

    /**
     * Set C++ standard version.
     * Example: standard("c++20") generates -std=c++20
     */
    fun standard(version: String) {
        standardVersion.set(version)
    }

    // === Logging Helpers ===

    private fun logNormal(message: String) {
        if (logLevel.get() >= LogLevel.NORMAL) {
            logger.lifecycle(message)
        }
    }

    private fun logVerbose(message: String) {
        if (logLevel.get() >= LogLevel.VERBOSE) {
            logger.lifecycle(message)
        }
    }

    private fun logDebug(message: String) {
        if (logLevel.get() == LogLevel.DEBUG) {
            logger.lifecycle(message)
        }
    }

    private fun shouldShowCommandLine(): Boolean {
        return showCommandLines.get() || logLevel.get() == LogLevel.DEBUG
    }

    @TaskAction
    fun compile() {
        val objDir = objectFileDir.get().asFile
        objDir.mkdirs()

        // Build base compiler arguments with convenience properties
        val baseArgs = compilerArgs.get().toMutableList()

        // Add C++ standard if specified
        if (standardVersion.isPresent) {
            baseArgs.add("-std=${standardVersion.get()}")
        }

        // Add defines (-D)
        defines.get().forEach { define ->
            baseArgs.add("-D$define")
        }

        // Add undefines (-U)
        undefines.get().forEach { undefine ->
            baseArgs.add("-U$undefine")
        }

        // Add -Werror if warnings should be treated as errors
        if (treatWarningsAsErrors.get()) {
            baseArgs.add("-Werror")
        }

        // Build include arguments
        val includeArgs = mutableListOf<String>()
        includes.files.forEach { dir ->
            if (dir.exists()) {
                includeArgs.add("-I")
                includeArgs.add(dir.absolutePath)
            }
        }

        val errors = ConcurrentLinkedQueue<String>()
        val compiled = AtomicInteger(0)

        // Choose compilation mode: source sets or simple sources
        if (sourceSets.isEmpty()) {
            // Simple mode: compile all sources with base args
            compileSimpleMode(objDir, baseArgs, includeArgs, compiled, errors)
        } else {
            // Source sets mode: compile each set with merged args
            compileSourceSetsMode(objDir, baseArgs, includeArgs, compiled, errors)
        }

        // Report errors if any
        if (errors.isNotEmpty()) {
            val maxErrors = maxErrorsToShow.get()
            val errorMsg = buildString {
                appendLine("Compilation failed with ${errors.size} error(s):")
                errors.take(maxErrors).forEach { error ->
                    appendLine("  - $error")
                }
                if (errors.size > maxErrors) {
                    appendLine("  ... and ${errors.size - maxErrors} more error(s)")
                }
            }
            throw RuntimeException(errorMsg)
        }

        logNormal("Successfully compiled ${compiled.get()} file${if (compiled.get() == 1) "" else "s"}")
    }

    private fun compileSimpleMode(
        objDir: File,
        baseArgs: List<String>,
        includeArgs: List<String>,
        compiled: AtomicInteger,
        errors: ConcurrentLinkedQueue<String>
    ) {
        val sourceFiles = sources.files.toList()
        if (sourceFiles.isEmpty()) {
            logNormal("No source files to compile")
            return
        }

        val total = sourceFiles.size
        logNormal("Compiling $total C++ source file${if (total == 1) "" else "s"} with ${compiler.get()}...")

        // Compile files in parallel
        sourceFiles.parallelStream().forEach { sourceFile ->
            try {
                compileFile(sourceFile, objDir, baseArgs, includeArgs, compiled, total, errors)
            } catch (e: Exception) {
                errors.add("Exception compiling ${sourceFile.name}: ${e.message}")
            }
        }
    }

    private fun compileSourceSetsMode(
        objDir: File,
        baseArgs: List<String>,
        includeArgs: List<String>,
        compiled: AtomicInteger,
        errors: ConcurrentLinkedQueue<String>
    ) {
        // Collect all files from all source sets
        val allFiles = mutableListOf<Pair<File, List<String>>>()

        sourceSets.forEach { sourceSet ->
            val setFiles = sourceSet.sources.asFileTree
                .matching {
                    sourceSet.includes.get().forEach { pattern -> include(pattern) }
                    sourceSet.excludes.get().forEach { pattern -> exclude(pattern) }
                }
                .files
                .toList()

            // Merge base args with source-set-specific args
            val mergedArgs = baseArgs + sourceSet.compilerArgs.get()

            setFiles.forEach { file ->
                allFiles.add(file to mergedArgs)
            }
        }

        if (allFiles.isEmpty()) {
            logNormal("No source files to compile in source sets")
            return
        }

        val total = allFiles.size
        logNormal("Compiling $total C++ source file${if (total == 1) "" else "s"} from ${sourceSets.size} source set${if (sourceSets.size == 1) "" else "s"} with ${compiler.get()}...")

        // Compile files in parallel with their specific args
        allFiles.parallelStream().forEach { (sourceFile, specificArgs) ->
            try {
                compileFile(sourceFile, objDir, specificArgs, includeArgs, compiled, total, errors)
            } catch (e: Exception) {
                errors.add("Exception compiling ${sourceFile.name}: ${e.message}")
            }
        }
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

        if (shouldShowCommandLine()) {
            logDebug("  ${cmdLine.joinToString(" ")}")
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

            // FAIL_FAST: throw immediately on first error
            if (errorHandling.get() == ErrorHandlingMode.FAIL_FAST) {
                throw RuntimeException(errorMsg)
            }
        } else {
            val count = compiled.incrementAndGet()
            val interval = progressReportInterval.get()
            if (logLevel.get() >= LogLevel.VERBOSE && (count % interval == 0 || count == total)) {
                logVerbose("  Compiled $count/$total files...")
            }
        }
    }
}
