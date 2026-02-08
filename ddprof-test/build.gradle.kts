import com.datadoghq.profiler.ProfilerTestExtension

plugins {
  java
  `java-library`
  application
  id("com.datadoghq.profiler-test")
}

repositories {
  mavenCentral()
}

// Reference to native test helpers library directory
val testNativeLibDir = project(":ddprof-test-native").layout.buildDirectory.dir("lib")

// Access version catalog
val catalog = the<VersionCatalogsExtension>().named("libs")

// Configure profiler test plugin - this generates all multi-config tasks automatically
configure<ProfilerTestExtension> {
  // Native library path for JNI test helpers
  nativeLibDir.set(testNativeLibDir)

  // Enable multi-config task generation
  profilerLibProject.set(":ddprof-lib")

  // Extra JVM args specific to this project's tests
  extraJvmArgs.addAll(
    "-Dddprof.disable_unsafe=true",
    "-XX:OnError=/tmp/do_stuff.sh"
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
// The plugin creates testCommon and mainCommon configurations that we extend
afterEvaluate {
  configurations.findByName("testCommon")?.let { testCommon ->
    catalog.findBundle("testing").ifPresent { bundle ->
      bundle.get().forEach { testCommon.dependencies.add(dependencies.create(it)) }
    }
    catalog.findBundle("profiler-runtime").ifPresent { bundle ->
      bundle.get().forEach { testCommon.dependencies.add(dependencies.create(it)) }
    }
    catalog.findLibrary("asm").ifPresent {
      testCommon.dependencies.add(dependencies.create(it.get()))
    }
  }

  configurations.findByName("mainCommon")?.let { mainCommon ->
    catalog.findLibrary("slf4j-simple").ifPresent {
      mainCommon.dependencies.add(dependencies.create(it.get()))
    }
    catalog.findBundle("profiler-runtime").ifPresent { bundle ->
      bundle.get().forEach { mainCommon.dependencies.add(dependencies.create(it)) }
    }
  }
}

// Additional test task configuration beyond what the plugin provides
tasks.withType<Test>().configureEach {
  // Ensure native test library is built before running tests
  dependsOn(":ddprof-test-native:linkLib")

  // Extract config name from task name for test-specific JVM args
  val configName = name.replace("test", "")
  val keepRecordings = project.hasProperty("keepJFRs") || System.getenv("KEEP_JFRS")?.toBoolean() ?: false

  jvmArgs(
    "-Dddprof_test.keep_jfrs=$keepRecordings",
    "-Dddprof_test.config=$configName",
    "-Dddprof_test.ci=${project.hasProperty("CI")}"
  )
}

// Disable the default 'test' task - we use config-specific tasks instead
tasks.named<Test>("test") {
  onlyIf { false }
}

// Java compilation settings
tasks.withType<JavaCompile>().configureEach {
  options.compilerArgs.addAll(listOf("--release", "8"))

  if (name == "compileTestJava") {
    sourceCompatibility = "8"
    targetCompatibility = "8"
  }
}

// Ensure compileTestJava has access to the test dependencies for compilation
// (must be set after project evaluation when the configuration is created)
gradle.projectsEvaluated {
  configurations.findByName("testReleaseImplementation")?.let { testReleaseCfg ->
    tasks.withType<JavaCompile>().configureEach {
      classpath += testReleaseCfg
    }
  }
}
