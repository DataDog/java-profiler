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
 * A configurable executable linking task for linking object files into an executable binary.
 * Used for Google Test binaries, fuzzer targets, and benchmark executables. Supports advanced
 * features like library path conveniences, rpath management, debug symbol extraction, configurable
 * logging, and post-link verification.
 *
 * <p>Basic usage (backward compatible):</p>
 * <pre>
 * tasks.register("linkGtestCallTrace", SimpleLinkExecutable) {
 *     linker = 'g++'
 *     linkerArgs = ['-lgtest', '-lgtest_main', '-lpthread']
 *     objectFiles = fileTree("build/obj/gtest/callTrace") { include '*.o' }
 *     outputFile = file("build/bin/gtest/callTrace_test")
 * }
 * </pre>
 *
 * <p>Advanced usage with library conveniences and debug extraction:</p>
 * <pre>
 * tasks.register("linkBenchmark", SimpleLinkExecutable) {
 *     linker = 'g++'
 *     linkerArgs = ['-O3']
 *     objectFiles = fileTree("build/obj/benchmark") { include '*.o' }
 *     outputFile = file("build/bin/benchmark_suite")
 *
 *     // Library conveniences
 *     lib 'pthread', 'dl', 'benchmark'
 *     libPath '/usr/local/lib'
 *     runtimePath '/opt/lib', '/usr/local/lib'
 *
 *     // Symbol management
 *     stripSymbols = true
 *
 *     // Debug symbol extraction
 *     generateDebugInfo = true
 *     debugInfoFile = file("build/bin/benchmark_suite.debug")
 *
 *     // Logging
 *     logLevel = CppBuildExtension.LogLevel.VERBOSE
 *     showCommandLine = true
 * }
 * </pre>
 */
class SimpleLinkExecutable extends DefaultTask {

    // === Core Properties (Backward Compatible) ===

    /**
     * The linker executable (usually same as compiler: 'g++', 'clang++').
     */
    @Input
    final Property<String> linker

    /**
     * Linker arguments (flags and libraries).
     * Example: ['-lgtest', '-lgtest_main', '-lpthread']
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
     * The output executable file.
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
     * Enable ANSI color codes in output.
     * Default: true
     */
    @Input
    @Optional
    final Property<Boolean> colorOutput

    // === Executable Properties ===

    /**
     * Set executable permission on output file.
     * Default: true
     */
    @Input
    @Optional
    final Property<Boolean> setExecutablePermission

    /**
     * Executable permission bits (octal string).
     * Default: "755"
     */
    @Input
    @Optional
    final Property<String> executablePermissions

    /**
     * Strip symbols from the output executable.
     * Default: false
     */
    @Input
    @Optional
    final Property<Boolean> stripSymbols

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

    /**
     * Runtime library search paths (-rpath flags).
     * Use runtimePath() method to add.
     */
    @Input
    @Optional
    final ListProperty<String> rpath

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
     * Verify executable after linking (basic checks).
     * Default: true
     */
    @Input
    @Optional
    final Property<Boolean> verifyExecutable

    /**
     * Check library dependencies with ldd (Linux/macOS).
     * Default: false
     */
    @Input
    @Optional
    final Property<Boolean> checkLdd

    /**
     * Report output file size after linking.
     * Default: true
     */
    @Input
    @Optional
    final Property<Boolean> reportSize

    // === Testing Support ===

    /**
     * Run a basic sanity test after linking.
     * Default: false
     */
    @Input
    @Optional
    final Property<Boolean> runSanityTest

    /**
     * Arguments for sanity test (e.g., ['--version']).
     * Default: []
     */
    @Input
    @Optional
    final ListProperty<String> sanityTestArgs

    /**
     * Capture stdout/stderr from linker.
     * Default: true
     */
    @Input
    @Optional
    final Property<Boolean> captureOutput

    @Inject
    SimpleLinkExecutable(ObjectFactory objects) {
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
        colorOutput = objects.property(Boolean).convention(true)

        // Executable properties
        setExecutablePermission = objects.property(Boolean).convention(true)
        executablePermissions = objects.property(String).convention("755")
        stripSymbols = objects.property(Boolean).convention(false)

        // Library conveniences
        libraryPaths = objects.listProperty(String).convention([])
        libraries = objects.listProperty(String).convention([])
        rpath = objects.listProperty(String).convention([])

        // Debug extraction
        generateDebugInfo = objects.property(Boolean).convention(false)
        debugInfoFile = objects.fileProperty()

        // Verification
        verifyExecutable = objects.property(Boolean).convention(true)
        checkLdd = objects.property(Boolean).convention(false)
        reportSize = objects.property(Boolean).convention(true)

        // Testing
        runSanityTest = objects.property(Boolean).convention(false)
        sanityTestArgs = objects.listProperty(String).convention([])

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
     * Add runtime library search paths (-rpath).
     * Example: runtimePath('/opt/lib', '/usr/local/lib')
     */
    void runtimePath(String... paths) {
        rpath.addAll(paths)
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

        // Build command line
        def cmdLine = [linker.get()] + objectPaths

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

        // Add rpath settings
        rpath.get().each { path ->
            def osName = System.getProperty('os.name').toLowerCase()
            if (osName.contains('mac')) {
                cmdLine.add("-Wl,-rpath,${path}")
            } else {
                cmdLine.add("-Wl,-rpath,${path}")
            }
        }

        // Add library files if provided
        if (!libs.isEmpty()) {
            libs.files.each { lib ->
                cmdLine.add(lib.absolutePath)
            }
        }

        // Add output file
        cmdLine.addAll(['-o', outFile.absolutePath])

        logMessage(CppBuildExtension.LogLevel.NORMAL,
            "Linking executable: ${outFile.name}")

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

        // Set executable permission if requested
        if (setExecutablePermission.get()) {
            def permissions = executablePermissions.get()
            try {
                outFile.setExecutable(true, false)
                outFile.setReadable(true, false)
                outFile.setWritable(true, true)
            } catch (Exception e) {
                logger.warn("Failed to set executable permissions: ${e.message}")
            }
        }

        // Verify executable if requested
        if (verifyExecutable.get()) {
            if (!outFile.exists()) {
                throw new RuntimeException("Output file does not exist: ${outFile.absolutePath}")
            }
            if (outFile.length() == 0) {
                throw new RuntimeException("Output file is empty: ${outFile.absolutePath}")
            }
            if (!outFile.canExecute()) {
                logger.warn("Output file is not executable: ${outFile.absolutePath}")
            }
        }

        // Check library dependencies if requested
        if (checkLdd.get()) {
            def osName = System.getProperty('os.name').toLowerCase()
            def lddCmd = osName.contains('mac') ? ['otool', '-L', outFile.absolutePath] : ['ldd', outFile.absolutePath]
            def lddStdout = new ByteArrayOutputStream()

            def lddResult = execOperations.exec { spec ->
                spec.commandLine lddCmd
                spec.standardOutput = lddStdout
                spec.ignoreExitValue = true
            }

            if (lddResult.exitValue == 0) {
                logMessage(CppBuildExtension.LogLevel.VERBOSE, "Library dependencies:\n${lddStdout.toString().trim()}")
            } else {
                logger.warn("Failed to check library dependencies (exit code ${lddResult.exitValue})")
            }
        }

        // Run sanity test if requested
        if (runSanityTest.get()) {
            def testCmd = [outFile.absolutePath] + sanityTestArgs.get()
            def testStdout = new ByteArrayOutputStream()

            def testResult = execOperations.exec { spec ->
                spec.commandLine testCmd
                spec.standardOutput = testStdout
                spec.ignoreExitValue = true
            }

            if (testResult.exitValue == 0) {
                logMessage(CppBuildExtension.LogLevel.VERBOSE, "Sanity test passed")
            } else {
                logger.warn("Sanity test failed (exit code ${testResult.exitValue})")
            }
        }

        if (reportSize.get()) {
            logMessage(CppBuildExtension.LogLevel.NORMAL,
                "Successfully linked: ${outFile.absolutePath} (${outFile.length()} bytes)")
        }
    }

    protected void extractDebugSymbols(File executable, File debugFile) {
        debugFile.parentFile.mkdirs()

        logMessage(CppBuildExtension.LogLevel.VERBOSE,
            "Extracting debug symbols to ${debugFile.name}")

        // Copy debug info to separate file
        def objcopyCmd = ['objcopy', '--only-keep-debug', executable.absolutePath, debugFile.absolutePath]

        def result = execOperations.exec { spec ->
            spec.commandLine objcopyCmd
            spec.ignoreExitValue = true
        }

        if (result.exitValue != 0) {
            logger.warn("Failed to extract debug symbols (exit code ${result.exitValue})")
            return
        }

        // Strip executable
        def stripCmd = ['objcopy', '--strip-debug', executable.absolutePath]

        result = execOperations.exec { spec ->
            spec.commandLine stripCmd
            spec.ignoreExitValue = true
        }

        if (result.exitValue != 0) {
            logger.warn("Failed to strip executable (exit code ${result.exitValue})")
            return
        }

        // Add debug link
        def linkCmd = ['objcopy', "--add-gnu-debuglink=${debugFile.absolutePath}", executable.absolutePath]

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
