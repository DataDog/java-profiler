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

import org.gradle.api.file.DirectoryProperty
import org.gradle.api.file.RegularFileProperty
import org.gradle.api.model.ObjectFactory
import org.gradle.api.provider.Property
import org.gradle.api.provider.MapProperty

import javax.inject.Inject

/**
 * Configuration extension for the DebugSymbolsPlugin.
 *
 * <p>This extension provides a declarative DSL for configuring debug symbol extraction
 * from native libraries. It supports both Linux (objcopy/strip) and macOS (dsymutil/strip)
 * workflows for splitting debug information into separate files.
 *
 * <p>Example usage:
 * <pre>
 * debugSymbols {
 *     // Required: The linked library file to extract symbols from
 *     libraryFile = file('build/lib/libjavaProfiler.so')
 *
 *     // Required: Output directory for debug symbols
 *     debugOutputDir = file('build/lib/debug')
 *
 *     // Required: Output directory for stripped libraries
 *     strippedOutputDir = file('build/lib/stripped')
 *
 *     // Optional: Target directory for final artifacts (debug + stripped)
 *     targetDir = file('build/native/lib')
 *
 *     // Optional: Skip extraction even if tools are available
 *     skipExtraction = false
 *
 *     // Optional: Library file extension (.so, .dylib)
 *     libraryExtension = 'so'
 * }
 * </pre>
 */
class DebugSymbolsExtension {

    /**
     * The linked library file to extract debug symbols from.
     * This should be the output of a link task before stripping.
     */
    final RegularFileProperty libraryFile

    /**
     * Output directory for extracted debug symbol files.
     * On Linux: Creates .debug files (e.g., libjavaProfiler.so.debug)
     * On macOS: Creates .dSYM bundles (e.g., libjavaProfiler.dylib.dSYM/)
     */
    final DirectoryProperty debugOutputDir

    /**
     * Output directory for stripped library files.
     * Contains the production-ready libraries with debug symbols removed.
     */
    final DirectoryProperty strippedOutputDir

    /**
     * Optional target directory for copying final artifacts.
     * If set, both debug symbols and stripped libraries will be copied here.
     */
    final DirectoryProperty targetDir

    /**
     * Skip debug symbol extraction even if tools are available.
     * Useful for faster builds when debug symbols are not needed.
     * Default: false
     */
    final Property<Boolean> skipExtraction

    /**
     * Library file extension without the dot (.so, .dylib, .dll).
     * Used to construct output file names.
     * Default: Detected based on platform ('so' for Linux, 'dylib' for macOS)
     */
    final Property<String> libraryExtension

    /**
     * Base name of the library file without extension.
     * Used to construct output file names.
     * Default: 'libjavaProfiler'
     */
    final Property<String> libraryBaseName

    /**
     * Custom tool paths for debug symbol extraction.
     * Useful when tools are not in PATH or need specific versions.
     * Keys: 'objcopy', 'strip', 'dsymutil'
     */
    final MapProperty<String, String> toolPaths

    @Inject
    DebugSymbolsExtension(ObjectFactory objects) {
        this.libraryFile = objects.fileProperty()
        this.debugOutputDir = objects.directoryProperty()
        this.strippedOutputDir = objects.directoryProperty()
        this.targetDir = objects.directoryProperty()

        this.skipExtraction = objects.property(Boolean).convention(false)
        this.libraryExtension = objects.property(String)
        this.libraryBaseName = objects.property(String).convention('libjavaProfiler')

        this.toolPaths = objects.mapProperty(String, String).convention([:])
    }
}
