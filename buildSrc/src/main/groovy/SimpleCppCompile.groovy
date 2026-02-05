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
import java.util.concurrent.ConcurrentLinkedQueue
import java.util.concurrent.atomic.AtomicInteger

/**
 * A simple C++ compilation task that directly invokes gcc/clang without relying on
 * Gradle's cpp-library plugin. This avoids issues with compiler version detection
 * that plague the official plugin.
 *
 * <p>Usage example:</p>
 * <pre>
 * tasks.register("compileLibRelease", SimpleCppCompile) {
 *     compiler = 'g++'
 *     compilerArgs = ['-O3', '-fPIC', '-std=c++17']
 *     sources = fileTree('src/main/cpp') { include '**&#47;*.cpp' }
 *     includes = files('src/main/cpp', "${System.env.JAVA_HOME}/include")
 *     objectFileDir = file("build/obj/release")
 * }
 * </pre>
 */
class SimpleCppCompile extends DefaultTask {

    /**
     * The C++ compiler executable (e.g., 'g++', 'clang++', or full path).
     */
    @Input
    String compiler = 'g++'

    /**
     * Compiler arguments (flags) to pass to the compiler.
     * Example: ['-O3', '-fPIC', '-std=c++17', '-DNDEBUG']
     */
    @Input
    List<String> compilerArgs = []

    /**
     * The C++ source files to compile.
     */
    @InputFiles
    @SkipWhenEmpty
    FileCollection sources

    /**
     * Include directories for header file lookup.
     */
    @InputFiles
    @Optional
    FileCollection includes

    /**
     * Output directory for object files.
     */
    @OutputDirectory
    File objectFileDir

    /**
     * Number of parallel compilation jobs. Defaults to available processors.
     * Note: Currently uses default ForkJoinPool parallelism.
     */
    @Input
    @Optional
    Integer parallelJobs = Runtime.runtime.availableProcessors()

    @Inject
    protected ExecOperations getExecOperations() {
        throw new UnsupportedOperationException()
    }

    @TaskAction
    void compile() {
        objectFileDir.mkdirs()

        def includeArgs = []
        if (includes != null) {
            includes.files.each { dir ->
                if (dir.exists()) {
                    includeArgs.addAll(['-I', dir.absolutePath])
                }
            }
        }

        def sourceFiles = sources.files.toList()
        def errors = new ConcurrentLinkedQueue<String>()
        def compiled = new AtomicInteger(0)
        def total = sourceFiles.size()

        logger.lifecycle("Compiling ${total} C++ source files with ${compiler}...")

        // Use parallel streams for compilation
        sourceFiles.parallelStream().forEach { sourceFile ->
            // Replace any source extension (.cpp, .c, .cc) with .o
            def baseName = sourceFile.name.substring(0, sourceFile.name.lastIndexOf('.'))
            def objectFile = new File(objectFileDir, baseName + '.o')

            def cmdLine = [compiler] + compilerArgs + includeArgs + ['-c', sourceFile.absolutePath, '-o', objectFile.absolutePath]

            try {
                def stdout = new ByteArrayOutputStream()
                def stderr = new ByteArrayOutputStream()

                def result = execOperations.exec { spec ->
                    spec.commandLine cmdLine
                    spec.standardOutput = stdout
                    spec.errorOutput = stderr
                    spec.ignoreExitValue = true
                }

                if (result.exitValue != 0) {
                    def errorMsg = "Failed to compile ${sourceFile.name}: exit code ${result.exitValue}"
                    def errorOutput = stderr.toString().trim()
                    if (errorOutput) {
                        errorMsg += "\n${errorOutput}"
                    }
                    errors.add(errorMsg)
                } else {
                    def count = compiled.incrementAndGet()
                    if (count % 10 == 0 || count == total) {
                        logger.lifecycle("  Compiled ${count}/${total} files...")
                    }
                }
            } catch (Exception e) {
                errors.add("Exception compiling ${sourceFile.name}: ${e.message}")
            }
        }

        if (!errors.isEmpty()) {
            errors.each { logger.error(it) }
            throw new RuntimeException("Compilation failed with ${errors.size()} error(s)")
        }

        logger.lifecycle("Successfully compiled ${total} files to ${objectFileDir}")
    }
}
