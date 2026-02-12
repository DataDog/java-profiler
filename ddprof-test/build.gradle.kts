import com.datadoghq.profiler.ProfilerTestExtension

plugins {
  java
  `java-library`
  application
  id("com.datadoghq.profiler-test")
  id("com.datadoghq.java-conventions")
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
  "testCommon"(libs.asm)

  // Main/application dependencies
  "mainCommon"(libs.slf4j.simple)
  "mainCommon"(libs.bundles.profiler.runtime)
}

// Additional test task configuration beyond what the plugin provides
// The plugin creates Exec tasks (not Test tasks) for config-specific tests
tasks.withType<org.gradle.api.tasks.Exec>().matching { it.name.startsWith("test") }.configureEach {
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
