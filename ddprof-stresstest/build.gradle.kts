plugins {
  java
  id("me.champeau.jmh") version "0.7.1"
}

repositories {
  mavenCentral()
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
  val javaTestHome = System.getenv("JAVA_TEST_HOME")
  val javaHome = javaTestHome ?: System.getenv("JAVA_HOME")

  // Set the JVM executable - this is used by the JMH plugin to fork benchmark processes
  jvm.set("$javaHome/bin/java")

  // Explicitly set fork to use external JVM (not Gradle's JVM)
  fork.set(3)

  iterations.set(3)
  timeOnIteration.set("3s")
  warmup.set("1s")
  warmupIterations.set(3)
}

// Configure all JMH-related JavaExec tasks to use the correct JDK
tasks.withType<JavaExec>().matching { it.name.startsWith("jmh") }.configureEach {
  val javaTestHome = System.getenv("JAVA_TEST_HOME")
  val javaHome = javaTestHome ?: System.getenv("JAVA_HOME")

  executable = "$javaHome/bin/java"
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
  val javaTestHome = System.getenv("JAVA_TEST_HOME")
  val javaHome = javaTestHome ?: System.getenv("JAVA_HOME")

  group = "Execution"
  description = "Run JMH stresstests"
  commandLine(
    "$javaHome/bin/java",
    "-jar",
    "build/libs/stresstests.jar",
    "-prof",
    "com.datadoghq.profiler.stresstest.WhiteboxProfiler",
    "counters.*"
  )
}

tasks.withType<JavaCompile>().configureEach {
  options.compilerArgs.addAll(listOf("--release", "8"))
}
