
package com.datadoghq.native.tasks

import com.datadoghq.native.model.LogLevel
import com.datadoghq.native.util.PlatformUtils
import org.gradle.api.DefaultTask
import org.gradle.api.file.ConfigurableFileCollection
import org.gradle.api.file.DirectoryProperty
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
     * Extract debug symbols to separate file before stripping.
     */
    @get:Input
    @get:Optional
    abstract val extractDebugSymbols: Property<Boolean>

    /**
     * Output directory for extracted debug symbols.
     */
    @get:OutputDirectory
    @get:Optional
    abstract val debugSymbolsDir: DirectoryProperty

    /**
     * Show detailed linking output.
     */
    @get:Input
    @get:Optional
    abstract val verbose: Property<Boolean>

    // === Logging and Verbosity ===

    /**
     * Logging verbosity level.
     * Default: NORMAL
     */
    @get:Input
    @get:Optional
    abstract val logLevel: Property<LogLevel>

    /**
     * Show full command line for the link operation.
     * Default: false (only shown at DEBUG level)
     */
    @get:Input
    @get:Optional
    abstract val showCommandLine: Property<Boolean>

    /**
     * Show linker map (symbol resolution details).
     * Default: false
     */
    @get:Input
    @get:Optional
    abstract val showLinkerMap: Property<Boolean>

    /**
     * Linker map output file (when showLinkerMap is true).
     * Default: null (stdout/stderr)
     */
    @get:OutputFile
    @get:Optional
    abstract val linkerMapFile: RegularFileProperty

    /**
     * Enable ANSI color codes in output.
     * Default: true
     */
    @get:Input
    @get:Optional
    abstract val colorOutput: Property<Boolean>

    // === Symbol Management ===

    /**
     * Symbol patterns to export (make visible).
     * For example: ["Java_*", "JNI_OnLoad", "JNI_OnUnload"]
     */
    @get:Input
    @get:Optional
    abstract val exportSymbols: ListProperty<String>

    /**
     * Symbol patterns to hide (make not visible).
     * Applied after exportSymbols.
     */
    @get:Input
    @get:Optional
    abstract val hideSymbols: ListProperty<String>

    // === Library Path Management ===

    /**
     * Runtime library search paths (-Wl,-rpath).
     * Use runtimePath() method to add.
     */
    @get:Input
    @get:Optional
    abstract val runtimePaths: ListProperty<String>

    // === Verification ===

    /**
     * Check for undefined symbols after linking.
     * Default: false
     */
    @get:Input
    @get:Optional
    abstract val checkUndefinedSymbols: Property<Boolean>

    /**
     * Verify the shared library after linking (ldd/otool -L).
     * Default: false
     */
    @get:Input
    @get:Optional
    abstract val verifySharedLib: Property<Boolean>

    init {
        libraryPaths.convention(emptyList())
        libraries.convention(emptyList())
        runtimePaths.convention(emptyList())
        stripSymbols.convention(false)
        extractDebugSymbols.convention(false)
        verbose.convention(false)
        logLevel.convention(LogLevel.NORMAL)
        showCommandLine.convention(false)
        showLinkerMap.convention(false)
        colorOutput.convention(true)
        exportSymbols.convention(emptyList())
        hideSymbols.convention(emptyList())
        checkUndefinedSymbols.convention(false)
        verifySharedLib.convention(false)
        group = "build"
        description = "Links object files into a shared library"
    }

    fun lib(vararg libs: String) {
        libraries.addAll(*libs)
    }

    fun libPath(vararg paths: String) {
        libraryPaths.addAll(*paths)
    }

    fun runtimePath(vararg paths: String) {
        runtimePaths.addAll(*paths)
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
        return showCommandLine.get() || logLevel.get() == LogLevel.DEBUG
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

            // Add runtime search paths (-rpath)
            runtimePaths.get().forEach { path ->
                add("-Wl,-rpath,$path")
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

            // Add symbol visibility control if specified
            if (exportSymbols.get().isNotEmpty() || hideSymbols.get().isNotEmpty()) {
                addAll(generateSymbolVisibilityFlags(outFile))
            }

            // Add output file
            add("-o")
            add(outFile.absolutePath)
        }

        logNormal("Linking shared library: ${outFile.name}")

        if (shouldShowCommandLine()) {
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
                append("Failed to link shared library: exit code ${result.exitValue}")
                if (allOutput.isNotEmpty()) {
                    appendLine()
                    append(allOutput)
                }
            }
            throw RuntimeException(errorMsg)
        }

        // Extract debug symbols before stripping if requested
        if (extractDebugSymbols.get()) {
            extractDebugInfo(outFile)
        }

        // Strip symbols if requested
        if (stripSymbols.get()) {
            stripLibrary(outFile)
        }

        val sizeKB = outFile.length() / 1024
        logNormal("Successfully linked ${outFile.name} (${sizeKB}KB)")
    }

    /**
     * Generate platform-specific symbol visibility flags.
     * Returns linker flags to control symbol export/hiding.
     */
    private fun generateSymbolVisibilityFlags(outFile: java.io.File): List<String> {
        return when (PlatformUtils.currentPlatform) {
            com.datadoghq.native.model.Platform.LINUX -> {
                generateLinuxVersionScript(outFile)
            }
            com.datadoghq.native.model.Platform.MACOS -> {
                generateMacOSExportList(outFile)
            }
        }
    }

    /**
     * Generate Linux version script for symbol visibility control.
     */
    private fun generateLinuxVersionScript(outFile: java.io.File): List<String> {
        val versionScript = java.io.File(temporaryDir, "${outFile.nameWithoutExtension}.ver")

        val scriptContent = buildString {
            appendLine("{")
            appendLine("  global:")

            // Export specified symbols
            exportSymbols.get().forEach { pattern ->
                appendLine("    $pattern;")
            }

            // Consolidate all hidden symbols in a single local section
            appendLine("  local:")

            // Explicitly hide specified symbols (override exports)
            hideSymbols.get().forEach { pattern ->
                appendLine("    $pattern;")
            }

            // Hide everything else unless it was explicitly exported
            if (exportSymbols.get().isNotEmpty() || hideSymbols.get().isNotEmpty()) {
                appendLine("    *;")
            }

            appendLine("};")
        }

        versionScript.writeText(scriptContent)
        logVerbose("Generated version script: ${versionScript.name}")

        return listOf("-Wl,--version-script=${versionScript.absolutePath}")
    }

    /**
     * Generate macOS exported symbols list for symbol visibility control.
     */
    private fun generateMacOSExportList(outFile: java.io.File): List<String> {
        val exportList = java.io.File(temporaryDir, "${outFile.nameWithoutExtension}.exp")

        // Warn if wildcards are used - macOS doesn't support them
        exportSymbols.get().forEach { pattern ->
            if (pattern.contains('*') || pattern.contains('?')) {
                logger.warn("Symbol pattern '$pattern' contains wildcards which are not supported on macOS. " +
                           "Pattern will be treated as a literal symbol name. " +
                           "Consider using -fvisibility compiler flags instead, or list symbols explicitly.")
            }
        }

        val listContent = buildString {
            // Export specified symbols (macOS needs leading underscore for C symbols)
            exportSymbols.get().forEach { pattern ->
                // Convert glob patterns to exact names or keep as-is
                // macOS export list doesn't support wildcards like Linux version scripts
                // For wildcards, we'd need to use -exported_symbols_list with all matching symbols
                // For now, treat patterns as literal symbol names
                val symbol = if (pattern.startsWith("_")) pattern else "_$pattern"
                appendLine(symbol)
            }
        }

        exportList.writeText(listContent)
        logVerbose("Generated export list: ${exportList.name}")

        val flags = mutableListOf<String>()

        // Add export list
        if (exportSymbols.get().isNotEmpty()) {
            flags.add("-Wl,-exported_symbols_list,${exportList.absolutePath}")
        }

        // For hiding, use -unexported_symbols_list if needed
        if (hideSymbols.get().isNotEmpty()) {
            val hideList = java.io.File(temporaryDir, "${outFile.nameWithoutExtension}.hide")
            val hideContent = buildString {
                hideSymbols.get().forEach { pattern ->
                    val symbol = if (pattern.startsWith("_")) pattern else "_$pattern"
                    appendLine(symbol)
                }
            }
            hideList.writeText(hideContent)
            flags.add("-Wl,-unexported_symbols_list,${hideList.absolutePath}")
        }

        return flags
    }

    private fun extractDebugInfo(libFile: java.io.File) {
        val debugDir = if (debugSymbolsDir.isPresent) {
            debugSymbolsDir.get().asFile
        } else {
            libFile.parentFile
        }
        debugDir.mkdirs()

        when (PlatformUtils.currentPlatform) {
            com.datadoghq.native.model.Platform.LINUX -> {
                extractDebugInfoLinux(libFile, debugDir)
            }
            com.datadoghq.native.model.Platform.MACOS -> {
                extractDebugInfoMacOS(libFile, debugDir)
            }
        }
    }

    private fun extractDebugInfoLinux(libFile: java.io.File, debugDir: java.io.File) {
        val debugFile = java.io.File(debugDir, "${libFile.name}.debug")

        logNormal("Extracting debug symbols to ${debugFile.name}...")

        // Extract debug symbols
        val extractResult = execOperations.exec {
            commandLine("objcopy", "--only-keep-debug", libFile.absolutePath, debugFile.absolutePath)
            isIgnoreExitValue = true
        }

        if (extractResult.exitValue != 0) {
            logger.warn("Failed to extract debug symbols (exit code ${extractResult.exitValue})")
            return
        }

        // Add GNU debuglink to stripped library
        val debuglinkResult = execOperations.exec {
            commandLine("objcopy", "--add-gnu-debuglink=${debugFile.absolutePath}", libFile.absolutePath)
            isIgnoreExitValue = true
        }

        if (debuglinkResult.exitValue != 0) {
            logger.warn("Failed to add debuglink (exit code ${debuglinkResult.exitValue})")
        } else {
            logNormal("Created debug file: ${debugFile.name} (${debugFile.length() / 1024}KB)")
        }
    }

    private fun extractDebugInfoMacOS(libFile: java.io.File, debugDir: java.io.File) {
        val dsymBundle = java.io.File(debugDir, "${libFile.name}.dSYM")

        logNormal("Creating dSYM bundle...")

        val result = execOperations.exec {
            commandLine("dsymutil", libFile.absolutePath, "-o", dsymBundle.absolutePath)
            isIgnoreExitValue = true
        }

        if (result.exitValue != 0) {
            logger.warn("Failed to create dSYM bundle (exit code ${result.exitValue})")
        } else {
            logNormal("Created dSYM bundle: ${dsymBundle.name}")
        }
    }

    private fun stripLibrary(libFile: java.io.File) {
        logNormal("Stripping symbols from ${libFile.name}...")

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
