/*
 * Copyright 2026, Datadog, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import org.gradle.api.DefaultTask
import org.gradle.api.file.ConfigurableFileCollection
import org.gradle.api.file.RegularFileProperty
import org.gradle.api.model.ObjectFactory
import org.gradle.api.provider.ListProperty
import org.gradle.api.provider.Property
import org.gradle.api.tasks.*
import org.gradle.process.ExecOperations

import javax.inject.Inject

/**
 * A configurable shared library linking task that directly invokes the linker without relying on
 * Gradle's cpp-library plugin. Supports advanced features like symbol management, library path
 * conveniences, debug symbol extraction, configurable logging, and post-link verification.
 *
 * <p>Basic usage (backward compatible):</p>
 * <pre>
 * tasks.register("linkLibRelease", SimpleLinkShared) {
 *     linker = 'g++'
 *     linkerArgs = ['-ldl', '-lpthread', '-static-libstdc++']
 *     objectFiles = fileTree("build/obj/release") { include '*.o' }
 *     outputFile = file("build/lib/release/libjavaProfiler.so")
 * }
 * </pre>
 *
 * <p>Advanced usage with symbol management and debug extraction:</p>
 * <pre>
 * tasks.register("linkLibRelease", SimpleLinkShared) {
 *     linker = 'g++'
 *     linkerArgs = ['-O3']
 *     objectFiles = fileTree("build/obj/release") { include '*.o' }
 *     outputFile = file("build/lib/release/libjavaProfiler.so")
 *
 *     // Symbol management
 *     soname = 'libjavaProfiler.so.1'
 *     stripSymbols = true
 *     exportSymbols = ['Java_*', 'JNI_*']
 *
 *     // Debug symbol extraction
 *     generateDebugInfo = true
 *     debugInfoFile = file("build/lib/release/libjavaProfiler.so.debug")
 *
 *     // Library conveniences
 *     lib 'pthread', 'dl', 'm'
 *     libPath '/usr/local/lib'
 *
 *     // Logging
 *     logLevel = CppBuildExtension.LogLevel.VERBOSE
 *     showCommandLine = true
 * }
 * </pre>
 */
class SimpleLinkShared extends DefaultTask {

    // === Core Properties (Backward Compatible) ===

    /**
     * The linker executable (usually same as compiler: 'g++', 'clang++').
     */
    @Input
    final Property<String> linker

    /**
     * Linker arguments (flags and libraries).
     * Example: ['-ldl', '-lpthread', '-Wl,--gc-sections']
     */
    @Input
    final ListProperty<String> linkerArgs

    /**
     * The object files to link.
     */
    @InputFiles
    @SkipWhenEmpty
    final ConfigurableFileCollection objectFiles

    /**
     * Additional library files to link against (optional).
     */
    @InputFiles
    @Optional
    final ConfigurableFileCollection libs

    /**
     * The output shared library file.
     */
    @OutputFile
    final RegularFileProperty outputFile

    // === Logging and Verbosity ===

    /**
     * Logging verbosity level.
     * Default: NORMAL
     */
    @Input
    @Optional
    final Property<CppBuildExtension.LogLevel> logLevel

    /**
     * Show full command line for the link operation.
     * Default: false (only shown at INFO level)
     */
    @Input
    @Optional
    final Property<Boolean> showCommandLine

    /**
     * Show linker map (symbol resolution details).
     * Default: false
     */
    @Input
    @Optional
    final Property<Boolean> showLinkerMap

    /**
     * Linker map output file (when showLinkerMap is true).
     * Default: null (stdout/stderr)
     */
    @OutputFile
    @Optional
    final RegularFileProperty linkerMapFile

    /**
     * Enable ANSI color codes in output.
     * Default: true
     */
    @Input
    @Optional
    final Property<Boolean> colorOutput

    // === Platform and Behavior ===

    /**
     * Target platform override (for cross-compilation).
     * Default: auto-detect
     */
    @Input
    @Optional
    final Property<String> targetPlatform

    /**
     * Auto-detect shared library flag based on platform.
     * Default: true (-shared on Linux, -dynamiclib on macOS)
     */
    @Input
    @Optional
    final Property<Boolean> autoDetectSharedFlag

    /**
     * Manual override for shared library flag.
     * Default: null (auto-detected)
     */
    @Input
    @Optional
    final Property<String> sharedLibraryFlag

    // === Symbol Management ===

    /**
     * Set soname for the shared library (Linux -Wl,-soname,name).
     * Default: null (no soname)
     */
    @Input
    @Optional
    final Property<String> soname

    /**
     * Set install_name for the shared library (macOS -Wl,-install_name,name).
     * Default: null (no install_name)
     */
    @Input
    @Optional
    final Property<String> installName

    /**
     * Strip symbols from the output library.
     * Default: false
     */
    @Input
    @Optional
    final Property<Boolean> stripSymbols

    /**
     * Symbol export patterns (wildcards supported).
     * Default: [] (export all)
     */
    @Input
    @Optional
    final ListProperty<String> exportSymbols

    /**
     * Symbol hide patterns (wildcards supported).
     * Default: [] (hide nothing)
     */
    @Input
    @Optional
    final ListProperty<String> hideSymbols

    // === Library Conveniences ===

    /**
     * Library search paths (-L flags).
     * Use libPath() method to add.
     */
    @Input
    @Optional
    final ListProperty<String> libraryPaths

    /**
     * Libraries to link against (-l flags).
     * Use lib() method to add.
     */
    @Input
    @Optional
    final ListProperty<String> libraries

    // === Debug Symbol Extraction ===

    /**
     * Extract debug symbols to separate file.
     * Default: false
     */
    @Input
    @Optional
    final Property<Boolean> generateDebugInfo

    /**
     * Debug info output file.
     * Default: null (auto-generated as ${outputFile}.debug)
     */
    @OutputFile
    @Optional
    final RegularFileProperty debugInfoFile

    // === Post-Link Verification ===

    /**
     * Verify shared library after linking (basic checks).
     * Default: true
     */
    @Input
    @Optional
    final Property<Boolean> verifySharedLib

    /**
     * Check for undefined symbols after linking.
     * Default: false
     */
    @Input
    @Optional
    final Property<Boolean> checkUndefinedSymbols

    /**
     * Report output file size after linking.
     * Default: true
     */
    @Input
    @Optional
    final Property<Boolean> reportSize

    /**
     * Capture stdout/stderr from linker.
     * Default: true
     */
    @Input
    @Optional
    final Property<Boolean> captureOutput

    @Inject
    SimpleLinkShared(ObjectFactory objects) {
        // Core properties
        linker = objects.property(String).convention('g++')
        linkerArgs = objects.listProperty(String).convention([])
        objectFiles = objects.fileCollection()
        libs = objects.fileCollection()
        outputFile = objects.fileProperty()

        // Logging
        logLevel = objects.property(CppBuildExtension.LogLevel)
            .convention(CppBuildExtension.LogLevel.NORMAL)
        showCommandLine = objects.property(Boolean).convention(false)
        showLinkerMap = objects.property(Boolean).convention(false)
        linkerMapFile = objects.fileProperty()
        colorOutput = objects.property(Boolean).convention(true)

        // Platform
        targetPlatform = objects.property(String)
        autoDetectSharedFlag = objects.property(Boolean).convention(true)
        sharedLibraryFlag = objects.property(String)

        // Symbol management
        soname = objects.property(String)
        installName = objects.property(String)
        stripSymbols = objects.property(Boolean).convention(false)
        exportSymbols = objects.listProperty(String).convention([])
        hideSymbols = objects.listProperty(String).convention([])

        // Library conveniences
        libraryPaths = objects.listProperty(String).convention([])
        libraries = objects.listProperty(String).convention([])

        // Debug extraction
        generateDebugInfo = objects.property(Boolean).convention(false)
        debugInfoFile = objects.fileProperty()

        // Verification
        verifySharedLib = objects.property(Boolean).convention(true)
        checkUndefinedSymbols = objects.property(Boolean).convention(false)
        reportSize = objects.property(Boolean).convention(true)

        // Output
        captureOutput = objects.property(Boolean).convention(true)
    }

    @Inject
    protected ExecOperations getExecOperations() {
        throw new UnsupportedOperationException()
    }

    // === Convenience Methods ===

    /**
     * Add library search paths (-L).
     * Example: libPath('/usr/local/lib', '/opt/lib')
     */
    void libPath(String... paths) {
        libraryPaths.addAll(paths)
    }

    /**
     * Add libraries to link against (-l).
     * Example: lib('pthread', 'dl', 'm')
     */
    void lib(String... libs) {
        libraries.addAll(libs)
    }

    /**
     * Apply conventions from extension (optional).
     */
    void applyConventions(CppBuildExtension extension) {
        linker.convention(extension.defaultLinker)
        logLevel.convention(extension.logLevel)
    }

    @TaskAction
    void link() {
        def outFile = outputFile.get().asFile
        outFile.parentFile.mkdirs()

        def objectPaths = objectFiles.files.collect { it.absolutePath }

        // Determine shared library flag
        def sharedFlag
        if (sharedLibraryFlag.isPresent()) {
            sharedFlag = sharedLibraryFlag.get()
        } else if (autoDetectSharedFlag.get()) {
            def osName = targetPlatform.isPresent()
                ? targetPlatform.get()
                : System.getProperty('os.name').toLowerCase()
            sharedFlag = osName.contains('mac') ? '-dynamiclib' : '-shared'
        } else {
            sharedFlag = '-shared'
        }

        // Build command line
        def cmdLine = [linker.get(), sharedFlag] + objectPaths

        // Add linker arguments
        cmdLine.addAll(linkerArgs.get())

        // Add library search paths (-L)
        libraryPaths.get().each { path ->
            cmdLine.add("-L${path}")
        }

        // Add libraries (-l)
        libraries.get().each { lib ->
            cmdLine.add("-l${lib}")
        }

        // Add library files if provided
        if (!libs.isEmpty()) {
            libs.files.each { lib ->
                cmdLine.add(lib.absolutePath)
            }
        }

        // Add soname/install_name
        def osName = targetPlatform.isPresent()
            ? targetPlatform.get()
            : System.getProperty('os.name').toLowerCase()
        if (soname.isPresent() && !osName.contains('mac')) {
            cmdLine.add("-Wl,-soname,${soname.get()}")
        }
        if (installName.isPresent() && osName.contains('mac')) {
            cmdLine.add("-Wl,-install_name,${installName.get()}")
        }

        // Add export/hide symbols
        exportSymbols.get().each { pattern ->
            cmdLine.add("-Wl,--export-dynamic-symbol=${pattern}")
        }
        hideSymbols.get().each { pattern ->
            cmdLine.add("-Wl,--exclude-libs=${pattern}")
        }

        // Add linker map if requested
        if (showLinkerMap.get() && linkerMapFile.isPresent()) {
            def mapFile = linkerMapFile.get().asFile
            mapFile.parentFile.mkdirs()
            if (osName.contains('mac')) {
                cmdLine.add("-Wl,-map,${mapFile.absolutePath}")
            } else {
                cmdLine.add("-Wl,-Map=${mapFile.absolutePath}")
            }
        }

        // Add output file
        cmdLine.addAll(['-o', outFile.absolutePath])

        logMessage(CppBuildExtension.LogLevel.NORMAL,
            "Linking shared library: ${outFile.name}")

        if (showCommandLine.get()) {
            logMessage(CppBuildExtension.LogLevel.DEBUG, cmdLine.join(' '))
        } else {
            logger.info("Command: ${cmdLine.join(' ')}")
        }

        // Execute linking
        def stdout = new ByteArrayOutputStream()
        def stderr = new ByteArrayOutputStream()

        def result = execOperations.exec { spec ->
            spec.commandLine cmdLine
            if (captureOutput.get()) {
                spec.standardOutput = stdout
                spec.errorOutput = stderr
            }
            spec.ignoreExitValue = true
        }

        if (result.exitValue != 0) {
            def errorMsg = "Linking failed with exit code ${result.exitValue}"
            if (captureOutput.get()) {
                def allOutput = (stdout.toString() + stderr.toString()).trim()
                if (allOutput) {
                    errorMsg += "\n${allOutput}"
                }
            }
            logger.error(errorMsg)
            throw new RuntimeException(errorMsg)
        }

        // Strip symbols if requested
        if (stripSymbols.get()) {
            logMessage(CppBuildExtension.LogLevel.VERBOSE, "Stripping symbols from ${outFile.name}")
            def stripCmd = ['strip', outFile.absolutePath]

            def stripResult = execOperations.exec { spec ->
                spec.commandLine stripCmd
                spec.ignoreExitValue = true
            }

            if (stripResult.exitValue != 0) {
                logger.warn("Failed to strip symbols (exit code ${stripResult.exitValue})")
            }
        }

        // Extract debug symbols if requested
        if (generateDebugInfo.get()) {
            def debugFile = debugInfoFile.isPresent()
                ? debugInfoFile.get().asFile
                : new File(outFile.parentFile, "${outFile.name}.debug")

            extractDebugSymbols(outFile, debugFile)
        }

        // Verify shared library if requested
        if (verifySharedLib.get()) {
            if (!outFile.exists()) {
                throw new RuntimeException("Output file does not exist: ${outFile.absolutePath}")
            }
            if (outFile.length() == 0) {
                throw new RuntimeException("Output file is empty: ${outFile.absolutePath}")
            }
        }

        // Check undefined symbols if requested
        if (checkUndefinedSymbols.get()) {
            def nmCmd = ['nm', '-u', outFile.absolutePath]
            def nmStdout = new ByteArrayOutputStream()

            def nmResult = execOperations.exec { spec ->
                spec.commandLine nmCmd
                spec.standardOutput = nmStdout
                spec.ignoreExitValue = true
            }

            if (nmResult.exitValue == 0) {
                def undefinedSymbols = nmStdout.toString().trim()
                if (undefinedSymbols) {
                    logger.warn("Undefined symbols found:\n${undefinedSymbols}")
                } else {
                    logMessage(CppBuildExtension.LogLevel.VERBOSE, "No undefined symbols")
                }
            }
        }

        if (reportSize.get()) {
            logMessage(CppBuildExtension.LogLevel.NORMAL,
                "Successfully linked: ${outFile.absolutePath} (${outFile.length()} bytes)")
        }
    }

    protected void extractDebugSymbols(File library, File debugFile) {
        debugFile.parentFile.mkdirs()

        logMessage(CppBuildExtension.LogLevel.VERBOSE,
            "Extracting debug symbols to ${debugFile.name}")

        // Copy debug info to separate file
        def objcopyCmd = ['objcopy', '--only-keep-debug', library.absolutePath, debugFile.absolutePath]

        def result = execOperations.exec { spec ->
            spec.commandLine objcopyCmd
            spec.ignoreExitValue = true
        }

        if (result.exitValue != 0) {
            logger.warn("Failed to extract debug symbols (exit code ${result.exitValue})")
            return
        }

        // Strip library
        def stripCmd = ['objcopy', '--strip-debug', library.absolutePath]

        result = execOperations.exec { spec ->
            spec.commandLine stripCmd
            spec.ignoreExitValue = true
        }

        if (result.exitValue != 0) {
            logger.warn("Failed to strip library (exit code ${result.exitValue})")
            return
        }

        // Add debug link
        def linkCmd = ['objcopy', "--add-gnu-debuglink=${debugFile.absolutePath}", library.absolutePath]

        result = execOperations.exec { spec ->
            spec.commandLine linkCmd
            spec.ignoreExitValue = true
        }

        if (result.exitValue != 0) {
            logger.warn("Failed to add debug link (exit code ${result.exitValue})")
            return
        }

        logMessage(CppBuildExtension.LogLevel.NORMAL,
            "Debug symbols extracted: ${debugFile.absolutePath} (${debugFile.length()} bytes)")
    }

    protected void logMessage(CppBuildExtension.LogLevel level, String message) {
        def currentLevel = logLevel.get()

        if (currentLevel == CppBuildExtension.LogLevel.DEBUG ||
            (currentLevel == CppBuildExtension.LogLevel.VERBOSE && level != CppBuildExtension.LogLevel.DEBUG) ||
            (currentLevel == CppBuildExtension.LogLevel.NORMAL && level == CppBuildExtension.LogLevel.NORMAL) ||
            (currentLevel == CppBuildExtension.LogLevel.QUIET && level == CppBuildExtension.LogLevel.QUIET)) {

            switch (level) {
                case CppBuildExtension.LogLevel.DEBUG:
                    logger.info(message)
                    break
                case CppBuildExtension.LogLevel.VERBOSE:
                    logger.info(message)
                    break
                default:
                    logger.lifecycle(message)
            }
        }
    }
}
