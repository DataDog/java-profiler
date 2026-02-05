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

import org.gradle.api.Plugin
import org.gradle.api.Project
import org.gradle.api.tasks.Exec
import org.gradle.api.tasks.Copy

/**
 * Gradle plugin for extracting and managing debug symbols from native libraries.
 *
 * <p>This plugin automates the process of splitting debug information from production
 * binaries, reducing deployed library size while maintaining separate debug files for
 * debugging and symbolication.
 *
 * <p>Supported platforms:
 * <ul>
 *   <li><b>Linux</b>: Uses objcopy to extract symbols and add GNU debuglink</li>
 *   <li><b>macOS</b>: Uses dsymutil to create .dSYM bundles</li>
 * </ul>
 *
 * <p>The plugin creates the following task workflow:
 * <pre>
 * extractDebugSymbols → addDebugLink (Linux only) → stripLibrary → copyDebugFiles
 * </pre>
 *
 * <p>Usage:
 * <pre>
 * apply plugin: DebugSymbolsPlugin
 *
 * debugSymbols {
 *     libraryFile = file('build/lib/libjavaProfiler.so')
 *     debugOutputDir = file('build/lib/debug')
 *     strippedOutputDir = file('build/lib/stripped')
 *     targetDir = file('build/native/lib')
 * }
 * </pre>
 *
 * <p>The plugin automatically:
 * <ul>
 *   <li>Detects platform and selects appropriate tools</li>
 *   <li>Checks tool availability and warns if missing</li>
 *   <li>Skips extraction if tools are unavailable or explicitly disabled</li>
 *   <li>Creates platform-specific debug symbol files (.debug on Linux, .dSYM on macOS)</li>
 *   <li>Strips production libraries to minimize size</li>
 *   <li>Maintains GNU debuglink on Linux for symbol resolution</li>
 * </ul>
 */
class DebugSymbolsPlugin implements Plugin<Project> {

    @Override
    void apply(Project project) {
        // Create extension
        def extension = project.extensions.create('debugSymbols', DebugSymbolsExtension, project.objects)

        // Set platform-specific defaults
        if (isMac()) {
            extension.libraryExtension.convention('dylib')
        } else if (isLinux()) {
            extension.libraryExtension.convention('so')
        }

        // Add helper method to project for per-config setup
        project.ext.setupDebugExtraction = { config, linkTask, copyTaskName = null ->
            // Only for release builds
            if (config.name != 'release' || !config.active) {
                return
            }

            // Skip if project has skip-native property
            if (project.hasProperty('skip-native')) {
                return
            }

            // Check if extraction should be skipped
            if (shouldSkipExtraction(project, extension)) {
                project.logger.info("DebugSymbolsPlugin: Skipping debug symbol extraction")
                return
            }

            // Check tool availability
            def toolsAvailable = checkToolsAvailable(project)
            if (!toolsAvailable) {
                project.logger.warn("WARNING: Required tools not available - skipping debug symbol extraction")
                project.logger.warn(getMissingToolMessage())
                return
            }

            // Configure extension from link task if not already set
            if (!extension.libraryFile.isPresent()) {
                extension.libraryFile.set(linkTask.map { it.outputFile })
            }

            // Use config-specific paths if not already set
            if (!extension.debugOutputDir.isPresent()) {
                extension.debugOutputDir.set(project.layout.buildDirectory.dir(
                    "lib/main/${config.name}/${project.osIdentifier()}/${project.archIdentifier()}/debug"
                ))
            }

            if (!extension.strippedOutputDir.isPresent()) {
                extension.strippedOutputDir.set(project.layout.buildDirectory.dir(
                    "lib/main/${config.name}/${project.osIdentifier()}/${project.archIdentifier()}/stripped"
                ))
            }

            // Create extraction workflow tasks for this config
            def taskNameSuffix = config.name.capitalize()
            def extractTask = createExtractTask(project, extension, linkTask, taskNameSuffix)
            def debugLinkTask = createDebugLinkTask(project, extension, linkTask, extractTask, taskNameSuffix)
            def stripTask = createStripTask(project, extension, linkTask, debugLinkTask, taskNameSuffix)
            def copyDebugTask = createCopyDebugTask(project, extension, extractTask, taskNameSuffix)

            // Wire up to copy task if specified
            if (copyTaskName != null) {
                def copyTask = project.tasks.findByName(copyTaskName)
                if (copyTask != null) {
                    copyTask.dependsOn stripTask
                    copyTask.inputs.files stripTask.get().outputs.files
                    copyTask.dependsOn copyDebugTask
                }
            }
        }
    }

    // === Tool Availability Checks ===

    private static boolean checkToolsAvailable(Project project) {
        if (isLinux()) {
            return checkToolAvailable('objcopy') && checkToolAvailable('strip')
        } else if (isMac()) {
            return checkToolAvailable('dsymutil') && checkToolAvailable('strip')
        }
        return false
    }

    private static boolean checkToolAvailable(String toolName) {
        try {
            def process = [toolName, '--version'].execute()
            process.waitFor()
            return process.exitValue() == 0
        } catch (Exception e) {
            return false
        }
    }

    private static boolean shouldSkipExtraction(Project project, DebugSymbolsExtension extension) {
        // Skip if explicitly disabled
        if (extension.skipExtraction.get()) {
            return true
        }

        // Skip if project property is set
        if (project.hasProperty('skip-debug-extraction')) {
            return true
        }

        // Skip if skip-native is set
        if (project.hasProperty('skip-native')) {
            return true
        }

        return false
    }

    private static String getMissingToolMessage() {
        if (isLinux()) {
            return """
                |objcopy or strip not available but required for split debug information.
                |
                |To fix this issue:
                |  - On Debian/Ubuntu: sudo apt-get install binutils
                |  - On RHEL/CentOS: sudo yum install binutils
                |  - On Arch: sudo pacman -S binutils
                |
                |If you want to build without split debug info, set -Pskip-debug-extraction=true
            """.stripMargin()
        } else if (isMac()) {
            return """
                |dsymutil or strip not available but required for split debug information.
                |
                |To fix this issue:
                |  - Install Xcode Command Line Tools: xcode-select --install
                |
                |If you want to build without split debug info, set -Pskip-debug-extraction=true
            """.stripMargin()
        }
        return "Debug symbol extraction tools not available for this platform"
    }

    // === Task Creation ===

    private def createExtractTask(Project project, DebugSymbolsExtension extension, linkTask, taskNameSuffix) {
        return project.tasks.register("extractDebugLib${taskNameSuffix}", Exec) {
            onlyIf { !shouldSkipExtraction(project, extension) }
            dependsOn linkTask
            description = "Extract debug symbols from ${taskNameSuffix.toLowerCase()} library"
            group = 'build'
            workingDir project.buildDir

            def baseName = extension.libraryBaseName.get()
            def libExt = extension.libraryExtension.get()

            // Platform-specific output files
            if (isLinux()) {
                def debugFile = new File(extension.debugOutputDir.get().asFile, "${baseName}.${libExt}.debug")
                outputs.file debugFile
            } else if (isMac()) {
                def dsymBundle = new File(extension.debugOutputDir.get().asFile, "${baseName}.${libExt}.dSYM")
                outputs.dir dsymBundle
            }

            doFirst {
                def sourceFile = linkTask.get().outputFile
                def debugOutputDir = extension.debugOutputDir.get().asFile

                // Ensure output directory exists
                debugOutputDir.mkdirs()

                // Set command line based on platform
                if (isLinux()) {
                    def debugFile = new File(debugOutputDir, "${baseName}.${libExt}.debug")
                    commandLine 'objcopy', '--only-keep-debug', sourceFile.absolutePath, debugFile.absolutePath
                } else if (isMac()) {
                    def dsymBundle = new File(debugOutputDir, "${baseName}.${libExt}.dSYM")
                    commandLine 'dsymutil', sourceFile.absolutePath, '-o', dsymBundle.absolutePath
                }
            }
        }
    }

    private def createDebugLinkTask(Project project, DebugSymbolsExtension extension, linkTask, extractTask, taskNameSuffix) {
        return project.tasks.register("addDebugLinkLib${taskNameSuffix}", Exec) {
            onlyIf { isLinux() && !shouldSkipExtraction(project, extension) }
            dependsOn extractTask
            description = "Add GNU debuglink to ${taskNameSuffix.toLowerCase()} library (Linux only)"
            group = 'build'

            def baseName = extension.libraryBaseName.get()
            def libExt = extension.libraryExtension.get()

            inputs.files linkTask, extractTask
            outputs.file { linkTask.get().outputFile }

            doFirst {
                def sourceFile = linkTask.get().outputFile
                def debugFile = new File(extension.debugOutputDir.get().asFile, "${baseName}.${libExt}.debug")

                commandLine 'objcopy', '--add-gnu-debuglink=' + debugFile.absolutePath, sourceFile.absolutePath
            }
        }
    }

    private def createStripTask(Project project, DebugSymbolsExtension extension, linkTask, debugLinkTask, taskNameSuffix) {
        return project.tasks.register("stripLib${taskNameSuffix}", Exec) {
            dependsOn debugLinkTask
            onlyIf { !shouldSkipExtraction(project, extension) }
            description = "Strip debug symbols from ${taskNameSuffix.toLowerCase()} library"
            group = 'build'

            def baseName = extension.libraryBaseName.get()
            def libExt = extension.libraryExtension.get()
            def strippedFile = new File(extension.strippedOutputDir.get().asFile, "${baseName}.${libExt}")

            outputs.file strippedFile

            doFirst {
                // Ensure output directory exists
                strippedFile.parentFile.mkdirs()

                def sourceFile = linkTask.get().outputFile

                // Copy original to stripped location
                if (isLinux()) {
                    commandLine 'cp', sourceFile.absolutePath, strippedFile.absolutePath
                } else {
                    commandLine 'cp', sourceFile.absolutePath, strippedFile.absolutePath
                }
            }

            doLast {
                def strippedFilePath = strippedFile.absolutePath
                // Strip the copied file
                if (isLinux()) {
                    project.exec { commandLine 'strip', '--strip-debug', strippedFilePath }
                } else if (isMac()) {
                    project.exec { commandLine 'strip', '-S', strippedFilePath }
                }
            }
        }
    }

    private def createCopyDebugTask(Project project, DebugSymbolsExtension extension, extractTask, taskNameSuffix) {
        return project.tasks.register("copy${taskNameSuffix}DebugFiles", Copy) {
            onlyIf { !shouldSkipExtraction(project, extension) }
            dependsOn extractTask
            description = "Copy ${taskNameSuffix.toLowerCase()} debug symbol files"
            group = 'build'

            from project.file("${project.buildDir}/lib/main/${taskNameSuffix.toLowerCase()}/${project.osIdentifier()}/${project.archIdentifier()}/debug")
            into { project.ext.libraryTargetPath(taskNameSuffix.toLowerCase()) }
            include '**/*.debug'
            include '**/*.dSYM/**'
        }
    }

    // === Platform Detection Utilities ===

    private static boolean isMac() {
        return System.getProperty('os.name').toLowerCase().contains('mac')
    }

    private static boolean isLinux() {
        return System.getProperty('os.name').toLowerCase().contains('linux')
    }
}
