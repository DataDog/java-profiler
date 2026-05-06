import com.datadoghq.native.util.PlatformUtils

plugins {
  java
  id("me.champeau.jmh") version "0.7.3"
  id("com.datadoghq.java-conventions")
}

dependencies {
  implementation(project(mapOf("path" to ":ddprof-lib", "configuration" to "debug")))
  implementation(project(":ddprof-test-tracer"))
  implementation(libs.bundles.jmh)
}

sourceSets {
  named("jmh") {
    java {
      runtimeClasspath += project(":ddprof-lib").sourceSets["main"].output
    }
  }
}

jmh {
  // Set the JVM executable - this is used by the JMH plugin to fork benchmark processes
  jvm.set(PlatformUtils.testJavaExecutable())

  // Explicitly set fork to use external JVM (not Gradle's JVM)
  fork.set(3)

  iterations.set(3)
  timeOnIteration.set("3s")
  warmup.set("1s")
  warmupIterations.set(3)

  val jmhInclude: String? by project
  if (jmhInclude != null) {
    includes.set(listOf(jmhInclude!!))
  }
}

// Configure all JMH-related JavaExec tasks to use the correct JDK
tasks.withType<JavaExec>().matching { it.name.startsWith("jmh") }.configureEach {
  setExecutable(PlatformUtils.testJavaExecutable())
}

tasks.named<Jar>("jmhJar") {
  manifest {
    attributes(
      "Main-Class" to "com.datadoghq.profiler.stresstest.Main",
    )
  }
  archiveFileName.set("stresstests.jar")
}

// --- chaos harness ---------------------------------------------------------
// Long-running antagonist workload driven by the reliability CI cell. NOT a JMH
// benchmark — runs for a wall-clock budget and exits 0 on clean shutdown; JVM
// crashes propagate as non-zero exit codes. Black-box w.r.t. the profiler:
// runs under a dd-java-agent.jar patched with the locally built ddprof.jar.

sourceSets {
  create("chaos")
}

dependencies {
  "chaosImplementation"(libs.asm)
  // dd-trace-api: annotations only at compile time. The patched dd-java-agent
  // provides the (relocated) runtime classes and intercepts @Trace.
  "chaosCompileOnly"(libs.dd.trace.api)
}

tasks.register<Jar>("chaosJar") {
  group = "build"
  description = "Fat jar of the chaos reliability harness"
  archiveFileName.set("chaos.jar")
  from(sourceSets["chaos"].output)
  from({
    configurations["chaosRuntimeClasspath"].map { if (it.isDirectory) it else zipTree(it) }
  })
  duplicatesStrategy = DuplicatesStrategy.EXCLUDE
  manifest {
    attributes("Main-Class" to "com.datadoghq.profiler.chaos.Main")
  }
}

tasks.register<Exec>("runStressTests") {
  dependsOn(tasks.named("jmhJar"))

  group = "application"
  description = "Run JMH stresstests"
  commandLine(
    PlatformUtils.testJavaExecutable(),
    "-jar",
    "build/libs/stresstests.jar",
    "-prof",
    "com.datadoghq.profiler.stresstest.WhiteboxProfiler",
    "counters.*",
  )
}
