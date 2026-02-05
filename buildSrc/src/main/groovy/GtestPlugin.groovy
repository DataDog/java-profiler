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

/**
 * Gradle plugin for Google Test integration in C++ projects.
 *
 * <p>This plugin automatically creates compilation, linking, and execution tasks for Google Test
 * tests across multiple build configurations. It handles platform-specific differences (macOS, Linux)
 * and integrates with the custom SimpleCppCompile and SimpleLinkExecutable tasks.
 *
 * <p>For each test file in the test source directory, the plugin creates:
 * <ul>
 *   <li>compileGtest{Config}_{TestName} - Compile all main sources + test file</li>
 *   <li>linkGtest{Config}_{TestName} - Link test executable with gtest libraries</li>
 *   <li>gtest{Config}_{TestName} - Execute the test</li>
 * </ul>
 *
 * <p>Aggregation tasks:</p>
 * <ul>
 *   <li>gtest{Config} - Run all tests for a specific configuration (e.g., gtestDebug)</li>
 *   <li>gtest - Run all tests across all configurations</li>
 * </ul>
 *
 * <p>Usage:</p>
 * <pre>
 * plugins {
 *     id 'gtest'
 * }
 *
 * gtest {
 *     testSourceDir = file('src/test/cpp')
 *     mainSourceDir = file('src/main/cpp')
 *     includes = files('src/main/cpp', "${System.env.JAVA_HOME}/include")
 *     configurations = [debug, release, asan, tsan]
 * }
 * </pre>
 */
class GtestPlugin implements Plugin<Project> {

    @Override
    void apply(Project project) {
        // Create extension
        def extension = project.extensions.create('gtest', GtestExtension, project.objects)

        // Set default conventions - note: these use convention() which means they can be overridden
        // We don't set defaults here, let the build.gradle set them explicitly
        // extension.testSourceDir.convention(project.layout.projectDirectory.dir('src/test/cpp'))
        // extension.mainSourceDir.convention(project.layout.projectDirectory.dir('src/main/cpp'))
        // extension.nativeLibsSourceDir.convention(project.layout.projectDirectory.dir('src/test/resources/native-libs'))
        // extension.nativeLibsOutputDir.convention(project.layout.buildDirectory.dir('test/resources/native-libs'))

        // Register tasks after project evaluation
        project.afterEvaluate {
            // Check if testSourceDir is set
            if (!extension.testSourceDir.isPresent()) {
                project.logger.warn("WARNING: gtest.testSourceDir not configured - skipping Google Test tasks")
                return
            }

            // Check if configurations are set
            def configs = extension.configurations.get()
            if (configs.isEmpty()) {
                project.logger.warn("WARNING: gtest.configurations not configured - skipping Google Test tasks")
                return
            }

            // Check if gtest is available
            def hasGtest = checkGtestAvailable(project)
            if (!hasGtest) {
                project.logger.warn("WARNING: Google Test not found - skipping native tests")
            }

            // Create buildNativeLibs task (Linux only)
            if (extension.buildNativeLibs.get()) {
                createBuildNativeLibsTask(project, extension, hasGtest)
            }

            // Create master aggregation task
            def gtestAll = createMasterAggregationTask(project, hasGtest)

            // Create tasks for each configuration
            configs.each { config ->
                // Only create tasks for matching platform/arch and active configs
                if (configMatches(project, config) && config.active) {
                    createConfigTasks(project, extension, config, hasGtest, gtestAll)
                }
            }
        }
    }

    private static boolean checkGtestAvailable(Project project) {
        // Check if hasGtest property exists (set in common.gradle or similar)
        return project.hasProperty('hasGtest') ? project.property('hasGtest') : true
    }

    private static boolean configMatches(Project project, config) {
        // Use the osIdentifier() and archIdentifier() functions from common.gradle
        // These are available as extension properties on the project
        def currentOs = project.osIdentifier()
        def currentArch = project.archIdentifier()

        return (config.os == currentOs && config.arch == currentArch)
    }

    private void createBuildNativeLibsTask(Project project, GtestExtension extension, boolean hasGtest) {
        project.tasks.register("buildNativeLibs") {
            group = 'build'
            description = "Build the native libs for the Google Tests"

            onlyIf {
                hasGtest &&
                !project.hasProperty('skip-native') &&
                !project.hasProperty('skip-gtest') &&
                isLinux() &&
                extension.nativeLibsSourceDir.isPresent() &&
                extension.nativeLibsOutputDir.isPresent()
            }

            def srcDir = extension.nativeLibsSourceDir.isPresent() ?
                extension.nativeLibsSourceDir.get().asFile :
                project.file('src/test/resources/native-libs')
            def targetDir = extension.nativeLibsOutputDir.isPresent() ?
                extension.nativeLibsOutputDir.get().asFile :
                project.file('build/test/resources/native-libs')

            doLast {
                if (!srcDir.exists()) {
                    project.logger.info("Native libs source directory does not exist: ${srcDir}")
                    return
                }

                srcDir.eachDir { dir ->
                    def libName = dir.name
                    def libDir = new File("${targetDir}/${libName}")
                    def libSrcDir = new File("${srcDir}/${libName}")

                    project.exec {
                        commandLine "sh", "-c", """
                            echo "Processing library: ${libName} @ ${libSrcDir}"
                            mkdir -p ${libDir}
                            cd ${libSrcDir}
                            make TARGET_DIR=${libDir}
                        """
                    }
                }
            }

            inputs.files project.fileTree(srcDir) { include '**/*' }
            outputs.dir targetDir
        }
    }

    private createMasterAggregationTask(Project project, boolean hasGtest) {
        return project.tasks.register("gtest") {
            group = 'verification'
            description = "Run all Google Tests for all build configurations of the library"

            onlyIf {
                hasGtest &&
                !project.hasProperty('skip-tests') &&
                !project.hasProperty('skip-native') &&
                !project.hasProperty('skip-gtest')
            }
        }
    }

    private void createConfigTasks(Project project, GtestExtension extension, config, boolean hasGtest, gtestAll) {
        // Determine compiler - use CompilerUtils instead of config.compiler
        def compiler = CompilerUtils.findCxxCompiler()

        // Build include paths
        def includeFiles = extension.includes
        if (isMac() && extension.googleTestHome.isPresent()) {
            includeFiles = includeFiles + project.files("${extension.googleTestHome.get().asFile}/include")
        } else if (isMac() && extension.gtestIncludePaths.get().containsKey('macos')) {
            includeFiles = includeFiles + project.files(extension.gtestIncludePaths.get().get('macos'))
        } else if (isMac()) {
            includeFiles = includeFiles + project.files('/opt/homebrew/opt/googletest/include/')
        }

        // Adjust compiler args
        def gtestCompilerArgs = adjustCompilerArgs(config.compilerArgs, extension)

        // Adjust linker args
        def gtestLinkerArgs = adjustLinkerArgs(config, extension)

        // Create per-config aggregation task
        def gtestConfigTask = project.tasks.register("gtest${config.name.capitalize()}") {
            group = 'verification'
            description = "Run all Google Tests for the ${config.name} build of the library"
        }

        // Discover and create tasks for each test file
        def testDir = extension.testSourceDir.get().asFile
        if (!testDir.exists()) {
            project.logger.info("Test source directory does not exist: ${testDir}")
            return
        }

        testDir.eachFile { testFile ->
            if (!testFile.name.endsWith('.cpp')) {
                return
            }

            def testName = testFile.name.substring(0, testFile.name.lastIndexOf('.'))

            // Create compile task
            def compileTask = createCompileTask(project, extension, config, testFile, testName,
                compiler, gtestCompilerArgs, includeFiles, hasGtest)

            // Create link task
            def linkTask = createLinkTask(project, config, testName, compiler, gtestLinkerArgs,
                compileTask, hasGtest)

            // Create execute task
            def executeTask = createExecuteTask(project, extension, config, testName, linkTask, hasGtest)

            // Wire up dependencies
            gtestConfigTask.configure { dependsOn executeTask }
            gtestAll.configure { dependsOn executeTask }
        }
    }

    private createCompileTask(Project project, GtestExtension extension, config, testFile, testName,
                               compiler, compilerArgs, includeFiles, hasGtest) {
        return project.tasks.register("compileGtest${config.name.capitalize()}_${testName}", SimpleCppCompile) {
            onlyIf {
                config.active &&
                hasGtest &&
                !project.hasProperty('skip-tests') &&
                !project.hasProperty('skip-native') &&
                !project.hasProperty('skip-gtest')
            }
            group = 'build'
            description = "Compile the Google Test ${testName} for the ${config.name} build of the library"

            it.compiler = compiler
            it.compilerArgs = new ArrayList(compilerArgs) // copy list

            // Combine main sources and test file (simple mode - no source sets needed)
            sources = project.fileTree(extension.mainSourceDir.get()) { include '**/*.cpp' } + project.files(testFile)

            includes = includeFiles
            objectFileDir = project.file("${project.buildDir}/obj/gtest/${config.name}/${testName}")
        }
    }

    private createLinkTask(Project project, config, testName, compiler, linkerArgs,
                            compileTask, hasGtest) {
        def binary = project.file("${project.buildDir}/bin/gtest/${config.name}_${testName}/${testName}")

        return project.tasks.register("linkGtest${config.name.capitalize()}_${testName}", SimpleLinkExecutable) {
            onlyIf {
                config.active &&
                hasGtest &&
                !project.hasProperty('skip-tests') &&
                !project.hasProperty('skip-native') &&
                !project.hasProperty('skip-gtest')
            }
            dependsOn compileTask
            group = 'build'
            description = "Link the Google Test ${testName} for the ${config.name} build of the library"

            linker = compiler
            it.linkerArgs = new ArrayList(linkerArgs) // copy list
            objectFiles = project.fileTree("${project.buildDir}/obj/gtest/${config.name}/${testName}") {
                include '*.o'
            }
            outputFile = binary
        }
    }

    private createExecuteTask(Project project, GtestExtension extension, config, testName,
                               linkTask, hasGtest) {
        def binary = project.file("${project.buildDir}/bin/gtest/${config.name}_${testName}/${testName}")

        return project.tasks.register("gtest${config.name.capitalize()}_${testName}", Exec) {
            onlyIf {
                config.active &&
                hasGtest &&
                !project.hasProperty('skip-tests') &&
                !project.hasProperty('skip-native') &&
                !project.hasProperty('skip-gtest')
            }
            dependsOn linkTask

            // Add dependency on buildNativeLibs if it exists (Linux only)
            if (isLinux() && extension.buildNativeLibs.get()) {
                def buildNativeLibsTask = project.tasks.findByName('buildNativeLibs')
                if (buildNativeLibsTask != null) {
                    dependsOn buildNativeLibsTask
                }
            }

            group = 'verification'
            description = "Run the Google Test ${testName} for the ${config.name} build of the library"

            executable binary.absolutePath

            // Set test environment variables
            if (config.testEnv) {
                config.testEnv.each { key, value ->
                    environment key, value
                }
            }

            inputs.files binary

            // Always re-run tests if configured
            if (extension.alwaysRun.get()) {
                outputs.upToDateWhen { false }
            }

            // Fail fast if configured
            ignoreExitValue = !extension.failFast.get()
        }
    }

    private List adjustCompilerArgs(List baseArgs, GtestExtension extension) {
        def args = baseArgs.findAll {
            it != '-std=c++17' && (extension.enableAssertions.get() ? it != '-DNDEBUG' : true)
        }

        // Re-add C++17 standard
        args.add('-std=c++17')

        // Add musl define if needed
        if (isLinux() && isMusl()) {
            args.add('-D__musl__')
        }

        return args
    }

    private List adjustLinkerArgs(config, GtestExtension extension) {
        def args = []

        // For release config, skip minimizing flags if keepSymbols is true
        if (config.name != 'release' || !extension.keepSymbols.get()) {
            args.addAll(config.linkerArgs)
        } else {
            // Keep symbols - filter out minimizing flags
            args.addAll(config.linkerArgs)
        }

        // Add gtest libraries
        args.addAll('-lgtest', '-lgtest_main', '-lgmock', '-lgmock_main', '-ldl', '-lpthread', '-lm')

        // Platform-specific library paths and libraries
        if (isMac()) {
            if (extension.googleTestHome.isPresent()) {
                args.add("-L${extension.googleTestHome.get().asFile}/lib")
            } else if (extension.gtestLibPaths.get().containsKey('macos')) {
                args.add("-L${extension.gtestLibPaths.get().get('macos')}")
            } else {
                args.add('-L/opt/homebrew/opt/googletest/lib')
            }
        } else {
            args.add('-lrt')
        }

        return args
    }

    // === Platform Detection Utilities ===

    private static boolean isMac() {
        return System.getProperty('os.name').toLowerCase().contains('mac')
    }

    private static boolean isLinux() {
        return System.getProperty('os.name').toLowerCase().contains('linux')
    }

    private static boolean isMusl() {
        if (!isLinux()) {
            return false
        }
        try {
            def result = 'ldd --version'.execute()
            result.waitFor()
            return result.text.contains('musl')
        } catch (Exception e) {
            return false
        }
    }
}
