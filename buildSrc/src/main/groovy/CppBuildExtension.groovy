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

import org.gradle.api.model.ObjectFactory
import org.gradle.api.provider.ListProperty
import org.gradle.api.provider.Property

import javax.inject.Inject

/**
 * Optional extension for project-wide C++ build configuration defaults.
 *
 * <p>This extension is OPTIONAL. Tasks can be configured directly without using this extension.
 * It provides a convenient way to set defaults that multiple tasks can inherit.
 *
 * <p>Usage in build.gradle:</p>
 * <pre>
 * cppBuild {
 *     defaultCompiler = 'clang++'
 *     logLevel = LogLevel.VERBOSE
 *     errorHandling = ErrorHandlingMode.COLLECT_ALL
 *     parallelJobs = 16
 * }
 *
 * // Tasks can then inherit these defaults
 * tasks.register("compile", SimpleCppCompile) {
 *     applyConventions(extensions.cppBuild)
 *     // ... task-specific configuration
 * }
 * </pre>
 */
class CppBuildExtension {

    /**
     * Logging verbosity level.
     */
    enum LogLevel {
        /** Only errors */
        QUIET,
        /** Standard lifecycle messages (default) */
        NORMAL,
        /** Detailed progress information */
        VERBOSE,
        /** Full command lines and output */
        DEBUG
    }

    /**
     * Error handling strategy for compilation.
     */
    enum ErrorHandlingMode {
        /** Stop on first error (default) */
        FAIL_FAST,
        /** Compile all files, collect all errors, report at end */
        COLLECT_ALL
    }

    /**
     * Default compiler executable.
     * Default: 'g++'
     */
    final Property<String> defaultCompiler

    /**
     * Default linker executable.
     * Default: 'g++'
     */
    final Property<String> defaultLinker

    /**
     * Global compiler arguments applied to all compilations.
     * Default: []
     */
    final ListProperty<String> globalCompilerArgs

    /**
     * Global linker arguments applied to all linking.
     * Default: []
     */
    final ListProperty<String> globalLinkerArgs

    /**
     * Logging verbosity level.
     * Default: NORMAL
     */
    final Property<LogLevel> logLevel

    /**
     * Progress reporting interval (log every N files during compilation).
     * Default: 10
     */
    final Property<Integer> progressReportInterval

    /**
     * Number of parallel compilation jobs.
     * Default: Runtime.runtime.availableProcessors()
     */
    final Property<Integer> parallelJobs

    /**
     * Maximum memory per job in MB (guidance only, not enforced).
     * Default: 2048
     */
    final Property<Integer> maxMemoryPerJob

    /**
     * Error handling mode.
     * Default: FAIL_FAST
     */
    final Property<ErrorHandlingMode> errorHandling

    /**
     * Maximum number of errors to show when using COLLECT_ALL mode.
     * Default: 10
     */
    final Property<Integer> maxErrorsToShow

    /**
     * Automatically detect platform for shared library flags, etc.
     * Default: true
     */
    final Property<Boolean> autoDetectPlatform

    @Inject
    CppBuildExtension(ObjectFactory objects) {
        this.defaultCompiler = objects.property(String)
            .convention('g++')

        this.defaultLinker = objects.property(String)
            .convention('g++')

        this.globalCompilerArgs = objects.listProperty(String)
            .convention([])

        this.globalLinkerArgs = objects.listProperty(String)
            .convention([])

        this.logLevel = objects.property(LogLevel)
            .convention(LogLevel.NORMAL)

        this.progressReportInterval = objects.property(Integer)
            .convention(10)

        this.parallelJobs = objects.property(Integer)
            .convention(Runtime.runtime.availableProcessors())

        this.maxMemoryPerJob = objects.property(Integer)
            .convention(2048)

        this.errorHandling = objects.property(ErrorHandlingMode)
            .convention(ErrorHandlingMode.FAIL_FAST)

        this.maxErrorsToShow = objects.property(Integer)
            .convention(10)

        this.autoDetectPlatform = objects.property(Boolean)
            .convention(true)
    }
}
