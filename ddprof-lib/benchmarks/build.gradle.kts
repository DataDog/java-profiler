// Copyright 2026, Datadog, Inc

/*
 * Benchmark for testing unwinding failures.
 * Uses NativeCompileTask/NativeLinkExecutableTask from build-logic.
 */

import com.datadoghq.native.model.Platform
import com.datadoghq.native.tasks.NativeCompileTask
import com.datadoghq.native.tasks.NativeLinkExecutableTask
import com.datadoghq.native.util.PlatformUtils

plugins {
  base
  id("com.datadoghq.native-build")
}

val benchmarkName = "unwind_failures_benchmark"

// Determine if we should build for this platform
val shouldBuild = PlatformUtils.currentPlatform == Platform.MACOS ||
  PlatformUtils.currentPlatform == Platform.LINUX

if (shouldBuild) {
  val compiler = PlatformUtils.findCompiler(project)

  // Compile task
  val compileTask = tasks.register<NativeCompileTask>("compileBenchmark") {
    onlyIf { shouldBuild && !project.hasProperty("skip-native") }
    group = "build"
    description = "Compile the unwinding failures benchmark"

    this.compiler.set(compiler)
    compilerArgs.set(listOf("-O2", "-g", "-std=c++17"))
    sources.from(file("src/unwindFailuresBenchmark.cpp"))
    includes.from(project(":ddprof-lib").file("src/main/cpp"))
    objectFileDir.set(file("${layout.buildDirectory.get()}/obj/benchmark"))
  }

  // Link task
  val binary = file("${layout.buildDirectory.get()}/bin/$benchmarkName")
  val linkTask = tasks.register<NativeLinkExecutableTask>("linkBenchmark") {
    onlyIf { shouldBuild && !project.hasProperty("skip-native") }
    dependsOn(compileTask)
    group = "build"
    description = "Link the unwinding failures benchmark"

    linker.set(compiler)
    val args = mutableListOf("-ldl", "-lpthread")
    if (PlatformUtils.currentPlatform == Platform.LINUX) {
      args.add("-lrt")
    }
    linkerArgs.set(args)
    objectFiles.from(fileTree("${layout.buildDirectory.get()}/obj/benchmark") { include("*.o") })
    outputFile.set(binary)
  }

  // Wire linkBenchmark into the standard assemble lifecycle
  tasks.named("assemble") {
    dependsOn(linkTask)
  }

  // Add a task to run the benchmark
  tasks.register<Exec>("runBenchmark") {
    dependsOn(linkTask)
    group = "verification"
    description = "Run the unwinding failures benchmark"

    executable = binary.absolutePath

    // Add any additional arguments passed to the Gradle task
    doFirst {
      if (project.hasProperty("args")) {
        args(project.property("args").toString().split(" "))
      }
      println("Running benchmark: ${binary.absolutePath}")
    }

    doLast {
      println("Benchmark completed.")
    }
  }
}
