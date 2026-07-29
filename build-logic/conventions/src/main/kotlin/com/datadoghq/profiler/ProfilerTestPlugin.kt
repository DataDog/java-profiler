
package com.datadoghq.profiler

import com.datadoghq.native.NativeBuildExtension
import com.datadoghq.native.model.BuildConfiguration
import com.datadoghq.native.model.Platform
import com.datadoghq.native.util.PlatformUtils
import org.gradle.api.DefaultTask
import org.gradle.api.GradleException
import org.gradle.api.Plugin
import org.gradle.api.Project
import org.gradle.api.artifacts.Configuration
import org.gradle.api.file.FileCollection
import org.gradle.api.provider.ListProperty
import org.gradle.api.provider.Property
import org.gradle.api.tasks.Exec
import org.gradle.api.tasks.SourceSetContainer
import org.gradle.api.tasks.testing.Test
import java.io.File
import java.time.Duration
import javax.inject.Inject

/**
 * Convention plugin for profiler test configuration.
 *
 * Provides:
 * - Standard JVM arguments for profiler testing (attach self, error files, etc.)
 * - Java executable selection (JAVA_TEST_HOME or JAVA_HOME) on ALL platforms
 * - Common environment variables (CI, rate limiting)
 * - Unified -Ptests flag support across all platforms
 * - Automatic multi-config test task generation from NativeBuildExtension
 *
 * Implementation:
 * - glibc/macOS: Uses native Test tasks with Gradle's JUnit Platform integration
 * - musl (Alpine): Uses Exec tasks with custom ProfilerTestRunner (bypasses toolchain probe)
 * - Unified interface: -Ptests property works identically on all platforms
 * - Supports multi-JDK testing via JAVA_TEST_HOME on all platforms
 * - Same task names everywhere (testdebug, testrelease, unwindingReportRelease)
 *
 * Platform Detection:
 * - Uses PlatformUtils.isMusl() at configuration time to select task implementation
 * - musl systems: Exec task with ProfilerTestRunner (uses JUnit Platform Launcher API directly)
 * - glibc/macOS: Normal Test task with native JUnit integration
 *
 * Custom Test Runner:
 * - ProfilerTestRunner uses JUnit Platform Launcher API directly
 * - Avoids Console Launcher issues (assertions, JVM args, NoSuchMethodError on musl + JDK 11)
 * - Same API used by IDEs and Gradle's Test task internally
 * - Supports test filtering via -Dtest.filter system property
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
 *
 * // Run tests (all platforms use same syntax):
 * ./gradlew :ddprof-test:testdebug -Ptests=ClassName.methodName
 * ./gradlew :ddprof-test:testdebug -Ptests=ClassName
 * ./gradlew :ddprof-test:testdebug -Ptests="*.Pattern*"
 * ```
 */
class ProfilerTestPlugin : Plugin<Project> {

    /**
     * Major version of the *test* JVM, read from its `release` file (`JAVA_VERSION="..."`) rather
     * than by executing the launcher.
     *
     * Executing `$JAVA_TEST_HOME/bin/java -version` (PlatformUtils.testJvmMajorVersion()) is
     * unreliable here: in the musl split-JDK matrix it has been observed to report the build JDK
     * (21) even when the test JVM is JDK 8, which put a JDK-21-only `--add-exports` onto a JDK-8
     * launcher and aborted it. Reading the `release` file is a pure file read of the same
     * JAVA_TEST_HOME the executable is resolved from — deterministic, no subprocess, no exec-format
     * or PATH hazards. Returns 0 when it cannot be determined (missing/old `release`), so callers
     * fail safe: they omit the flag, the profiler degrades to thread-scoped storage, and the
     * carrier-scoping tests skip — never an abort.
     */
    private fun testJvmMajorVersionFromRelease(): Int = try {
        val release = File(PlatformUtils.testJavaHome(), "release")
        val version = release.takeIf { it.isFile }
            ?.readLines()
            ?.firstOrNull { it.startsWith("JAVA_VERSION=") }
            ?.substringAfter('=')?.trim()?.trim('"')
        // "1.8.0_452" -> 8 ; "21.0.5" -> 21
        val parts = version?.split('.').orEmpty()
        val majorToken = when {
            parts.isEmpty() -> ""
            parts[0] == "1" && parts.size > 1 -> parts[1]
            else -> parts[0]
        }
        majorToken.takeWhile { it.isDigit() }.toIntOrNull() ?: 0
    } catch (e: Exception) {
        0
    }

    /**
     * JVM args required to enable carrier-scoped OTEL context storage
     * (`OtelContextStorage.Mode.CARRIER`), or an empty list when the test JVM does not support it.
     *
     * Carrier scoping resolves `jdk.internal.misc.CarrierThreadLocal`, which lives in a
     * non-exported package, so it needs `--add-exports java.base/jdk.internal.misc=ALL-UNNAMED`.
     * That type only exists on JDK 21+, and the flag *aborts* a Java 8 JVM ("Unrecognized option"),
     * so it is gated on the version of the actual test JVM.
     *
     * MUST be evaluated at task execution time (inside doFirst), not configuration time: the test
     * JVM is selected via JAVA_TEST_HOME, which the CI only makes resolvable at execution time (see
     * the `executable` assignments below).
     */
    private fun carrierExportJvmArgs(project: Project): List<String> {
        val major = testJvmMajorVersionFromRelease()
        val enabled = major >= 21
        project.logger.info(
            "ddprof: carrier --add-exports gate — testJavaHome={}, detected major={}, flag {}",
            PlatformUtils.testJavaHome(), major, if (enabled) "ADDED" else "omitted"
        )
        return if (enabled) listOf("--add-exports=java.base/jdk.internal.misc=ALL-UNNAMED") else emptyList()
    }

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

    /**
     * Shared test task configuration extracted for reuse between Test and Exec paths.
     */
    private data class TestTaskConfiguration(
        val configName: String,
        val isActive: Boolean,
        val testClasspath: FileCollection,
        val standardJvmArgs: List<String>,
        val extraJvmArgs: List<String>,
        val configJvmArgs: List<String>,
        val systemProperties: Map<String, String>,
        val environmentVariables: Map<String, String>
    )

    /**
     * Build shared test configuration used by both Test and Exec task creation.
     */
    private fun buildTestConfiguration(
        project: Project,
        extension: ProfilerTestExtension,
        config: BuildConfiguration,
        testCfg: Configuration,
        sourceSets: SourceSetContainer
    ): TestTaskConfiguration {
        val configName = config.name
        val testEnv = config.testEnvironment.get()

        // Build classpath
        val testClasspath = sourceSets.getByName("test").runtimeClasspath.filter { file ->
            !file.name.contains("ddprof-") || file.name.contains("test-tracer")
        } + testCfg

        // System properties
        val keepRecordings = project.hasProperty("keepJFRs") ||
                             System.getenv("KEEP_JFRS")?.toBoolean() ?: false
        val systemPropsBase = mapOf(
            "ddprof_test.keep_jfrs" to keepRecordings.toString(),
            "ddprof_test.config" to configName,
            "ddprof_test.ci" to (project.hasProperty("CI")).toString(),
            "DDPROF_TEST_DISABLE_RATE_LIMIT" to "1",
            "CI" to (project.hasProperty("CI") || System.getenv("CI")?.toBoolean() ?: false).toString()
        )
        val systemProps = systemPropsBase + testEnv

        // Environment variables (explicit for consistency across both paths)
        val envVars = buildMap<String, String> {
            // Turn silent glibc heap corruption (e.g. a use-after-free write into a
            // freed chunk) into an immediate, attributable SIGABRT instead of a crash
            // much later in an unrelated allocation. Only meaningful against glibc's
            // own malloc: skip on musl (no MALLOC_CHECK_ support), and skip whenever a
            // sanitizer/allocator already replaces malloc via LD_PRELOAD.
            if (PlatformUtils.currentPlatform == Platform.LINUX &&
                !PlatformUtils.isMusl() &&
                !testEnv.containsKey("LD_PRELOAD")
            ) {
                val perturbByte = (1..255).random()
                put("MALLOC_CHECK_", "3")
                put("MALLOC_PERTURB_", perturbByte.toString())
                // Logged so a glibc-detected corruption abort can be reproduced with the
                // same perturb byte (the value is otherwise random per run).
                project.logger.lifecycle("[$configName] MALLOC_PERTURB_=$perturbByte")
            }
            putAll(testEnv)
            put("DDPROF_TEST_DISABLE_RATE_LIMIT", "1")
            put("CI", (project.hasProperty("CI") || System.getenv("CI")?.toBoolean() ?: false).toString())
            // Pass through CI vars (needed for Exec, optional for Test)
            System.getenv("LIBC")?.let { put("LIBC", it) }
            System.getenv("KEEP_JFRS")?.let { put("KEEP_JFRS", it) }
            System.getenv("TEST_COMMIT")?.let { put("TEST_COMMIT", it) }
            System.getenv("TEST_CONFIGURATION")?.let { put("TEST_CONFIGURATION", it) }
            System.getenv("SANITIZER")?.let { put("SANITIZER", it) }
        }

        return TestTaskConfiguration(
            configName = configName,
            isActive = config.active.get(),
            testClasspath = testClasspath,
            standardJvmArgs = extension.standardJvmArgs.get(),
            extraJvmArgs = extension.extraJvmArgs.get(),
            configJvmArgs = config.testJvmArgs.get(),
            systemProperties = systemProps,
            environmentVariables = envVars
        )
    }

    /**
     * Create native Test task for glibc/macOS (normal path).
     * Uses Gradle's Test task with -Ptests property support.
     */
    private fun createTestTask(
        project: Project,
        extension: ProfilerTestExtension,
        testConfig: TestTaskConfiguration,
        testCfg: Configuration,
        sourceSets: SourceSetContainer
    ) {
        project.tasks.register("test${testConfig.configName.replaceFirstChar { it.uppercase() }}", Test::class.java) {
            val testTask = this
            testTask.description = "Runs unit tests with the ${testConfig.configName} library variant"
            testTask.group = "verification"
            testTask.onlyIf { testConfig.isActive && !project.hasProperty("skip-tests") }

            // Dependencies
            testTask.dependsOn(project.tasks.named("compileTestJava"))
            testTask.dependsOn(testCfg)
            testTask.dependsOn(sourceSets.getByName("test").output)

            // Test class directories and classpath
            testTask.testClassesDirs = sourceSets.getByName("test").output.classesDirs
            testTask.classpath = testConfig.testClasspath

            // Use JUnit Platform
            testTask.useJUnitPlatform()

            // Configure Java executable - bypasses toolchain system
            testTask.setExecutable(PlatformUtils.testJavaExecutable())

            // Environment variables (from testConfig which already includes DDPROF_TEST_DISABLE_RATE_LIMIT and CI)
            testConfig.environmentVariables.forEach { (key, value) ->
                testTask.environment(key, value)
            }

            // Test output
            testTask.testLogging {
                val logging = this
                logging.events("started", "passed", "skipped", "failed")
                logging.showStandardStreams = true
            }

            // UNIFIED INTERFACE: Support -Ptests property (same as musl)
            val testsFilter = project.findProperty("tests") as String?
            if (testsFilter != null) {
                // Forward -Ptests to Test task's filter
                testTask.filter.includeTestsMatching(testsFilter)
            }

            // Warn if --tests flag was used instead of -Ptests
            testTask.doFirst {
                val filterPatterns = testTask.filter.includePatterns
                if (filterPatterns.isNotEmpty() && testsFilter == null) {
                    project.logger.warn("")
                    project.logger.warn("WARNING: --tests flag detected. While it works on glibc/macOS, it will FAIL on musl systems.")
                    project.logger.warn("For consistent behavior across all platforms, please use -Ptests instead:")
                    project.logger.warn("  ./gradlew :ddprof-test:${testTask.name} -Ptests=${filterPatterns.first()}")
                    project.logger.warn("")
                }
            }

            // JVM arguments and system properties - configure in doFirst like main does
            testTask.doFirst {
                val allArgs = mutableListOf<String>()
                allArgs.addAll(testConfig.standardJvmArgs)
                // Version-gated at execution time, when the real test JVM is resolvable.
                allArgs.addAll(carrierExportJvmArgs(project))

                if (extension.nativeLibDir.isPresent) {
                    allArgs.add("-Djava.library.path=${extension.nativeLibDir.get().asFile.absolutePath}")
                }

                // System properties as JVM args
                testConfig.systemProperties.forEach { (key, value) ->
                    allArgs.add("-D$key=$value")
                }

                allArgs.addAll(testConfig.extraJvmArgs)
                allArgs.addAll(testConfig.configJvmArgs)
                testTask.jvmArgs(allArgs)
            }

            // Sanitizer conditions
            when (testConfig.configName) {
                "asan" -> {
                    testTask.onlyIf {
                        PlatformUtils.locateLibasan() != null &&
                        // Skip J9+ASAN: OpenJ9 has known GC stack-scanning and defineClass
                        // race bugs exposed by ASAN timing
                        // https://github.com/eclipse-openj9/openj9/issues/23514
                        !PlatformUtils.isTestJvmJ9()
                    }
                    // The ASAN test JVM is pinned to -Xmx1024m (see ConfigurationPresets.kt)
                    // to keep the heap below ASan's shadow-memory region. Without forking,
                    // Gradle reuses one JVM for the whole suite, and per-test allocations
                    // (JFR recordings, JMC object models) accumulate until it OOMs late in
                    // the run even though every individual test passes. Restart periodically
                    // to bound cumulative heap growth.
                    testTask.setForkEvery(25)
                }
                // TSan + JVM integration tests are incompatible: the profiler's signal
                // handlers (SIGPROF at 1ms) are TSan-instrumented; when a signal fires
                // while TSan is updating its shadow memory it causes re-entrance and a
                // SIGSEGV.  TSan coverage is provided by the C++ gtest suite (gtestTsan).
                "tsan" -> testTask.onlyIf { false }
            }
        }
    }

    /**
     * Create Exec task with custom test runner for musl platforms.
     * Uses ProfilerTestRunner with JUnit Platform Launcher API directly.
     * Supports unified -Ptests property interface for test filtering.
     */
    private fun createExecTestTask(
        project: Project,
        extension: ProfilerTestExtension,
        testConfig: TestTaskConfiguration,
        testCfg: Configuration,
        sourceSets: SourceSetContainer
    ) {
        project.tasks.register("test${testConfig.configName.replaceFirstChar { it.uppercase() }}", Exec::class.java) {
            val execTask = this
            execTask.description = "Runs unit tests with the ${testConfig.configName} library variant (musl workaround)"
            execTask.group = "verification"
            execTask.onlyIf { testConfig.isActive && !project.hasProperty("skip-tests") }

            // Dependencies
            execTask.dependsOn(project.tasks.named("compileTestJava"))
            execTask.dependsOn(testCfg)
            execTask.dependsOn(sourceSets.getByName("test").output)

            // Configure at execution time to capture -Ptests filter
            execTask.doFirst {
                execTask.executable = PlatformUtils.testJavaExecutable()

                val allArgs = mutableListOf<String>()

                // JVM args
                allArgs.addAll(testConfig.standardJvmArgs)
                // Version-gated at execution time, when the real test JVM (JAVA_TEST_HOME) is resolvable.
                allArgs.addAll(carrierExportJvmArgs(project))
                if (extension.nativeLibDir.isPresent) {
                    allArgs.add("-Djava.library.path=${extension.nativeLibDir.get().asFile.absolutePath}")
                }
                allArgs.addAll(testConfig.extraJvmArgs)
                allArgs.addAll(testConfig.configJvmArgs)

                // System properties
                testConfig.systemProperties.forEach { (key, value) ->
                    allArgs.add("-D$key=$value")
                }

                // UNIFIED INTERFACE: Test filter from -Ptests property
                val testsFilter = project.findProperty("tests") as String?
                if (testsFilter != null) {
                    allArgs.add("-Dtest.filter=$testsFilter")
                }

                // Classpath (includes custom test runner)
                allArgs.add("-cp")
                allArgs.add(testConfig.testClasspath.asPath)

                // Use custom test runner (NOT ConsoleLauncher)
                allArgs.add("com.datadoghq.profiler.test.ProfilerTestRunner")

                execTask.args = allArgs
            }

            // Environment variables
            // CRITICAL FIX: Filter out LD_LIBRARY_PATH to let RPATH work correctly
            // The test JDK's launcher has RPATH set to find its own libraries ($ORIGIN/../lib/jli)
            // But LD_LIBRARY_PATH overrides RPATH and causes it to load the wrong libjli.so
            // Solution: Never propagate LD_LIBRARY_PATH so RPATH takes precedence
            testConfig.environmentVariables.forEach { (key, value) ->
                if (key == "LD_LIBRARY_PATH") {
                    project.logger.info("Removing LD_LIBRARY_PATH to prevent cross-JDK library conflicts (was: $value)")
                    return@forEach
                }
                execTask.environment(key, value)
            }

            // Sanitizer conditions
            when (testConfig.configName) {
                "asan" -> execTask.onlyIf {
                    PlatformUtils.locateLibasan() != null &&
                    // Skip J9+ASAN: OpenJ9 has known GC stack-scanning and defineClass
                    // race bugs exposed by ASAN timing
                    // https://github.com/eclipse-openj9/openj9/issues/23514
                    !PlatformUtils.isTestJvmJ9()
                }
                "tsan" -> execTask.onlyIf { false }  // same reason as testTask above
            }
        }
    }

    /**
     * Create Exec-based test task that always runs in a separate process.
     * Available on all platforms. Supports -Pprofiler.options for overriding profiler settings.
     * Task name: testProcess<Config> (e.g., testProcessDebug, testProcessRelease)
     */
    private fun createProcessTestTask(
        project: Project,
        extension: ProfilerTestExtension,
        testConfig: TestTaskConfiguration,
        testCfg: Configuration,
        sourceSets: SourceSetContainer
    ) {
        val taskName = "testProcess${testConfig.configName.replaceFirstChar { it.uppercase() }}"
        project.tasks.register(taskName, Exec::class.java) {
            val execTask = this
            execTask.description = "Runs tests in separate process with ${testConfig.configName} library (supports -Pprofiler.options)"
            execTask.group = "verification"
            execTask.onlyIf { testConfig.isActive && !project.hasProperty("skip-tests") }

            // Dependencies
            execTask.dependsOn(project.tasks.named("compileTestJava"))
            execTask.dependsOn(testCfg)
            execTask.dependsOn(sourceSets.getByName("test").output)

            // Configure at execution time to capture properties
            execTask.doFirst {
                execTask.executable = PlatformUtils.testJavaExecutable()

                val allArgs = mutableListOf<String>()

                // JVM args
                allArgs.addAll(testConfig.standardJvmArgs)
                // Version-gated at execution time, when the real test JVM (JAVA_TEST_HOME) is resolvable.
                allArgs.addAll(carrierExportJvmArgs(project))
                if (extension.nativeLibDir.isPresent) {
                    allArgs.add("-Djava.library.path=${extension.nativeLibDir.get().asFile.absolutePath}")
                }
                allArgs.addAll(testConfig.extraJvmArgs)
                allArgs.addAll(testConfig.configJvmArgs)

                // System properties
                testConfig.systemProperties.forEach { (key, value) ->
                    allArgs.add("-D$key=$value")
                }

                // Test filter from -Ptests property
                val testsFilter = project.findProperty("tests") as String?
                if (testsFilter != null) {
                    allArgs.add("-Dtest.filter=$testsFilter")
                }

                // Profiler options from -Pprofiler.options property
                val profilerOptions = project.findProperty("profiler.options") as String?
                if (profilerOptions != null) {
                    allArgs.add("-Dddprof.test.options=$profilerOptions")
                }

                // Classpath
                allArgs.add("-cp")
                allArgs.add(testConfig.testClasspath.asPath)

                // Use custom test runner
                allArgs.add("com.datadoghq.profiler.test.ProfilerTestRunner")

                execTask.args = allArgs
            }

            // Environment variables
            testConfig.environmentVariables.forEach { (key, value) ->
                execTask.environment(key, value)
            }

            // Remove LD_LIBRARY_PATH to let RPATH work correctly
            execTask.doFirst {
                val currentLdLibPath = (execTask.environment["LD_LIBRARY_PATH"] as? String) ?: System.getenv("LD_LIBRARY_PATH")
                if (!currentLdLibPath.isNullOrEmpty()) {
                    project.logger.info("Removing LD_LIBRARY_PATH to prevent cross-JDK library conflicts (was: $currentLdLibPath)")
                    execTask.environment.remove("LD_LIBRARY_PATH")
                }
            }

            // Sanitizer conditions
            when (testConfig.configName) {
                "asan" -> {
                    execTask.onlyIf {
                        PlatformUtils.locateLibasan() != null &&
                        !PlatformUtils.isTestJvmJ9()
                    }
                    // Unlike the Test task's asan variant (setForkEvery(25) above), this task
                    // is a single un-forked Exec process running the whole suite in one JVM —
                    // there is no forkEvery equivalent for Exec. An unfiltered run would
                    // reintroduce the late-suite OOM under ASan's -Xmx512m cap that forkEvery
                    // was added to avoid, so require -Ptests to bound the run instead.
                    execTask.doFirst {
                        if (project.findProperty("tests") == null) {
                            throw GradleException(
                                "$taskName requires -Ptests=<ClassName|ClassName.method> for the " +
                                "asan config: it runs in a single process with no forkEvery " +
                                "equivalent, and JFR/JMC allocations accumulate under ASan's " +
                                "-Xmx512m heap cap until an unfiltered run OOMs late in the suite. " +
                                "For full-suite ASan coverage, use the forked testAsan task instead."
                            )
                        }
                    }
                }
                "tsan" -> execTask.onlyIf { false }
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

            // Build shared configuration
            val testConfig = buildTestConfiguration(project, extension, config, testCfg, sourceSets)

            // Platform-conditional task creation
            // Check both PlatformUtils.isMusl() and LIBC environment variable (set by Docker)
            val isMuslSystem = PlatformUtils.isMusl() || System.getenv("LIBC") == "musl"
            if (isMuslSystem) {
                project.logger.info("Creating Exec task for $configName (musl workaround, LIBC=${System.getenv("LIBC")})")
                createExecTestTask(project, extension, testConfig, testCfg, sourceSets)
            } else {
                project.logger.info("Creating Test task for $configName (glibc/macOS, LIBC=${System.getenv("LIBC")})")
                createTestTask(project, extension, testConfig, testCfg, sourceSets)
            }

            // Create process-based test task (always uses Exec, available on all platforms)
            // Supports -Pprofiler.options for overriding profiler settings
            createProcessTestTask(project, extension, testConfig, testCfg, sourceSets)

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

                    // CRITICAL FIX: Remove LD_LIBRARY_PATH to let RPATH work correctly
                    runTask.doFirst {
                        val currentLdLibPath = (runTask.environment["LD_LIBRARY_PATH"] as? String) ?: System.getenv("LD_LIBRARY_PATH")
                        if (!currentLdLibPath.isNullOrEmpty()) {
                            project.logger.info("Removing LD_LIBRARY_PATH to prevent cross-JDK library conflicts (was: $currentLdLibPath)")
                            runTask.environment.remove("LD_LIBRARY_PATH")
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

                    // CRITICAL FIX: Remove LD_LIBRARY_PATH to let RPATH work correctly
                    reportTask.doFirst {
                        val currentLdLibPath = (reportTask.environment["LD_LIBRARY_PATH"] as? String) ?: System.getenv("LD_LIBRARY_PATH")
                        if (!currentLdLibPath.isNullOrEmpty()) {
                            project.logger.info("Removing LD_LIBRARY_PATH to prevent cross-JDK library conflicts (was: $currentLdLibPath)")
                            reportTask.environment.remove("LD_LIBRARY_PATH")
                        }
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

        // Wire up gtest -> test dependencies (C++ tests run before Java tests)
        project.gradle.projectsEvaluated {
            configNames.forEach { cfgName ->
                val capitalizedCfgName = cfgName.replaceFirstChar { it.uppercaseChar() }
                val testTaskName = "test$capitalizedCfgName"
                val testTask = project.tasks.findByName(testTaskName)
                val profilerLibProject = project.rootProject.findProject(profilerLibProjectPath)

                if (profilerLibProject != null && testTask != null) {
                    // gtest runs before test (C++ unit tests run before Java integration tests)
                    val gtestTaskName = "gtest${capitalizedCfgName}"
                    try {
                        val gtestTask = profilerLibProject.tasks.named(gtestTaskName)
                        testTask.dependsOn(gtestTask)
                    } catch (e: org.gradle.api.UnknownTaskException) {
                        project.logger.info("Task $gtestTaskName not found in $profilerLibProjectPath - gtest may not be available")
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
        // Standard JVM arguments for profiler testing.
        // NOTE: JDK-version-gated flags (e.g. the carrier-scoping --add-exports) must NOT be
        // added here. This convention is computed at configuration time, where JAVA_TEST_HOME
        // is not yet resolvable and PlatformUtils.testJavaHome() falls back to the *build* JDK
        // (JAVA_HOME) — which misdetects in the musl split-JDK CI (build JDK 21, test JDK 8) and
        // would emit a JDK-21 flag onto a JDK-8 test JVM. Version-gated flags are added at
        // execution time in the task doFirst blocks instead (see ProfilerTestPlugin).
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
