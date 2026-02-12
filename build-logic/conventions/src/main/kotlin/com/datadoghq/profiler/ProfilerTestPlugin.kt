
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
import org.gradle.api.tasks.Exec
import org.gradle.api.tasks.SourceSetContainer
import javax.inject.Inject

/**
 * Convention plugin for profiler test configuration.
 *
 * Provides:
 * - Standard JVM arguments for profiler testing (attach self, error files, etc.)
 * - Java executable selection (JAVA_TEST_HOME or JAVA_HOME) on ALL platforms
 * - Common environment variables (CI, rate limiting)
 * - JUnit Platform Console Launcher execution via Exec tasks
 * - Automatic multi-config test task generation from NativeBuildExtension
 *
 * Implementation:
 * - Uses Exec tasks instead of Test/JavaExec to bypass Gradle's toolchain system
 * - This provides consistent behavior across all platforms (glibc, musl, macOS)
 * - Supports multi-JDK testing via JAVA_TEST_HOME on all platforms
 * - Same task names everywhere (testdebug, testrelease, unwindingReportRelease)
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
 *   // Optional: specify which configs get application tasks (default: all active configs)
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

        // Create base configurations eagerly so they can be extended by build scripts
        // without needing afterEvaluate
        project.configurations.maybeCreate("testCommon").apply {
            isCanBeConsumed = false
            isCanBeResolved = true
        }
        project.configurations.maybeCreate("mainCommon").apply {
            isCanBeConsumed = false
            isCanBeResolved = true
        }

        // After evaluation, generate multi-config tasks if profilerLibProject is set
        project.afterEvaluate {
            if (extension.profilerLibProject.isPresent) {
                generateMultiConfigTasks(project, extension)
            }
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
        // Default to all active configs if not explicitly specified
        val explicitAppConfigs = extension.applicationConfigs.get()
        val applicationConfigs = if (explicitAppConfigs.isEmpty()) {
            activeConfigurations.map { it.name }
        } else {
            explicitAppConfigs
        }
        val appMainClass = extension.applicationMainClass.getOrElse("")

        val sourceSets = project.extensions.getByType(SourceSetContainer::class.java)

        // Get the base configurations (created eagerly in apply())
        val testCommon = project.configurations.getByName("testCommon")
        val mainCommon = project.configurations.getByName("mainCommon")

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
            val testCfg = project.configurations.maybeCreate("test${configName.replaceFirstChar { it.uppercaseChar() }}Implementation").apply {
                isCanBeConsumed = false
                isCanBeResolved = true
                extendsFrom(testCommon)
            }
            testCfg.dependencies.add(
                project.dependencies.project(mapOf("path" to profilerLibProjectPath, "configuration" to configName))
            )

            // Create test task using Exec to bypass Gradle's toolchain system
            project.tasks.register("test$configName", Exec::class.java) {
                val testTask = this
                testTask.onlyIf { isActive && !project.hasProperty("skip-tests") }
                testTask.description = "Runs unit tests with the $configName library variant"
                testTask.group = "verification"

                // Dependencies
                testTask.dependsOn(project.tasks.named("compileTestJava"))
                testTask.dependsOn(testCfg)
                testTask.dependsOn(sourceSets.getByName("test").output)

                // Build classpath
                val testClasspath = sourceSets.getByName("test").runtimeClasspath.filter { file ->
                    !file.name.contains("ddprof-") || file.name.contains("test-tracer")
                } + testCfg

                // Configure JVM arguments and test execution
                testTask.doFirst {
                    // Set executable at execution time so environment variables (JAVA_TEST_HOME) are read correctly
                    // (CI scripts export JAVA_TEST_HOME at runtime, not visible at Gradle configuration time)
                    testTask.executable = PlatformUtils.testJavaExecutable()

                    val allArgs = mutableListOf<String>()

                    // Standard JVM args
                    allArgs.addAll(extension.standardJvmArgs.get())
                    if (extension.nativeLibDir.isPresent) {
                        allArgs.add("-Djava.library.path=${extension.nativeLibDir.get().asFile.absolutePath}")
                    }
                    allArgs.addAll(extension.extraJvmArgs.get())

                    // Test-specific system properties (extracted from config name)
                    val keepRecordings = project.hasProperty("keepJFRs") || System.getenv("KEEP_JFRS")?.toBoolean() ?: false
                    allArgs.add("-Dddprof_test.keep_jfrs=$keepRecordings")
                    allArgs.add("-Dddprof_test.config=$configName")
                    allArgs.add("-Dddprof_test.ci=${project.hasProperty("CI")}")

                    // System properties
                    allArgs.add("-DDDPROF_TEST_DISABLE_RATE_LIMIT=1")
                    allArgs.add("-DCI=${project.hasProperty("CI") || System.getenv("CI")?.toBoolean() ?: false}")

                    // Test environment variables as system properties
                    testEnv.forEach { (key, value) ->
                        allArgs.add("-D$key=$value")
                    }

                    // Classpath
                    allArgs.add("-cp")
                    allArgs.add(testClasspath.asPath)

                    // JUnit Platform Console Launcher
                    allArgs.add("org.junit.platform.console.ConsoleLauncher")

                    // Support Gradle's --tests filter by mapping to JUnit's selection options
                    // Note: Cannot use --scan-classpath with explicit selectors
                    if (project.hasProperty("tests")) {
                        val testFilter = project.property("tests") as String
                        // Only use --select-method if filter contains '#' (method separator)
                        // FQCNs contain '.' but should use --select-class
                        if (testFilter.contains("#")) {
                            allArgs.add("--select-method=$testFilter")
                        } else {
                            allArgs.add("--select-class=$testFilter")
                        }
                    } else {
                        // No filter specified, scan the entire classpath
                        allArgs.add("--scan-classpath")
                    }

                    allArgs.add("--details=verbose")
                    allArgs.add("--details-theme=unicode")

                    testTask.args = allArgs
                }

                // Apply test environment
                if (testEnv.isNotEmpty()) {
                    testEnv.forEach { (key, value) ->
                        testTask.environment(key, value)
                    }
                }
                testTask.environment("DDPROF_TEST_DISABLE_RATE_LIMIT", "1")
                testTask.environment("CI", project.hasProperty("CI") || System.getenv("CI")?.toBoolean() ?: false)

                // Pass through CI environment variables that tests expect
                // (Exec tasks don't inherit environment automatically like Test tasks do)
                System.getenv("LIBC")?.let { testTask.environment("LIBC", it) }
                System.getenv("KEEP_JFRS")?.let { testTask.environment("KEEP_JFRS", it) }
                System.getenv("TEST_COMMIT")?.let { testTask.environment("TEST_COMMIT", it) }
                System.getenv("TEST_CONFIGURATION")?.let { testTask.environment("TEST_CONFIGURATION", it) }
                System.getenv("SANITIZER")?.let { testTask.environment("SANITIZER", it) }

                // Sanitizer-specific conditions
                when (configName) {
                    "asan" -> testTask.onlyIf { PlatformUtils.locateLibasan() != null }
                    "tsan" -> testTask.onlyIf { PlatformUtils.locateLibtsan() != null }
                }
            }

            // Create application tasks for specified configs
            if (configName in applicationConfigs && appMainClass.isNotEmpty()) {
                // Create main configuration
                val mainCfg = project.configurations.maybeCreate("${configName}Implementation").apply {
                    isCanBeConsumed = false
                    isCanBeResolved = true
                    extendsFrom(mainCommon)
                }
                mainCfg.dependencies.add(
                    project.dependencies.project(mapOf("path" to profilerLibProjectPath, "configuration" to configName))
                )

                // Create run task using Exec to bypass Gradle's toolchain system
                project.tasks.register("runUnwindingValidator${configName.replaceFirstChar { it.uppercaseChar() }}", Exec::class.java) {
                    val runTask = this
                    runTask.onlyIf { isActive }
                    runTask.description = "Run the unwinding validator application ($configName config)"
                    runTask.group = "application"

                    runTask.dependsOn(project.tasks.named("compileJava"))
                    runTask.dependsOn(mainCfg)

                    val mainClasspath = sourceSets.getByName("main").runtimeClasspath + mainCfg

                    runTask.doFirst {
                        // Set executable at execution time so environment variables are read correctly
                        runTask.executable = PlatformUtils.testJavaExecutable()

                        val allArgs = mutableListOf<String>()
                        allArgs.addAll(extension.standardJvmArgs.get())
                        allArgs.addAll(extension.extraJvmArgs.get())
                        allArgs.add("-cp")
                        allArgs.add(mainClasspath.asPath)
                        allArgs.add(appMainClass)

                        // Handle validatorArgs property
                        if (project.hasProperty("validatorArgs")) {
                            allArgs.addAll((project.property("validatorArgs") as String).split(" "))
                        }

                        runTask.args = allArgs
                    }

                    if (testEnv.isNotEmpty()) {
                        testEnv.forEach { (key, value) ->
                            runTask.environment(key, value)
                        }
                    }
                }

                // Create report task using Exec to bypass Gradle's toolchain system
                project.tasks.register("unwindingReport${configName.replaceFirstChar { it.uppercaseChar() }}", Exec::class.java) {
                    val reportTask = this
                    reportTask.onlyIf { isActive }
                    reportTask.description = "Generate unwinding report for CI ($configName config)"
                    reportTask.group = "verification"

                    reportTask.dependsOn(project.tasks.named("compileJava"))
                    reportTask.dependsOn(mainCfg)

                    val mainClasspath = sourceSets.getByName("main").runtimeClasspath + mainCfg

                    reportTask.doFirst {
                        // Set executable at execution time so environment variables are read correctly
                        reportTask.executable = PlatformUtils.testJavaExecutable()

                        project.file("${project.layout.buildDirectory.get()}/reports").mkdirs()

                        val allArgs = mutableListOf<String>()
                        allArgs.addAll(extension.standardJvmArgs.get())
                        allArgs.addAll(extension.extraJvmArgs.get())
                        allArgs.add("-cp")
                        allArgs.add(mainClasspath.asPath)
                        allArgs.add(appMainClass)
                        allArgs.add("--output-format=markdown")
                        allArgs.add("--output-file=build/reports/unwinding-summary.md")

                        reportTask.args = allArgs
                    }

                    if (testEnv.isNotEmpty()) {
                        testEnv.forEach { (key, value) ->
                            reportTask.environment(key, value)
                        }
                    }
                    reportTask.environment("CI", project.hasProperty("CI") || System.getenv("CI")?.toBoolean() ?: false)
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
                    val assembleTask = profilerLibProject.tasks.findByName("assemble${cfgName.replaceFirstChar { it.uppercaseChar() }}")
                    if (testTask != null && assembleTask != null) {
                        assembleTask.dependsOn(testTask)
                    }

                    val gtestTask = profilerLibProject.tasks.findByName("gtest${cfgName.replaceFirstChar { it.uppercaseChar() }}")
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
     * Standard JVM arguments applied to all Exec-based test and application tasks.
     * These are the common profiler testing requirements.
     */
    abstract val standardJvmArgs: ListProperty<String>

    /**
     * Additional JVM arguments to add beyond the standard set.
     */
    abstract val extraJvmArgs: ListProperty<String>

    /**
     * Directory containing native test libraries.
     * When set, adds -Djava.library.path to test Exec tasks.
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
     * Default: empty list means all active configurations get application tasks.
     * Set explicitly to restrict which configs get app tasks.
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
        applicationConfigs.convention(emptyList()) // Empty = all active configs get app tasks
        applicationMainClass.convention("com.datadoghq.profiler.unwinding.UnwindingValidator")
    }
}
