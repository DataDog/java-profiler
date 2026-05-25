
package com.datadoghq.native.gtest

import com.datadoghq.native.NativeBuildExtension
import com.datadoghq.native.model.BuildConfiguration
import com.datadoghq.native.model.Platform
import com.datadoghq.native.util.PlatformUtils
import org.gradle.api.Plugin
import org.gradle.api.Project
import java.io.File

/**
 * Gradle plugin for Google Test integration in C++ projects.
 *
 * This plugin automatically creates compilation, linking, and execution tasks for Google Test
 * tests across multiple build configurations. It handles platform-specific differences (macOS, Linux)
 * and integrates with the NativeBuildPlugin's BuildConfiguration model.
 *
 * For each test file in the test source directory, the plugin creates:
 * - compileGtest{Config}_{TestName} - Compile all main sources + test file
 * - linkGtest{Config}_{TestName} - Link test executable with gtest libraries
 * - gtest{Config}_{TestName} - Execute the test
 *
 * Aggregation tasks:
 * - gtest{Config} - Run all tests for a specific configuration (e.g., gtestDebug)
 * - gtest - Run all tests across all configurations
 *
 * Usage:
 * ```kotlin
 * plugins {
 *     id("com.datadoghq.native-build")
 *     id("com.datadoghq.gtest")
 * }
 *
 * gtest {
 *     testSourceDir.set(layout.projectDirectory.dir("src/test/cpp"))
 *     mainSourceDir.set(layout.projectDirectory.dir("src/main/cpp"))
 *     includes.from("src/main/cpp", "${javaHome}/include")
 * }
 * ```
 */
class GtestPlugin : Plugin<Project> {

    override fun apply(project: Project) {
        // Create extension
        val extension = project.extensions.create("gtest", GtestExtension::class.java)

        // Register tasks after project evaluation
        project.afterEvaluate {
            // Check if testSourceDir is set
            if (!extension.testSourceDir.isPresent) {
                project.logger.warn("WARNING: gtest.testSourceDir not configured - skipping Google Test tasks")
                return@afterEvaluate
            }

            // Get configurations from NativeBuildExtension
            val nativeBuildExtension = project.extensions.findByType(NativeBuildExtension::class.java)
            if (nativeBuildExtension == null) {
                project.logger.warn("WARNING: NativeBuildExtension not found - apply com.datadoghq.native-build plugin first")
                return@afterEvaluate
            }

            val activeConfigs = nativeBuildExtension.getActiveConfigurations(
                PlatformUtils.currentPlatform,
                PlatformUtils.currentArchitecture
            )

            if (activeConfigs.isEmpty()) {
                project.logger.warn("WARNING: No active build configurations - skipping Google Test tasks")
                return@afterEvaluate
            }

            // Check if gtest is available
            val hasGtest = checkGtestAvailable()
            if (!hasGtest) {
                project.logger.warn("WARNING: Google Test not found - skipping native tests")
            }

            // Create buildNativeLibs task (Linux only)
            if (extension.buildNativeLibs.get()) {
                createBuildNativeLibsTask(project, extension, hasGtest)
            }

            // Create master aggregation task
            val gtestAll = createMasterAggregationTask(project, hasGtest)

            // Create tasks for each active configuration
            activeConfigs.forEach { config ->
                createConfigTasks(project, extension, config, hasGtest, gtestAll)
            }
        }
    }

    private fun checkGtestAvailable(): Boolean {
        // Check common gtest locations
        val locations = when (PlatformUtils.currentPlatform) {
            Platform.MACOS -> listOf(
                "/opt/homebrew/opt/googletest",
                "/usr/local/opt/googletest"
            )
            Platform.LINUX -> listOf(
                "/usr/include/gtest",
                "/usr/local/include/gtest"
            )
        }
        return locations.any { File(it).exists() }
    }

    private fun createBuildNativeLibsTask(project: Project, extension: GtestExtension, hasGtest: Boolean) {
        project.tasks.register("buildNativeLibs") {
            group = "build"
            description = "Build the native libs for the Google Tests"

            onlyIf {
                hasGtest &&
                !project.hasProperty("skip-native") &&
                !project.hasProperty("skip-gtest") &&
                PlatformUtils.currentPlatform == Platform.LINUX &&
                extension.nativeLibsSourceDir.isPresent &&
                extension.nativeLibsOutputDir.isPresent
            }

            val srcDir = if (extension.nativeLibsSourceDir.isPresent) {
                extension.nativeLibsSourceDir.get().asFile
            } else {
                project.file("src/test/resources/native-libs")
            }
            val targetDir = if (extension.nativeLibsOutputDir.isPresent) {
                extension.nativeLibsOutputDir.get().asFile
            } else {
                project.file("build/test/resources/native-libs")
            }

            doLast {
                if (!srcDir.exists()) {
                    project.logger.info("Native libs source directory does not exist: $srcDir")
                    return@doLast
                }

                srcDir.listFiles()?.filter { it.isDirectory }?.forEach { dir ->
                    val libName = dir.name
                    val libDir = File("$targetDir/$libName")
                    val libSrcDir = File("$srcDir/$libName")

                    // Use ProcessBuilder directly (Gradle 9 removed project.exec in task actions)
                    val process = ProcessBuilder("sh", "-c", """
                        echo "Processing library: $libName @ $libSrcDir"
                        mkdir -p $libDir
                        cd $libSrcDir
                        make TARGET_DIR=$libDir
                    """.trimIndent())
                        .inheritIO()
                        .start()
                    val exitCode = process.waitFor()
                    if (exitCode != 0) {
                        throw org.gradle.api.GradleException("Failed to build native lib: $libName (exit code: $exitCode)")
                    }
                }
            }

            inputs.files(project.fileTree(srcDir))
            outputs.dir(targetDir)
        }
    }

    private fun createMasterAggregationTask(project: Project, hasGtest: Boolean): org.gradle.api.tasks.TaskProvider<*> {
        return project.tasks.register("gtest") {
            group = "verification"
            description = "Run all Google Tests for all build configurations of the library"

            onlyIf {
                hasGtest &&
                !project.hasProperty("skip-tests") &&
                !project.hasProperty("skip-native") &&
                !project.hasProperty("skip-gtest")
            }
        }
    }

    private fun createConfigTasks(
        project: Project,
        extension: GtestExtension,
        config: BuildConfiguration,
        hasGtest: Boolean,
        gtestAll: org.gradle.api.tasks.TaskProvider<*>
    ) {
        // Find compiler and build include paths
        val compiler = findCompiler(project)
        val includeFiles = extension.includes.plus(project.files(getGtestIncludes(extension)))

        // Create per-config aggregation task (compile + link + run)
        val gtestConfigTask = project.tasks.register("gtest${config.capitalizedName()}") {
            group = "verification"
            description = "Run all Google Tests for the ${config.name} build of the library"
        }

        // Per-config build-only aggregation task (compile + link, no run).
        // Useful in CI where binaries are executed directly without going
        // through Gradle's logging infrastructure.
        val buildGtestConfigTask = project.tasks.register("buildGtest${config.capitalizedName()}") {
            group = "build"
            description = "Compile and link all Google Tests for the ${config.name} build (no run)"
        }

        // Compile all library sources ONCE for this config.  Each test
        // binary only compiles its own test file and links against these
        // shared objects, reducing compilations from O(n_tests × n_sources)
        // to O(n_sources + n_tests).
        val sharedBuilder = GtestTaskBuilder(project, extension, config)
            .withCompiler(compiler)
            .withIncludes(includeFiles)
            .onlyIfGtest(hasGtest)
        val sharedCompilerArgs = sharedBuilder.sharedCompilerArgs()
        val sharedLibCompileTask = project.tasks.register(
            "compileGtestLibrary${config.capitalizedName()}",
            com.datadoghq.native.tasks.NativeCompileTask::class.java
        ) {
            onlyIf { hasGtest && !sharedBuilder.skipConditions() }
            group = "build"
            description = "Compile shared library sources for ${config.name} gtest binaries"

            this.compiler.set(compiler)
            this.compilerArgs.set(sharedCompilerArgs)
            sources.from(project.fileTree(extension.mainSourceDir.get()) { include("**/*.cpp") })
            includes.from(includeFiles)
            objectFileDir.set(project.file(
                "${project.layout.buildDirectory.get()}/obj/gtest/${config.name}/lib"
            ))
        }

        // Discover and create tasks for each test file using builder
        val testDir = extension.testSourceDir.get().asFile
        if (!testDir.exists()) {
            project.logger.info("Test source directory does not exist: $testDir")
            return
        }

        testDir.listFiles()?.filter { it.name.endsWith(".cpp") }?.forEach { testFile ->
            val executeTask = GtestTaskBuilder(project, extension, config)
                .forTest(testFile)
                .withCompiler(compiler)
                .withIncludes(includeFiles)
                .withSharedLibObjects(sharedLibCompileTask)
                .onlyIfGtest(hasGtest)
                .build()

            gtestConfigTask.configure { dependsOn(executeTask) }
            gtestAll.configure { dependsOn(executeTask) }
            // buildGtest depends on the link task, not the run task
            buildGtestConfigTask.configure {
                dependsOn("linkGtest${config.capitalizedName()}_${testFile.nameWithoutExtension}")
            }
        }
    }

    private fun findCompiler(project: Project): String = PlatformUtils.findCompiler(project)

    private fun getGtestIncludes(extension: GtestExtension): List<File> {
        return when (PlatformUtils.currentPlatform) {
            Platform.MACOS -> {
                val gtestPath = if (extension.googleTestHome.isPresent) {
                    extension.googleTestHome.get().asFile.absolutePath
                } else {
                    "/opt/homebrew/opt/googletest"
                }
                listOf(File("$gtestPath/include"))
            }
            Platform.LINUX -> emptyList() // System includes
        }
    }
}
