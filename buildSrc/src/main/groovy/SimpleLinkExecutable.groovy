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
import org.gradle.api.file.FileCollection
import org.gradle.api.tasks.*
import org.gradle.process.ExecOperations

import javax.inject.Inject

/**
 * A simple task for linking object files into an executable binary.
 * Used for Google Test binaries, fuzzer targets, and benchmark executables.
 *
 * <p>Usage example:</p>
 * <pre>
 * tasks.register("linkGtestCallTrace", SimpleLinkExecutable) {
 *     linker = 'g++'
 *     linkerArgs = ['-lgtest', '-lgtest_main', '-lpthread']
 *     objectFiles = fileTree("build/obj/gtest/callTrace") { include '*.o' }
 *     outputFile = file("build/bin/gtest/callTrace_test")
 * }
 * </pre>
 */
class SimpleLinkExecutable extends DefaultTask {

    /**
     * The linker executable (usually same as compiler: 'g++', 'clang++').
     */
    @Input
    String linker = 'g++'

    /**
     * Linker arguments (flags and libraries).
     * Example: ['-lgtest', '-lgtest_main', '-lpthread']
     */
    @Input
    List<String> linkerArgs = []

    /**
     * The object files to link.
     */
    @InputFiles
    @SkipWhenEmpty
    FileCollection objectFiles

    /**
     * Additional library files to link against (optional).
     */
    @InputFiles
    @Optional
    FileCollection libs

    /**
     * The output executable file.
     */
    @OutputFile
    File outputFile

    @Inject
    protected ExecOperations getExecOperations() {
        throw new UnsupportedOperationException()
    }

    @TaskAction
    void link() {
        outputFile.parentFile.mkdirs()

        def objectPaths = objectFiles.files.collect { it.absolutePath }

        def cmdLine = [linker] + objectPaths + linkerArgs + ['-o', outputFile.absolutePath]

        // Add library paths if provided
        if (libs != null) {
            libs.files.each { lib ->
                cmdLine.add(lib.absolutePath)
            }
        }

        logger.lifecycle("Linking executable: ${outputFile.name}")
        logger.info("Command: ${cmdLine.join(' ')}")

        def stdout = new ByteArrayOutputStream()
        def stderr = new ByteArrayOutputStream()

        def result = execOperations.exec { spec ->
            spec.commandLine cmdLine
            spec.standardOutput = stdout
            spec.errorOutput = stderr
            spec.ignoreExitValue = true
        }

        if (result.exitValue != 0) {
            def errorMsg = "Linking failed with exit code ${result.exitValue}"
            def errorOutput = stderr.toString().trim()
            if (errorOutput) {
                errorMsg += "\n${errorOutput}"
            }
            throw new RuntimeException(errorMsg)
        }

        // Make executable
        outputFile.setExecutable(true)

        logger.lifecycle("Successfully linked: ${outputFile.absolutePath} (${outputFile.length()} bytes)")
    }
}
