import com.datadoghq.profiler.ProfilerTestExtension
import org.gradle.api.tasks.SourceSetContainer

plugins {
  java
  `java-library`
  application
  jacoco
  id("com.datadoghq.profiler-test")
  id("com.datadoghq.java-conventions")
}

jacoco {
  toolVersion = "0.8.12"
}

// JaCoCo's plugin auto-attaches a JacocoTaskExtension (enabled by default) to every Test
// task in this project, including testAsan/testSlowAsan/testTsan/testSlowTsan. Restrict
// instrumentation to the plain debug config's tasks only -- asan/tsan already carry
// sanitizer instrumentation and don't need coverage data, and leaving JaCoCo enabled
// everywhere would multiply CI cost for no additional signal.
val coverageTaskNames: Set<String> = if (project.hasProperty("disableJacoco")) emptySet() else setOf("testDebug", "testSlowDebug")

// When jacocoTestReport is actually being requested, don't let a handful of
// known-flaky native-thread/CPU tests (already @RetryingTest-annotated; see
// NativeThreadTest, DynamicNativeThread, VtableReceiverFrameTest, ThreadEntryDetectionTest)
// block report generation -- testDebug still records and prints its failures,
// it just won't fail the build, so jacocoTestReport's dependency is satisfied
// and the exec data that was produced gets aggregated regardless.
val requestingCoverageReport = gradle.startParameter.taskNames.any { it.contains("jacocoTestReport") }

tasks.withType<Test>().configureEach {
  extensions.configure<JacocoTaskExtension> {
    isEnabled = name in coverageTaskNames
  }
  if (name in coverageTaskNames && requestingCoverageReport) {
    ignoreFailures = true
  }
}

// The jacoco plugin already registers a default "jacocoTestReport" task (wired to the
// disabled "test" task); reconfigure it to aggregate our actual coverage-producing tasks
// instead of registering a new one.
tasks.named<JacocoReport>("jacocoTestReport") {
  group = "verification"
  description = "Generates an aggregated HTML/XML coverage report from testDebug and testSlowDebug"

  val coverageTasks = tasks.matching { it.name in coverageTaskNames }
  dependsOn(coverageTasks)
  executionData.setFrom(coverageTasks.map { task ->
    fileTree(task.project.layout.buildDirectory) { include("jacoco/${task.name}.exec") }
  })

  // The tests here exercise ddprof-lib's classes (the profiler itself), not this
  // project's own trivial main sourceSet (just the UnwindingValidator app) -- so
  // coverage must be measured against ddprof-lib, the actual target under test.
  val libMainSourceSet = project(":ddprof-lib").extensions.getByType<SourceSetContainer>()["main"]
  sourceDirectories.setFrom(libMainSourceSet.allSource.srcDirs)
  classDirectories.setFrom(libMainSourceSet.output)

  reports {
    html.required.set(true)
    xml.required.set(true)
    html.outputLocation.set(layout.buildDirectory.dir("reports/jacoco/jacocoTestReport/html"))
    xml.outputLocation.set(layout.buildDirectory.file("reports/jacoco/jacocoTestReport/jacocoTestReport.xml"))
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
tasks.matching { it.name.startsWith("test") && it.name != "test" }.configureEach {
  // Ensure native test library is built before running tests
  dependsOn(":ddprof-test-native:linkLib")
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
