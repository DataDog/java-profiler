import com.datadoghq.native.NativeBuildExtension
import com.datadoghq.native.util.PlatformUtils
import org.gradle.internal.os.OperatingSystem

plugins {
  java
  `java-library`
  application
}

repositories {
  mavenCentral()
}

// 1. Define paths and properties
val nativeSrcDir = file("src/test/cpp")
val jniHeadersDir = layout.buildDirectory.dir("generated/jni-headers").get().asFile
val outputLibDir = layout.buildDirectory.dir("libs/native").get().asFile
// Define the name of your JNI library (e.g., "ddproftest" becomes libddproftest.so/ddproftest.dll/libddproftest.dylib)
val libraryName = "ddproftest"

// Determine OS-specific file extensions and library names
val currentOs = OperatingSystem.current()
val libFileExtension = if (currentOs.isMacOsX) "dylib" else "so"
val libraryFileName = "lib$libraryName.$libFileExtension"

// 2. Generate JNI headers using javac
tasks.named<JavaCompile>("compileJava") {
  // Tell javac to generate the JNI headers into the specified directory
  options.compilerArgs.addAll(listOf("-h", jniHeadersDir.absolutePath))
}

// 3. Define a task to compile the native code
tasks.register<Exec>("buildNativeJniLibrary") {
  description = "Compiles the JNI C/C++ sources into a shared library"
  group = "build"

  // Ensure Java compilation (and thus header generation) happens first
  dependsOn(tasks.named("compileJava"))

  // Clean up previous build artifacts
  doFirst {
    outputLibDir.mkdirs()
  }

  // Assume GCC/Clang on Linux/macOS
  commandLine("gcc")
  args("-I${System.getenv("JAVA_HOME")}/include") // Standard JNI includes
  if (currentOs.isMacOsX) {
    args("-I${System.getenv("JAVA_HOME")}/include/darwin") // macOS-specific includes
    args("-dynamiclib") // Build a dynamic library on macOS
  } else if (currentOs.isLinux) {
    args("-I${System.getenv("JAVA_HOME")}/include/linux") // Linux-specific includes
    args("-fPIC")
    args("-shared") // Build a shared library on Linux
    args("-Wl,--build-id") // Embed GNU build-id for remote symbolication testing
  }
  args(nativeSrcDir.listFiles()?.map { it.absolutePath } ?: emptyList<String>()) // Source files
  args("-o", "${outputLibDir.absolutePath}/$libraryFileName") // Output file path
}

// Helper function to add common test dependencies
fun addCommonTestDependencies(configuration: Configuration) {
  configuration.dependencies.add(dependencies.create("org.junit.jupiter:junit-jupiter-api:5.9.2"))
  configuration.dependencies.add(dependencies.create("org.junit.jupiter:junit-jupiter-engine:5.9.2"))
  configuration.dependencies.add(dependencies.create("org.junit.jupiter:junit-jupiter-params:5.9.2"))
  configuration.dependencies.add(dependencies.create("org.slf4j:slf4j-simple:1.7.32"))
  configuration.dependencies.add(dependencies.create("org.openjdk.jmc:flightrecorder:8.1.0"))
  configuration.dependencies.add(dependencies.create("org.openjdk.jol:jol-core:0.16"))
  configuration.dependencies.add(dependencies.create("org.junit-pioneer:junit-pioneer:1.9.1"))
  configuration.dependencies.add(dependencies.create("org.lz4:lz4-java:1.8.0"))
  configuration.dependencies.add(dependencies.create("org.xerial.snappy:snappy-java:1.1.10.1"))
  configuration.dependencies.add(dependencies.create("com.github.luben:zstd-jni:1.5.5-4"))
  configuration.dependencies.add(dependencies.create("org.ow2.asm:asm:9.6"))
  configuration.dependencies.add(dependencies.project(mapOf("path" to ":ddprof-test-tracer")))
}

// Helper function to add common main dependencies
fun addCommonMainDependencies(configuration: Configuration) {
  // Main dependencies for the unwinding validator application
  configuration.dependencies.add(dependencies.create("org.slf4j:slf4j-simple:1.7.32"))
  configuration.dependencies.add(dependencies.create("org.openjdk.jmc:flightrecorder:8.1.0"))
  configuration.dependencies.add(dependencies.create("org.openjdk.jol:jol-core:0.16"))
  configuration.dependencies.add(dependencies.create("org.lz4:lz4-java:1.8.0"))
  configuration.dependencies.add(dependencies.create("org.xerial.snappy:snappy-java:1.1.10.1"))
  configuration.dependencies.add(dependencies.create("com.github.luben:zstd-jni:1.5.5-4"))
  configuration.dependencies.add(dependencies.project(mapOf("path" to ":ddprof-test-tracer")))
}

val testCommon by configurations.creating {
  isCanBeConsumed = true
  isCanBeResolved = true
}

// Configuration for main source set dependencies
val mainCommon by configurations.creating {
  isCanBeConsumed = true
  isCanBeResolved = true
}

// Application configuration
application {
  mainClass.set("com.datadoghq.profiler.unwinding.UnwindingValidator")
}

// Access build configurations from root project plugin extension
val nativeBuildExt = rootProject.extensions.getByType(NativeBuildExtension::class.java)
val currentPlatform = PlatformUtils.currentPlatform
val currentArchitecture = PlatformUtils.currentArchitecture
val activeConfigurations = nativeBuildExt.getActiveConfigurations(currentPlatform, currentArchitecture)
val buildConfigNames = { activeConfigurations.map { it.name } }

activeConfigurations.forEach { config ->
  val name = config.name
  val isActive = config.active.get()
  val testEnv = config.testEnvironment.get()

  logger.debug("Creating configuration for $name")

  // Test configuration
  val cfg = configurations.create("test${name.capitalize()}Implementation") {
    isCanBeConsumed = true
    isCanBeResolved = true
    extendsFrom(testCommon)
  }
  addCommonTestDependencies(cfg)
  cfg.dependencies.add(dependencies.project(mapOf("path" to ":ddprof-lib", "configuration" to name)))

  val task = tasks.register<Test>("test$name") {
    onlyIf {
      isActive
    }
    dependsOn(tasks.named("compileTestJava"))
    description = "Runs the unit tests with the $name library variant"
    group = "verification"
    // Filter classpath to include only necessary dependencies for this test task
    classpath = sourceSets["test"].runtimeClasspath.filter { file ->
      !file.name.contains("ddprof-") || file.name.contains("test-tracer")
    } + cfg

    if (testEnv.isNotEmpty()) {
      testEnv.forEach { (key, value) ->
        environment(key, value)
      }
      logger.debug("Setting environment variables for $name: $testEnv")
    }
    if (name == "asan") {
      onlyIf {
        PlatformUtils.locateLibasan() != null
      }
    } else if (name == "tsan") {
      onlyIf {
        PlatformUtils.locateLibtsan() != null
      }
    }
  }

  // Main/application configuration for unwinding validator (release and debug configs)
  if (name == "release" || name == "debug") {
    val mainCfg = configurations.create("${name}Implementation") {
      isCanBeConsumed = true
      isCanBeResolved = true
      extendsFrom(mainCommon)
    }
    addCommonMainDependencies(mainCfg)
    mainCfg.dependencies.add(dependencies.project(mapOf("path" to ":ddprof-lib", "configuration" to name)))

    // Manual execution task
    tasks.register<JavaExec>("runUnwindingValidator${name.capitalize()}") {
      onlyIf {
        isActive
      }
      dependsOn(tasks.named("compileJava"))
      description = "Run the unwinding validator application (release or debug config)"
      group = "application"
      mainClass.set("com.datadoghq.profiler.unwinding.UnwindingValidator")
      classpath = sourceSets["main"].runtimeClasspath + mainCfg

      if (testEnv.isNotEmpty()) {
        testEnv.forEach { (key, value) ->
          environment(key, value)
        }
      }

      val javaHome = System.getenv("JAVA_TEST_HOME") ?: System.getenv("JAVA_HOME")
      executable = File(javaHome, "bin/java").absolutePath

      jvmArgs(
        "-Djdk.attach.allowAttachSelf",
        "-Djol.tryWithSudo=true",
        "-XX:ErrorFile=build/hs_err_pid%p.log",
        "-XX:+ResizeTLAB",
        "-Xmx512m"
      )
    }

    // Configure arguments for runUnwindingValidator task
    tasks.named<JavaExec>("runUnwindingValidator${name.capitalize()}") {
      if (project.hasProperty("validatorArgs")) {
        setArgs((project.property("validatorArgs") as String).split(" "))
      }
    }

    // CI reporting task
    tasks.register<JavaExec>("unwindingReport${name.capitalize()}") {
      onlyIf {
        isActive
      }
      dependsOn(tasks.named("compileJava"))
      description = "Generate unwinding report for CI (release or debug config)"
      group = "verification"
      mainClass.set("com.datadoghq.profiler.unwinding.UnwindingValidator")
      classpath = sourceSets["main"].runtimeClasspath + mainCfg
      args = listOf(
        "--output-format=markdown",
        "--output-file=build/reports/unwinding-summary.md"
      )

      if (testEnv.isNotEmpty()) {
        testEnv.forEach { (key, value) ->
          environment(key, value)
        }
      }
      environment("CI", project.hasProperty("CI") || System.getenv("CI")?.toBoolean() ?: false)

      val javaHome = System.getenv("JAVA_TEST_HOME") ?: System.getenv("JAVA_HOME")
      executable = File(javaHome, "bin/java").absolutePath

      jvmArgs(
        "-Djdk.attach.allowAttachSelf",
        "-Djol.tryWithSudo=true",
        "-XX:ErrorFile=build/hs_err_pid%p.log",
        "-XX:+ResizeTLAB",
        "-Xmx512m"
      )

      doFirst {
        file("${layout.buildDirectory.get()}/reports").mkdirs()
      }
    }
  }
}

// Create convenience tasks that delegate to the appropriate config
tasks.register("runUnwindingValidator") {
  description = "Run the unwinding validator application (delegates to release if available, otherwise debug)"
  group = "application"
  dependsOn(
    provider {
      when {
        tasks.findByName("runUnwindingValidatorRelease") != null -> listOf("runUnwindingValidatorRelease")
        tasks.findByName("runUnwindingValidatorDebug") != null -> listOf("runUnwindingValidatorDebug")
        else -> throw GradleException("No suitable build configuration available for unwinding validator")
      }
    }
  )

  doLast {
    // Delegate to the appropriate task - actual work is done by dependency
  }
}

tasks.register("unwindingReport") {
  description = "Generate unwinding report for CI (delegates to release if available, otherwise debug)"
  group = "verification"
  dependsOn(
    provider {
      when {
        tasks.findByName("unwindingReportRelease") != null -> listOf("unwindingReportRelease")
        tasks.findByName("unwindingReportDebug") != null -> listOf("unwindingReportDebug")
        else -> throw GradleException("No suitable build configuration available for unwinding report")
      }
    }
  )

  doLast {
    // Delegate to the appropriate task - actual work is done by dependency
  }
}

tasks.withType<Test>().configureEach {
  dependsOn(tasks.named("buildNativeJniLibrary"))

  // this is a shared configuration for all test tasks
  onlyIf {
    !project.hasProperty("skip-tests")
  }

  val configName = name.replace("test", "")

  val keepRecordings = project.hasProperty("keepJFRs") || System.getenv("KEEP_JFRS")?.toBoolean() ?: false
  environment("CI", project.hasProperty("CI") || System.getenv("CI")?.toBoolean() ?: false)
  environment("DDPROF_TEST_DISABLE_RATE_LIMIT", "1") // Disable PID controller rate limiting in tests

  // Base JVM arguments
  val jvmArgsList = listOf(
    "-Dddprof_test.keep_jfrs=$keepRecordings",
    "-Djdk.attach.allowAttachSelf",
    "-Djol.tryWithSudo=true",
    "-Dddprof_test.config=$configName",
    "-Dddprof_test.ci=${project.hasProperty("CI")}",
    "-Dddprof.disable_unsafe=true",
    "-XX:ErrorFile=build/hs_err_pid%p.log",
    "-XX:+ResizeTLAB",
    "-Xmx512m",
    "-XX:OnError=/tmp/do_stuff.sh",
    "-Djava.library.path=${outputLibDir.absolutePath}"
  )

  jvmArgs(jvmArgsList)

  val javaHome = System.getenv("JAVA_TEST_HOME") ?: System.getenv("JAVA_HOME")
  useJUnitPlatform()
  executable = File(javaHome, "bin/java").absolutePath

  testLogging {
    showStandardStreams = true
  }
}

tasks.named<Test>("test") {
  onlyIf {
    false
  }
}

tasks.withType<JavaCompile>().configureEach {
  options.compilerArgs.addAll(listOf("--release", "8"))

  if (name == "compileTestJava") {
    sourceCompatibility = "8"
    targetCompatibility = "8"
  }
  classpath += configurations["testReleaseImplementation"]
}

// Make the assemble* tasks depend on the test* tasks
gradle.projectsEvaluated {
  buildConfigNames().forEach { configName ->
    val testTask = tasks.findByName("test$configName")
    val assembleTask = project(":ddprof-lib").tasks.findByName("assemble${configName.capitalize()}")
    if (testTask != null && assembleTask != null) {
      assembleTask.dependsOn(testTask)
    }

    // Hook C++ gtest tasks to run as part of the corresponding Java test tasks
    // Note: gtest tasks are now in ddprof-lib directly via the GtestPlugin
    val gtestTask = project(":ddprof-lib").tasks.findByName("gtest${configName.capitalize()}")
    if (testTask != null && gtestTask != null) {
      testTask.dependsOn(gtestTask)
    }
  }
}
