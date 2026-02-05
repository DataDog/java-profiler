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
import org.gradle.api.NamedDomainObjectContainer
import org.gradle.api.file.ConfigurableFileCollection
import org.gradle.api.file.DirectoryProperty
import org.gradle.api.model.ObjectFactory
import org.gradle.api.provider.ListProperty
import org.gradle.api.provider.Property
import org.gradle.api.tasks.*
import org.gradle.process.ExecOperations

import javax.inject.Inject
import java.util.concurrent.ConcurrentLinkedQueue
import java.util.concurrent.atomic.AtomicInteger

/**
 * A configurable C++ compilation task that directly invokes gcc/clang without relying on
 * Gradle's cpp-library plugin. Supports advanced features like source sets, per-directory
 * compiler flags, configurable logging, and error handling modes.
 *
 * <p>Basic usage (backward compatible):</p>
 * <pre>
 * tasks.register("compile", SimpleCppCompile) {
 *     compiler = 'g++'
 *     compilerArgs = ['-O3', '-fPIC', '-std=c++17']
 *     sources = fileTree('src/main/cpp') { include '**&#47;*.{c,cc,cpp}' }
 *     includes = files('src/main/cpp', "${System.env.JAVA_HOME}/include")
 *     objectFileDir = file("build/obj")
 * }
 * </pre>
 *
 * <p>Advanced usage with source sets:</p>
 * <pre>
 * tasks.register("compile", SimpleCppCompile) {
 *     compiler = 'clang++'
 *     compilerArgs = ['-Wall', '-O3']
 *
 *     sourceSets {
 *         main {
 *             sources = fileTree('src/main/cpp')
 *             compilerArgs = ['-fPIC']
 *         }
 *         legacy {
 *             sources = fileTree('src/legacy')
 *             compilerArgs = ['-Wno-deprecated', '-std=c++11']
 *             excludes = ['**&#47;broken/*.cpp']
 *         }
 *     }
 *
 *     logLevel = CppBuildExtension.LogLevel.VERBOSE
 *     errorHandling = CppBuildExtension.ErrorHandlingMode.COLLECT_ALL
 *     objectFileDir = file("build/obj")
 * }
 * </pre>
 */
class SimpleCppCompile extends DefaultTask {

    // === Core Properties (Backward Compatible) ===

    /**
     * The C++ compiler executable (e.g., 'g++', 'clang++', or full path).
     */
    @Input
    final Property<String> compiler

    /**
     * Compiler arguments (flags) to pass to the compiler.
     * Example: ['-O3', '-fPIC', '-std=c++17', '-DNDEBUG']
     */
    @Input
    final ListProperty<String> compilerArgs

    /**
     * The C++ source files to compile (simple mode).
     * When sourceSets is used, this property is ignored.
     */
    @InputFiles
    @SkipWhenEmpty
    final ConfigurableFileCollection sources

    /**
     * Include directories for header file lookup.
     */
    @InputFiles
    @Optional
    final ConfigurableFileCollection includes

    /**
     * Output directory for object files.
     */
    @OutputDirectory
    final DirectoryProperty objectFileDir

    // === Advanced Source Configuration ===

    /**
     * Named source sets for advanced source directory configuration.
     * Allows per-directory compiler flags, include/exclude patterns, and file filtering.
     */
    @Nested
    @Optional
    final NamedDomainObjectContainer<SourceSet> sourceSets

    // === Logging and Verbosity ===

    /**
     * Logging verbosity level.
     * Default: NORMAL
     */
    @Input
    @Optional
    final Property<CppBuildExtension.LogLevel> logLevel

    /**
     * Progress reporting interval (log every N files during compilation).
     * Default: 10
     */
    @Input
    @Optional
    final Property<Integer> progressReportInterval

    /**
     * Show full command line for each file compilation.
     * Default: false (only shown at INFO level)
     */
    @Input
    @Optional
    final Property<Boolean> showCommandLines

    /**
     * Enable ANSI color codes in output.
     * Default: true
     */
    @Input
    @Optional
    final Property<Boolean> colorOutput

    // === Error Handling ===

    /**
     * Error handling mode.
     * FAIL_FAST: Stop on first compilation error (default)
     * COLLECT_ALL: Compile all files, collect errors, report at end
     */
    @Input
    @Optional
    final Property<CppBuildExtension.ErrorHandlingMode> errorHandling

    /**
     * Maximum number of errors to show when using COLLECT_ALL mode.
     * Default: 10
     */
    @Input
    @Optional
    final Property<Integer> maxErrorsToShow

    /**
     * Treat compiler warnings as errors (-Werror).
     * Default: false
     */
    @Input
    @Optional
    final Property<Boolean> treatWarningsAsErrors

    // === Compilation Behavior ===

    /**
     * Number of parallel compilation jobs.
     * Default: Runtime.runtime.availableProcessors()
     */
    @Input
    @Optional
    final Property<Integer> parallelJobs

    /**
     * Skip Gradle's up-to-date checking and always recompile.
     * Default: false
     */
    @Input
    @Optional
    final Property<Boolean> skipUpToDateCheck

    // === Convenience Properties ===

    /**
     * Convenience property for define flags (-D).
     * Use define() method to add: define('DEBUG', 'VERSION="1.0"')
     */
    @Input
    @Optional
    final ListProperty<String> defines

    /**
     * Convenience property for undefine flags (-U).
     * Use undefine() method to add: undefine('NDEBUG')
     */
    @Input
    @Optional
    final ListProperty<String> undefines

    /**
     * C++ standard version (e.g., 'c++17', 'c++20').
     * Use standard() method to set: standard('c++20')
     */
    @Input
    @Optional
    final Property<String> standardVersion

    // === Platform and Toolchain ===

    /**
     * Target platform override (for cross-compilation).
     * Default: auto-detect
     */
    @Input
    @Optional
    final Property<String> targetPlatform

    /**
     * Target architecture override (for cross-compilation).
     * Default: auto-detect
     */
    @Input
    @Optional
    final Property<String> targetArch

    // === Output Customization ===

    /**
     * Capture stdout/stderr from compiler.
     * Default: true
     */
    @Input
    @Optional
    final Property<Boolean> captureOutput

    @Inject
    SimpleCppCompile(ObjectFactory objects) {
        // Core properties
        compiler = objects.property(String).convention('g++')
        compilerArgs = objects.listProperty(String).convention([])
        sources = objects.fileCollection()
        includes = objects.fileCollection()
        objectFileDir = objects.directoryProperty()

        // Source sets
        sourceSets = objects.domainObjectContainer(SourceSet)

        // Logging
        logLevel = objects.property(CppBuildExtension.LogLevel)
            .convention(CppBuildExtension.LogLevel.NORMAL)
        progressReportInterval = objects.property(Integer).convention(10)
        showCommandLines = objects.property(Boolean).convention(false)
        colorOutput = objects.property(Boolean).convention(true)

        // Error handling
        errorHandling = objects.property(CppBuildExtension.ErrorHandlingMode)
            .convention(CppBuildExtension.ErrorHandlingMode.FAIL_FAST)
        maxErrorsToShow = objects.property(Integer).convention(10)
        treatWarningsAsErrors = objects.property(Boolean).convention(false)

        // Compilation behavior
        parallelJobs = objects.property(Integer)
            .convention(Runtime.runtime.availableProcessors())
        skipUpToDateCheck = objects.property(Boolean).convention(false)

        // Convenience
        defines = objects.listProperty(String).convention([])
        undefines = objects.listProperty(String).convention([])
        standardVersion = objects.property(String)

        // Platform
        targetPlatform = objects.property(String)
        targetArch = objects.property(String)

        // Output
        captureOutput = objects.property(Boolean).convention(true)
    }

    @Inject
    protected ExecOperations getExecOperations() {
        throw new UnsupportedOperationException()
    }

    // === Convenience Methods ===

    /**
     * Add define flags (-D).
     * Example: define('DEBUG', 'VERSION="1.0"')
     */
    void define(String... defs) {
        defines.addAll(defs)
    }

    /**
     * Add undefine flags (-U).
     * Example: undefine('NDEBUG')
     */
    void undefine(String... undefs) {
        undefines.addAll(undefs)
    }

    /**
     * Set C++ standard version.
     * Example: standard('c++20')
     */
    void standard(String std) {
        standardVersion.set(std)
    }

    /**
     * Apply conventions from extension (optional).
     */
    void applyConventions(CppBuildExtension extension) {
        compiler.convention(extension.defaultCompiler)
        parallelJobs.convention(extension.parallelJobs)
        logLevel.convention(extension.logLevel)
        progressReportInterval.convention(extension.progressReportInterval)
        errorHandling.convention(extension.errorHandling)
        maxErrorsToShow.convention(extension.maxErrorsToShow)
    }

    @TaskAction
    void compile() {
        def objDir = objectFileDir.get().asFile
        objDir.mkdirs()

        // Determine which sources to compile
        def allSourceFiles = []
        def sourceSetMap = [:]  // Map of source file to its source set

        if (sourceSets.isEmpty()) {
            // Simple mode: use sources property
            allSourceFiles = sources.files.toList()
        } else {
            // Advanced mode: use source sets
            sourceSets.each { sourceSet ->
                def setFiles = sourceSet.sources.files.toList()

                // Apply include/exclude patterns
                if (!sourceSet.includes.get().isEmpty() || !sourceSet.excludes.get().isEmpty()) {
                    setFiles = setFiles.findAll { file ->
                        def relativePath = file.absolutePath
                        def included = sourceSet.includes.get().any { pattern ->
                            matchesPattern(relativePath, pattern)
                        }
                        def excluded = sourceSet.excludes.get().any { pattern ->
                            matchesPattern(relativePath, pattern)
                        }
                        included && !excluded
                    }
                }

                // Apply file filter if provided
                if (sourceSet.fileFilter.isPresent()) {
                    def filter = sourceSet.fileFilter.get()
                    setFiles = setFiles.collect { file ->
                        filter.call(file)
                    }
                }

                setFiles.each { file ->
                    allSourceFiles.add(file)
                    sourceSetMap[file] = sourceSet
                }
            }
        }

        if (allSourceFiles.isEmpty()) {
            logMessage(CppBuildExtension.LogLevel.NORMAL, "No source files to compile")
            return
        }

        // Build base compiler arguments
        def baseArgs = []
        baseArgs.addAll(compilerArgs.get())

        // Add defines
        defines.get().each { define ->
            baseArgs.add("-D${define}")
        }

        // Add undefines
        undefines.get().each { undef ->
            baseArgs.add("-U${undef}")
        }

        // Add standard version
        if (standardVersion.isPresent()) {
            baseArgs.add("-std=${standardVersion.get()}")
        }

        // Add treat warnings as errors
        if (treatWarningsAsErrors.get()) {
            baseArgs.add("-Werror")
        }

        // Build include arguments
        def includeArgs = []
        if (includes != null && !includes.isEmpty()) {
            includes.files.each { dir ->
                if (dir.exists()) {
                    includeArgs.addAll(['-I', dir.absolutePath])
                }
            }
        }

        def errors = new ConcurrentLinkedQueue<String>()
        def compiled = new AtomicInteger(0)
        def total = allSourceFiles.size()

        logMessage(CppBuildExtension.LogLevel.NORMAL,
            "Compiling ${total} C++ source file${total == 1 ? '' : 's'} with ${compiler.get()}...")

        // Compile files
        def stream = errorHandling.get() == CppBuildExtension.ErrorHandlingMode.FAIL_FAST ?
            allSourceFiles.stream() :  // Sequential for fail-fast
            allSourceFiles.parallelStream()  // Parallel for collect-all

        stream.forEach { sourceFile ->
            try {
                // Get source set specific args
                def sourceSet = sourceSetMap[sourceFile]
                def fileSpecificArgs = sourceSet ? sourceSet.compilerArgs.get() : []

                // Determine object file name
                def baseName = sourceFile.name.substring(0, sourceFile.name.lastIndexOf('.'))
                def objectFile = new File(objDir, baseName + '.o')

                // Build full command line
                def cmdLine = [compiler.get()] + baseArgs + fileSpecificArgs + includeArgs +
                    ['-c', sourceFile.absolutePath, '-o', objectFile.absolutePath]

                // Show command line if requested
                if (showCommandLines.get()) {
                    logMessage(CppBuildExtension.LogLevel.DEBUG, cmdLine.join(' '))
                }

                // Execute compilation
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
                    def errorMsg = "Failed to compile ${sourceFile.name}: exit code ${result.exitValue}"
                    if (captureOutput.get()) {
                        def allOutput = (stdout.toString() + stderr.toString()).trim()
                        if (allOutput) {
                            errorMsg += "\n${allOutput}"
                        }
                    }

                    if (errorHandling.get() == CppBuildExtension.ErrorHandlingMode.FAIL_FAST) {
                        logger.error(errorMsg)
                        throw new RuntimeException(errorMsg)
                    } else {
                        errors.add(errorMsg)
                    }
                } else {
                    def count = compiled.incrementAndGet()
                    def interval = progressReportInterval.get()
                    if (count % interval == 0 || count == total) {
                        logMessage(CppBuildExtension.LogLevel.VERBOSE, "  Compiled ${count}/${total} files...")
                    }
                }
            } catch (Exception e) {
                def errorMsg = "Exception compiling ${sourceFile.name}: ${e.message}"
                if (errorHandling.get() == CppBuildExtension.ErrorHandlingMode.FAIL_FAST) {
                    logger.error(errorMsg)
                    throw e
                } else {
                    errors.add(errorMsg)
                }
            }
        }

        // Report errors if any
        if (!errors.isEmpty()) {
            def errorCount = errors.size()
            def maxToShow = maxErrorsToShow.get()
            def errorsToShow = errors.take(maxToShow)

            errorsToShow.each { logger.error(it) }

            if (errorCount > maxToShow) {
                logger.error("... and ${errorCount - maxToShow} more error(s)")
            }

            throw new RuntimeException("Compilation failed with ${errorCount} error(s)")
        }

        logMessage(CppBuildExtension.LogLevel.NORMAL,
            "Successfully compiled ${total} file${total == 1 ? '' : 's'} to ${objDir.absolutePath}")
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

    private static boolean matchesPattern(String path, String pattern) {
        // Simple Ant-style pattern matching
        def regex = pattern
            .replace('.', '\\.')
            .replace('**/', '.*')
            .replace('**', '.*')
            .replace('*', '[^/]*')
            .replace('?', '.')

        return path.matches(".*${regex}\$")
    }
}
