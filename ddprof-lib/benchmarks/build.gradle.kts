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
  // Note: Does NOT use native-build plugin - tasks are created manually below
  // because this project has a single benchmark executable, not the standard
  // multi-config library structure
}

data class BenchmarkDef(val name: String, val source: String)

val benchmarks = listOf(
  BenchmarkDef("unwind_failures_benchmark", "src/unwindFailuresBenchmark.cpp"),
  BenchmarkDef("hot_path_benchmark", "src/hotPathBenchmark.cpp"),
)

// Determine if we should build for this platform
val shouldBuild = PlatformUtils.currentPlatform == Platform.MACOS ||
  PlatformUtils.currentPlatform == Platform.LINUX

if (shouldBuild) {
  val compiler = PlatformUtils.findCompiler(project)

  benchmarks.forEach { bench ->
    val safeName = bench.name.split('_').joinToString("") { it.replaceFirstChar { c -> c.uppercase() } }

    // Compile task
    val compileTask = tasks.register<NativeCompileTask>("compile$safeName") {
      onlyIf { shouldBuild && !project.hasProperty("skip-native") }
      group = "build"
      description = "Compile ${bench.name}"

      this.compiler.set(compiler)
      compilerArgs.set(listOf("-O2", "-g", "-std=c++17"))
      sources.from(file(bench.source))
      includes.from(project(":ddprof-lib").file("src/main/cpp"))
      objectFileDir.set(file("${layout.buildDirectory.get()}/obj/${bench.name}"))
    }

    // Link task
    val binary = file("${layout.buildDirectory.get()}/bin/${bench.name}")
    val linkTask = tasks.register<NativeLinkExecutableTask>("link$safeName") {
      onlyIf { shouldBuild && !project.hasProperty("skip-native") }
      dependsOn(compileTask)
      group = "build"
      description = "Link ${bench.name}"

      linker.set(compiler)
      val args = mutableListOf("-ldl", "-lpthread")
      if (PlatformUtils.currentPlatform == Platform.LINUX) {
        args.add("-lrt")
      }
      linkerArgs.set(args)
      objectFiles.from(fileTree("${layout.buildDirectory.get()}/obj/${bench.name}") { include("*.o") })
      outputFile.set(binary)
    }

    tasks.named("assemble") {
      dependsOn(linkTask)
    }

    tasks.register<Exec>("run$safeName") {
      dependsOn(linkTask)
      group = "verification"
      description = "Run ${bench.name}"

      executable = binary.absolutePath

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

  // Convenience alias: runBenchmark → original unwind failures benchmark
  tasks.register<Exec>("runBenchmark") {
    dependsOn("linkUnwindFailuresBenchmark")
    group = "verification"
    description = "Run the unwinding failures benchmark (alias)"
    executable = file("${layout.buildDirectory.get()}/bin/unwind_failures_benchmark").absolutePath
    doFirst {
      if (project.hasProperty("args")) {
        args(project.property("args").toString().split(" "))
      }
    }
  }
}
