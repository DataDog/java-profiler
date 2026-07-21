/*
 * Copyright 2026, Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
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
  // ddprof-lib public API: compile-only; the patched dd-java-agent provides the
  // classes at runtime for antagonists that call JavaProfiler/ThreadContext directly.
  "chaosCompileOnly"(project(mapOf("path" to ":ddprof-lib", "configuration" to "debug")))
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

// --- reference-chains repro app ---------------------------------------------
// Plain, dependency-free demo app for manually reproducing the reference-chains
// feature: launched directly with `-agentpath:libjavaProfiler.so=start,...`
// (no dd-trace-java agent, no dynamic attach), so it deliberately has zero
// compile/runtime dependency on ddprof-lib or dd-trace - the profiler is
// entirely out-of-process from this app's own point of view.

sourceSets {
  create("repro")
}

dependencies {
  // ddprof-lib's Java API only - not the native library itself (that's the one
  // already loaded in-process via -agentpath). Used solely to call
  // JavaProfiler.getInstance().dump(...) periodically: Profiler::dump()
  // (profiler.cpp) is the only code path that drains ReferenceChainTracker's
  // pending chain-event queue and actually writes datadog.ReferenceChain into
  // the JFR file - nothing does this automatically on a timer, and in
  // production it's dd-trace-java's own recording-chunk rotation that calls
  // it. Without this dependency+call, chain events get built and enqueued
  // (visible in TEST_LOG output) but are silently dropped when the process
  // exits, and the JFR file never shows a single datadog.ReferenceChain event.
  "reproImplementation"(project(mapOf("path" to ":ddprof-lib", "configuration" to "debug")))
}

tasks.register<Jar>("reproJar") {
  group = "build"
  description = "Demo app that leaks memory in a controlled way, for manually reproducing reference-chains via -agentpath"
  archiveFileName.set("refchains_repro.jar")
  from(sourceSets["repro"].output)
  from({
    configurations["reproRuntimeClasspath"].map { if (it.isDirectory) it else zipTree(it) }
  })
  duplicatesStrategy = DuplicatesStrategy.EXCLUDE
  manifest {
    attributes("Main-Class" to "com.datadoghq.profiler.repro.ReferenceChainLeakDemo")
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
