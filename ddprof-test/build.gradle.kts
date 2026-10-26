/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

import com.datadoghq.profiler.ProfilerTestExtension
import com.datadoghq.profiler.ProfilerTestPlugin
import org.gradle.api.tasks.SourceSetContainer
import java.util.concurrent.ConcurrentHashMap

plugins {
  java
  `java-library`
  application
  jacoco
  id("com.datadoghq.profiler-test")
  id("com.datadoghq.java-conventions")
}

jacoco {
  toolVersion = "0.8.14"
}

// :ddprof-lib:coverageReport produces both the Java (JaCoCo) and the C++ (gcovr) report
// from a single run of the Java test suites: testCoverage and testSlowCoverage (created
// by the profiler-test plugin only with -PenableCoverage) load ddprof-lib's
// gcov-instrumented `coverage` library *and* carry the JaCoCo agent.
//
// JaCoCo's plugin auto-attaches a JacocoTaskExtension (enabled by default) to every Test
// task in this project. Instrument only the coverage config's tasks: ordinary testDebug
// runs (CI included) keep running the profiler against unmodified bytecode -- JaCoCo's
// injected $jacocoInit methods and probe arrays would otherwise show up in the allocation
// and stack-sampling data those tests assert on -- and asan/tsan already carry sanitizer
// instrumentation.
val coverageTaskNames: Set<String> = setOf("testCoverage", "testSlowCoverage")
val enableCoverage = project.hasProperty("enableCoverage")

// When a coverage report is requested, a handful of known-flaky native-thread/CPU tests
// (already @RetryingTest-annotated; see NativeThreadTest, DynamicNativeThread,
// VtableReceiverFrameTest, ThreadEntryDetectionTest) must not keep the report from being
// generated. Their failures are deferred, not ignored: the test task records them and
// lets the report run, and the report task fails the build once the report is written.
val deferredTestFailures: MutableSet<String> = ConcurrentHashMap.newKeySet()

fun Task.deferFailuresToCoverageReport() {
  val taskName = name
  when (this) {
    is Test -> {
      ignoreFailures = true
      addTestListener(object : TestListener {
        override fun beforeSuite(suite: TestDescriptor) {}
        override fun beforeTest(testDescriptor: TestDescriptor) {}
        override fun afterTest(testDescriptor: TestDescriptor, result: TestResult) {}
        override fun afterSuite(suite: TestDescriptor, result: TestResult) {
          if (suite.parent == null && result.resultType == TestResult.ResultType.FAILURE) {
            deferredTestFailures.add(taskName)
          }
        }
      })
    }
    is Exec -> {
      isIgnoreExitValue = true
      doLast {
        if (executionResult.get().exitValue != 0) {
          deferredTestFailures.add(taskName)
        }
      }
    }
  }
}

fun failOnDeferredTestFailures(taskNames: Collection<String>) {
  val failed = taskNames.filter { it in deferredTestFailures }
  if (failed.isNotEmpty()) {
    throw GradleException("Coverage report generated, but tests failed in: ${failed.joinToString()}")
  }
}

tasks.withType<Test>().configureEach {
  extensions.configure<JacocoTaskExtension> {
    isEnabled = name in coverageTaskNames
  }
}

// Pass JaCoCo agent info to Test tasks (glibc/macOS) so AbstractProcessProfilerTest can
// forward coverage to child JVMs. The JaCoCo extension already attaches the agent; we just
// need to tell the test code where to find it for child processes.
tasks.withType<Test>().named { it in coverageTaskNames }.configureEach {
  dependsOn(extractJacocoAgent)
  val agentJar = extractJacocoAgent.map { it.destinationDir.resolve("jacocoagent.jar") }
  doFirst {
    childJacocoDir.get().asFile.mkdirs()
    environment("JACOCO_AGENT_JAR", agentJar.get().absolutePath)
    environment("JACOCO_CHILD_DIR", childJacocoDir.get().asFile.absolutePath)
  }
}

// On musl the profiler-test plugin creates the test tasks as Exec tasks (running its own
// ProfilerTestRunner), which the jacoco plugin doesn't instrument -- attach the agent
// by hand so they write the same build/jacoco/<task>.exec file a Test task would.
// The agent jar ships nested inside the org.jacoco.agent artifact (`jacocoAgent`).
val extractJacocoAgent = tasks.register<Sync>("extractJacocoAgent") {
  from(configurations.named("jacocoAgent").map { zipTree(it.singleFile) }) {
    include("jacocoagent.jar")
  }
  into(layout.buildDirectory.dir("tmp/jacocoAgent"))
}

// Directory where child JVMs spawned by AbstractProcessProfilerTest.launch() write their
// JaCoCo execution data. Each child uses a unique file name to avoid overwrites.
val childJacocoDir = layout.buildDirectory.dir("jacoco/children")

tasks.withType<Exec>().named { it in coverageTaskNames }.configureEach {
  dependsOn(extractJacocoAgent)
  val agentJar = extractJacocoAgent.map { it.destinationDir.resolve("jacocoagent.jar") }
  val execFile = layout.buildDirectory.file("jacoco/$name.exec")
  outputs.file(execFile)
  ProfilerTestPlugin.additionalJvmArgs(this).add(
    provider { "-javaagent:${agentJar.get().absolutePath}=destfile=${execFile.get().asFile.absolutePath},append=false" },
  )
  // Pass the agent jar path to AbstractProcessProfilerTest so it can forward coverage to child JVMs.
  doFirst {
    childJacocoDir.get().asFile.mkdirs()
    (this as Exec).environment("JACOCO_AGENT_JAR", agentJar.get().absolutePath)
    (this as Exec).environment("JACOCO_CHILD_DIR", childJacocoDir.get().asFile.absolutePath)
  }
}

// Every test JVM that loads the coverage library writes .gcda counts next to the
// library's objects when it exits, and :ddprof-lib:coverageReport folds them into the
// C++ report. gcov adds to existing .gcda counts, so clear them once before the coverage
// test tasks run -- not in each task, which would wipe the counts the other one just
// wrote (.gcno files, written at compile time, stay).
val libCoverageObjDir = project(":ddprof-lib").layout.buildDirectory.dir("obj/main/coverage")
val cleanLibCoverageData = tasks.register<Delete>("cleanLibCoverageData") {
  delete(fileTree(libCoverageObjDir) { include("**/*.gcda") })
  // Also clear child JVM JaCoCo data from the previous run.
  delete(fileTree(childJacocoDir) { include("*.exec") })
  // Fail on missing coverage tools before wiping the previous run's counts.
  if (enableCoverage) {
    dependsOn(":ddprof-lib:checkCoverageTools")
  }
}

tasks.named { it in coverageTaskNames }.configureEach {
  dependsOn(cleanLibCoverageData, ":ddprof-lib:checkCoverageTools")
  // cleanLibCoverageData always clears the .gcda counts, so the tests must always rerun to
  // write them again -- never UP-TO-DATE (which the musl Exec tasks would otherwise be: they
  // declare the JaCoCo .exec file as an output but no inputs). The same applies to a deferred
  // failure, whose results are cached like a pass would be.
  outputs.upToDateWhen { false }
}

// Decided from the resolved task graph, not the CLI task names, so abbreviations
// (`covRep`) and runs that pull the report in as a dependency defer failures too.
gradle.taskGraph.whenReady {
  if (hasTask(":ddprof-lib:coverageReport")) {
    allTasks.filter { it.project == project && it.name in coverageTaskNames }
      .forEach { it.deferFailuresToCoverageReport() }
  }
}

// Runs after coverageReport's own gcovr doLast, so both reports are written first.
project(":ddprof-lib").tasks.named { it == "coverageReport" }.configureEach {
  doLast { failOnDeferredTestFailures(coverageTaskNames) }
}

// The jacoco plugin already registers a default "jacocoTestReport" task (wired to the
// disabled "test" task); reconfigure it as the Java half of :ddprof-lib:coverageReport
// instead of registering a new one.
tasks.named<JacocoReport>("jacocoTestReport") {
  group = "verification"
  description = "Java half of :ddprof-lib:coverageReport (run that instead; requires -PenableCoverage)"

  dependsOn(tasks.named { it in coverageTaskNames })
  // The .exec files from: (1) the main test tasks (Test via jacoco plugin, musl Exec via agent
  // attached above), and (2) child JVMs spawned by AbstractProcessProfilerTest.launch().
  // Only existing files: a task that ran no tests writes none.
  executionData.setFrom(
    files(coverageTaskNames.map { layout.buildDirectory.file("jacoco/$it.exec") }).filter { it.exists() },
    fileTree(childJacocoDir) { include("*.exec") },
  )

  // The tests here exercise ddprof-lib's classes (the profiler itself), not this
  // project's own trivial main sourceSet (just the UnwindingValidator app) -- so
  // coverage must be measured against ddprof-lib, the actual target under test.
  val libMainSourceSet = project(":ddprof-lib").extensions.getByType<SourceSetContainer>()["main"]
  sourceDirectories.setFrom(libMainSourceSet.allSource.srcDirs)
  classDirectories.setFrom(libMainSourceSet.output)

  // Test failures are checked by coverageReport, after both reports are written.

  // Next to the C++ report (ddprof-lib/build/reports/coverage/cpp).
  val javaReportDir = project(":ddprof-lib").layout.buildDirectory.dir("reports/coverage/java")
  reports {
    html.required.set(true)
    xml.required.set(true)
    html.outputLocation.set(javaReportDir.map { it.dir("html") })
    xml.outputLocation.set(javaReportDir.map { it.file("jacoco.xml") })
  }
}

// Reference to native test helpers library directory
val testNativeLibDir = project(":ddprof-test-native").layout.buildDirectory.dir("lib")

// Configure profiler test plugin - this generates all multi-config tasks automatically
configure<ProfilerTestExtension> {
  // Native library path for JNI test helpers
  nativeLibDir.set(testNativeLibDir)

  // Enable multi-config task generation
  profilerLibProject.set(":ddprof-lib")

  // Extra JVM args specific to this project's tests
  extraJvmArgs.addAll(
    "-Dddprof.disable_unsafe=true",
    "-XX:OnError=/tmp/do_stuff.sh",
  )

  // Optional per-invocation heap override (-PtestMaxHeap=1536m). Appended after
  // standardJvmArgs' default -Xmx512m, so the last -Xmx on the command line wins.
  // Left unset everywhere except CI environments that need more headroom (e.g.
  // the EL7 functional job's shared runner pod, see functional-tests.sh) so the
  // shared 512m default is unaffected elsewhere.
  (project.findProperty("testMaxHeap") as String?)?.let { maxHeap ->
    extraJvmArgs.add("-Xmx$maxHeap")
  }
}

// Generate JNI headers using javac
val jniHeadersDir = layout.buildDirectory.dir("generated/jni-headers")
tasks.named<JavaCompile>("compileJava") {
  options.compilerArgs.addAll(listOf("-h", jniHeadersDir.get().asFile.absolutePath))
}

// Application configuration (for the run task)
application {
  mainClass.set("com.datadoghq.profiler.unwinding.UnwindingValidator")
}

// Add common dependencies to test and main configurations
// The plugin creates testCommon and mainCommon configurations eagerly
dependencies {
  // Test dependencies
  "testCommon"(libs.bundles.testing)
  "testCommon"(libs.bundles.profiler.runtime)
  "testCommon"(libs.jafar.parser)
  "testCommon"(libs.asm)

  // Main/application dependencies
  "mainCommon"(libs.slf4j.simple)
  "mainCommon"(libs.bundles.profiler.runtime)
}

// Additional test task configuration beyond what the plugin provides
// The plugin creates Test tasks on glibc/macOS and Exec tasks on musl
// Both need the native test library to be built first
val skipGtest = project.hasProperty("skip-gtest")
tasks.matching { it.name.startsWith("test") && it.name != "test" }.configureEach {
  // Ensure native test library is built before running tests
  dependsOn(":ddprof-test-native:linkLib")

  // Read back the .jfr written by :ddprof-lib's referenceChainJfrRoundtrip_ut gtest for the
  // same configuration (the task name encodes it; the path is scoped per configuration in
  // ddprof-lib/build.gradle.kts, which see). The profiler-test plugin's test<config> ->
  // gtest<config> wiring already orders that producer ahead of this task.
  val config = name.removePrefix("test").removePrefix("Slow").lowercase()
  val jfr = rootProject.layout.buildDirectory
    .file("tmp/reference-chain-roundtrip/$config/datadog_reference_chain_roundtrip.jfr")
    .get()
    .asFile
  (this as? ProcessForkOptions)?.environment("DDPROF_REFERENCE_CHAIN_ROUNDTRIP_JFR", jfr.absolutePath)
  if (skipGtest) {
    // The producing gtest does not run in this invocation: drop any file from an earlier one
    // so the parser test skips (Assumptions gate) instead of checking a stale recording.
    doFirst { jfr.delete() }
  }
}

// Disable the default 'test' task - we use config-specific tasks instead
tasks.named<Test>("test") {
  onlyIf { false }
}

// Java compilation settings handled by java-conventions plugin (--release 8)

// Ensure compileTestJava has access to the test dependencies for compilation
// (must be set after project evaluation when the configuration is created)
gradle.projectsEvaluated {
  configurations.findByName("testReleaseImplementation")?.let { testReleaseCfg ->
    tasks.withType<JavaCompile>().configureEach {
      classpath += testReleaseCfg
    }
  }
}
