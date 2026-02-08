import com.datadoghq.native.util.PlatformUtils

plugins {
  java
  id("me.champeau.jmh") version "0.7.1"
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
}

// Configure all JMH-related JavaExec tasks to use the correct JDK
tasks.withType<JavaExec>().matching { it.name.startsWith("jmh") }.configureEach {
  executable = PlatformUtils.testJavaExecutable()
}

tasks.named<Jar>("jmhJar") {
  manifest {
    attributes(
      "Main-Class" to "com.datadoghq.profiler.stresstest.Main"
    )
  }
  archiveFileName.set("stresstests.jar")
}

tasks.register<Exec>("runStressTests") {
  dependsOn(tasks.named("jmhJar"))

  group = "Execution"
  description = "Run JMH stresstests"
  commandLine(
    PlatformUtils.testJavaExecutable(),
    "-jar",
    "build/libs/stresstests.jar",
    "-prof",
    "com.datadoghq.profiler.stresstest.WhiteboxProfiler",
    "counters.*"
  )
}
