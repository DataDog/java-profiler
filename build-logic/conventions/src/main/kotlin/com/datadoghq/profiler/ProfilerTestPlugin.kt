// Copyright 2026, Datadog, Inc

package com.datadoghq.profiler

import com.datadoghq.native.NativeBuildExtension
import com.datadoghq.native.util.PlatformUtils
import org.gradle.api.DefaultTask
import org.gradle.api.GradleException
import org.gradle.api.Plugin
import org.gradle.api.Project
import org.gradle.api.artifacts.Configuration
import org.gradle.api.provider.ListProperty
import org.gradle.api.provider.Property
import org.gradle.api.tasks.JavaExec
import org.gradle.api.tasks.SourceSetContainer
import org.gradle.api.tasks.testing.Test
import org.gradle.api.tasks.testing.logging.TestLogEvent
import java.io.File
import javax.inject.Inject

/**
 * Convention plugin for profiler test configuration.
 *
 * Provides:
 * - Standard JVM arguments for profiler testing (attach self, error files, etc.)
 * - Java executable selection (JAVA_TEST_HOME or JAVA_HOME)
 * - Common environment variables (CI, rate limiting)
 * - JUnit Platform configuration
 * - Automatic multi-config test task generation from NativeBuildExtension
 *
 * Usage:
 * ```kotlin
 * plugins {
 *   id("com.datadoghq.profiler-test")
 * }
 *
 * profilerTest {
 *   // Required: the project providing the profiler library
 *   profilerLibProject.set(":ddprof-lib")
 *
 *   // Optional: override native library directory
 *   nativeLibDir.set(layout.buildDirectory.dir("libs/native"))
 *
 *   // Optional: add extra JVM args
 *   extraJvmArgs.add("-Xms256m")
 *
 *   // Optional: specify which configs get application tasks (default: release, debug)
 *   applicationConfigs.set(listOf("release", "debug"))
 *
 *   // Optional: main class for application tasks
 *   applicationMainClass.set("com.datadoghq.profiler.unwinding.UnwindingValidator")
 * }
 * ```
 */
class ProfilerTestPlugin : Plugin<Project> {
    override fun apply(project: Project) {
        val extension = project.extensions.create(
            "profilerTest",
            ProfilerTestExtension::class.java,
            project
        )

        // Configure all Test tasks with standard settings
        project.tasks.withType(Test::class.java).configureEach {
            configureTestTask(this, extension, project)
        }

        // Configure all JavaExec tasks with standard settings
        project.tasks.withType(JavaExec::class.java).configureEach {
            configureJavaExecTask(this, extension, project)
        }

        // After evaluation, generate multi-config tasks if profilerLibProject is set
        project.afterEvaluate {
            if (extension.profilerLibProject.isPresent) {
                generateMultiConfigTasks(project, extension)
            }
        }
    }

    private fun configureTestTask(task: Test, extension: ProfilerTestExtension, project: Project) {
        task.onlyIf { !project.hasProperty("skip-tests") }

        // Use JUnit Platform
        task.useJUnitPlatform()

        // Configure Java executable
        val javaHome = System.getenv("JAVA_TEST_HOME") ?: System.getenv("JAVA_HOME")
        task.setExecutable(File(javaHome, "bin/java").absolutePath)

        // Standard environment variables
        task.environment("DDPROF_TEST_DISABLE_RATE_LIMIT", "1")
        task.environment("CI", project.hasProperty("CI") || System.getenv("CI")?.toBoolean() ?: false)

        // Test logging
        task.testLogging.showStandardStreams = true
        task.testLogging.events(TestLogEvent.FAILED, TestLogEvent.SKIPPED)

        // JVM arguments - combine standard + extra
        task.doFirst {
            val allArgs = mutableListOf<String>()
            allArgs.addAll(extension.standardJvmArgs.get())

            // Add native library path if configured
            if (extension.nativeLibDir.isPresent) {
                allArgs.add("-Djava.library.path=${extension.nativeLibDir.get().asFile.absolutePath}")
            }

            allArgs.addAll(extension.extraJvmArgs.get())
            task.jvmArgs(allArgs)
        }
    }

    private fun configureJavaExecTask(task: JavaExec, extension: ProfilerTestExtension, project: Project) {
        // Configure Java executable
        val javaHome = System.getenv("JAVA_TEST_HOME") ?: System.getenv("JAVA_HOME")
        task.setExecutable(File(javaHome, "bin/java").absolutePath)

        // JVM arguments for JavaExec tasks
        task.doFirst {
            val allArgs = mutableListOf<String>()
            allArgs.addAll(extension.standardJvmArgs.get())
            allArgs.addAll(extension.extraJvmArgs.get())
            task.jvmArgs(allArgs)
        }
    }

    private fun generateMultiConfigTasks(project: Project, extension: ProfilerTestExtension) {
        val nativeBuildExt = project.rootProject.extensions.findByType(NativeBuildExtension::class.java)
            ?: return  // No native build extension, nothing to generate

        val currentPlatform = PlatformUtils.currentPlatform
        val currentArchitecture = PlatformUtils.currentArchitecture
        val activeConfigurations = nativeBuildExt.getActiveConfigurations(currentPlatform, currentArchitecture)

        if (activeConfigurations.isEmpty()) {
            return
        }

        val profilerLibProjectPath = extension.profilerLibProject.get()
        val tracerProjectPath = extension.tracerProject.getOrElse(":ddprof-test-tracer")
        val applicationConfigs = extension.applicationConfigs.get()
        val appMainClass = extension.applicationMainClass.getOrElse("")

        val sourceSets = project.extensions.getByType(SourceSetContainer::class.java)

        // Create base configurations
        val testCommon = project.configurations.maybeCreate("testCommon").apply {
            isCanBeConsumed = true
            isCanBeResolved = true
        }
        val mainCommon = project.configurations.maybeCreate("mainCommon").apply {
            isCanBeConsumed = true
            isCanBeResolved = true
        }

        // Add common dependencies to base configurations
        addCommonTestDependencies(project, testCommon, tracerProjectPath)
        addCommonMainDependencies(project, mainCommon, tracerProjectPath)

        val configNames = mutableListOf<String>()

        // Generate tasks for each active configuration
        activeConfigurations.forEach { config ->
            val configName = config.name
            val isActive = config.active.get()
            val testEnv = config.testEnvironment.get()

            configNames.add(configName)

            // Create test configuration
            val testCfg = project.configurations.maybeCreate("test${configName.capitalize()}Implementation").apply {
                isCanBeConsumed = true
                isCanBeResolved = true
                extendsFrom(testCommon)
            }
            testCfg.dependencies.add(
                project.dependencies.project(mapOf("path" to profilerLibProjectPath, "configuration" to configName))
            )

            // Create test task using configuration closure
            project.tasks.register("test$configName", Test::class.java) {
                val testTask = this
                testTask.onlyIf { isActive }
                testTask.dependsOn(project.tasks.named("compileTestJava"))
                testTask.description = "Runs unit tests with the $configName library variant"
                testTask.group = "verification"

                // Filter classpath to include only necessary dependencies
                testTask.classpath = sourceSets.getByName("test").runtimeClasspath.filter { file ->
                    !file.name.contains("ddprof-") || file.name.contains("test-tracer")
                } + testCfg

                // Apply test environment from config
                if (testEnv.isNotEmpty()) {
                    testEnv.forEach { (key, value) ->
                        testTask.environment(key, value)
                    }
                }

                // Sanitizer-specific conditions
                when (configName) {
                    "asan" -> testTask.onlyIf { PlatformUtils.locateLibasan() != null }
                    "tsan" -> testTask.onlyIf { PlatformUtils.locateLibtsan() != null }
                    else -> { /* no additional conditions */ }
                }
            }

            // Create application tasks for specified configs
            if (configName in applicationConfigs && appMainClass.isNotEmpty()) {
                // Create main configuration
                val mainCfg = project.configurations.maybeCreate("${configName}Implementation").apply {
                    isCanBeConsumed = true
                    isCanBeResolved = true
                    extendsFrom(mainCommon)
                }
                mainCfg.dependencies.add(
                    project.dependencies.project(mapOf("path" to profilerLibProjectPath, "configuration" to configName))
                )

                // Create run task
                project.tasks.register("runUnwindingValidator${configName.capitalize()}", JavaExec::class.java) {
                    val runTask = this
                    runTask.onlyIf { isActive }
                    runTask.dependsOn(project.tasks.named("compileJava"))
                    runTask.description = "Run the unwinding validator application ($configName config)"
                    runTask.group = "application"
                    runTask.mainClass.set(appMainClass)
                    runTask.classpath = sourceSets.getByName("main").runtimeClasspath + mainCfg

                    if (testEnv.isNotEmpty()) {
                        testEnv.forEach { (key, value) ->
                            runTask.environment(key, value)
                        }
                    }

                    // Handle validatorArgs property
                    if (project.hasProperty("validatorArgs")) {
                        runTask.setArgs((project.property("validatorArgs") as String).split(" "))
                    }
                }

                // Create report task
                project.tasks.register("unwindingReport${configName.capitalize()}", JavaExec::class.java) {
                    val reportTask = this
                    reportTask.onlyIf { isActive }
                    reportTask.dependsOn(project.tasks.named("compileJava"))
                    reportTask.description = "Generate unwinding report for CI ($configName config)"
                    reportTask.group = "verification"
                    reportTask.mainClass.set(appMainClass)
                    reportTask.classpath = sourceSets.getByName("main").runtimeClasspath + mainCfg
                    reportTask.args = listOf(
                        "--output-format=markdown",
                        "--output-file=build/reports/unwinding-summary.md"
                    )

                    if (testEnv.isNotEmpty()) {
                        testEnv.forEach { (key, value) ->
                            reportTask.environment(key, value)
                        }
                    }
                    reportTask.environment("CI", project.hasProperty("CI") || System.getenv("CI")?.toBoolean() ?: false)

                    reportTask.doFirst {
                        project.file("${project.layout.buildDirectory.get()}/reports").mkdirs()
                    }
                }
            }
        }

        // Create convenience delegate tasks
        if (applicationConfigs.isNotEmpty()) {
            project.tasks.register("runUnwindingValidator", DefaultTask::class.java) {
                val delegateTask = this
                delegateTask.description = "Run unwinding validator (delegates to release if available, otherwise debug)"
                delegateTask.group = "application"
                delegateTask.dependsOn(
                    project.provider {
                        when {
                            project.tasks.findByName("runUnwindingValidatorRelease") != null -> listOf("runUnwindingValidatorRelease")
                            project.tasks.findByName("runUnwindingValidatorDebug") != null -> listOf("runUnwindingValidatorDebug")
                            else -> throw GradleException("No suitable build configuration available for unwinding validator")
                        }
                    }
                )
            }

            project.tasks.register("unwindingReport", DefaultTask::class.java) {
                val delegateTask = this
                delegateTask.description = "Generate unwinding report (delegates to release if available, otherwise debug)"
                delegateTask.group = "verification"
                delegateTask.dependsOn(
                    project.provider {
                        when {
                            project.tasks.findByName("unwindingReportRelease") != null -> listOf("unwindingReportRelease")
                            project.tasks.findByName("unwindingReportDebug") != null -> listOf("unwindingReportDebug")
                            else -> throw GradleException("No suitable build configuration available for unwinding report")
                        }
                    }
                )
            }
        }

        // Wire up assemble/gtest dependencies
        project.gradle.projectsEvaluated {
            configNames.forEach { cfgName ->
                val testTask = project.tasks.findByName("test$cfgName")
                val profilerLibProject = project.rootProject.findProject(profilerLibProjectPath)

                if (profilerLibProject != null) {
                    val assembleTask = profilerLibProject.tasks.findByName("assemble${cfgName.capitalize()}")
                    if (testTask != null && assembleTask != null) {
                        assembleTask.dependsOn(testTask)
                    }

                    val gtestTask = profilerLibProject.tasks.findByName("gtest${cfgName.capitalize()}")
                    if (testTask != null && gtestTask != null) {
                        testTask.dependsOn(gtestTask)
                    }
                }
            }
        }
    }

    private fun addCommonTestDependencies(project: Project, configuration: Configuration, tracerProjectPath: String) {
        // Add tracer project dependency - other deps added via version catalog in build file
        configuration.dependencies.add(
            project.dependencies.project(mapOf("path" to tracerProjectPath))
        )
    }

    private fun addCommonMainDependencies(project: Project, configuration: Configuration, tracerProjectPath: String) {
        // Add tracer project dependency - other deps added via version catalog in build file
        configuration.dependencies.add(
            project.dependencies.project(mapOf("path" to tracerProjectPath))
        )
    }
}

/**
 * Extension for profiler test configuration.
 */
abstract class ProfilerTestExtension @Inject constructor(
    project: Project,
    objects: org.gradle.api.model.ObjectFactory
) {

    /**
     * Standard JVM arguments applied to all Test and JavaExec tasks.
     * These are the common profiler testing requirements.
     */
    abstract val standardJvmArgs: ListProperty<String>

    /**
     * Additional JVM arguments to add beyond the standard set.
     */
    abstract val extraJvmArgs: ListProperty<String>

    /**
     * Directory containing native test libraries.
     * When set, adds -Djava.library.path to Test tasks.
     */
    val nativeLibDir: org.gradle.api.file.DirectoryProperty = objects.directoryProperty()

    /**
     * Whether to skip tests when -Pskip-tests is set.
     * Default: true
     */
    abstract val respectSkipTests: Property<Boolean>

    /**
     * The project path providing the profiler library (e.g., ":ddprof-lib").
     * When set, enables automatic multi-config task generation.
     */
    abstract val profilerLibProject: Property<String>

    /**
     * The project path providing the test tracer (default: ":ddprof-test-tracer").
     */
    abstract val tracerProject: Property<String>

    /**
     * Configurations that should have application tasks (runUnwindingValidator*, unwindingReport*).
     * Default: ["release", "debug"]
     */
    abstract val applicationConfigs: ListProperty<String>

    /**
     * Main class for application tasks.
     * Default: "com.datadoghq.profiler.unwinding.UnwindingValidator"
     */
    abstract val applicationMainClass: Property<String>

    init {
        // Standard JVM arguments for profiler testing
        standardJvmArgs.convention(listOf(
            "-Djdk.attach.allowAttachSelf",      // Allow profiler to attach to self
            "-Djol.tryWithSudo=true",            // JOL memory layout analysis
            "-XX:ErrorFile=build/hs_err_pid%p.log", // HotSpot error file location
            "-XX:+ResizeTLAB",                   // Allow TLAB resizing for allocation profiling
            "-Xmx512m"                           // Default heap size for tests
        ))

        extraJvmArgs.convention(emptyList())
        respectSkipTests.convention(true)
        tracerProject.convention(":ddprof-test-tracer")
        applicationConfigs.convention(listOf("release", "debug"))
        applicationMainClass.convention("com.datadoghq.profiler.unwinding.UnwindingValidator")
    }
}
