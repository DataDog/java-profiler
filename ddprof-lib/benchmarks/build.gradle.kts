/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 * Benchmark for testing unwinding failures.
 * Uses NativeCompileTask/NativeLinkExecutableTask from build-logic.
 */

import com.datadoghq.native.model.Platform
import com.datadoghq.native.tasks.NativeCompileTask
import com.datadoghq.native.tasks.NativeLinkExecutableTask
import com.datadoghq.native.util.PlatformUtils
import java.io.ByteArrayOutputStream

plugins {
  base
  // Note: Does NOT use native-build plugin - tasks are created manually below
  // because this project has a single benchmark executable, not the standard
  // multi-config library structure
}

val benchmarkName = "unwind_failures_benchmark"

// Determine if we should build for this platform
val shouldBuild = PlatformUtils.currentPlatform == Platform.MACOS ||
  PlatformUtils.currentPlatform == Platform.LINUX

if (shouldBuild) {
  // Resolved lazily: the probe must not run at configuration time (e.g. for
  // 'help' on a host without a C++ compiler); it fires only when a task that
  // consumes the property runs, which the tasks' onlyIf gates on shouldBuild
  // and the skip-native flag.
  val compiler = providers.provider { PlatformUtils.findCompiler(project) }
  // This is the :ddprof-lib:benchmarks subproject, whose own name
  // ("benchmarks") is not what a caller means by -Pskip-native=ddprof-lib --
  // benchmarking is part of ddprof-lib's native surface, not a project a
  // caller names on its own, so the check goes through the parent project's
  // identity instead of this one's.
  val nativeSkipped = PlatformUtils.isNativeSkipped(project.parent ?: project)

  // Compile task
  val compileTask = tasks.register<NativeCompileTask>("compileBenchmark") {
    onlyIf { shouldBuild && !nativeSkipped }
    group = "build"
    description = "Compile the unwinding failures benchmark"

    this.compiler.set(compiler)
    compilerArgs.set(listOf("-O2", "-g", "-std=c++17", "-DDEBUG"))
    sources.from(file("src/unwindFailuresBenchmark.cpp"))
    includes.from(project(":ddprof-lib").file("src/main/cpp"))
    objectFileDir.set(file("${layout.buildDirectory.get()}/obj/benchmark"))
  }

  // Link task
  val binary = file("${layout.buildDirectory.get()}/bin/$benchmarkName")
  val linkTask = tasks.register<NativeLinkExecutableTask>("linkBenchmark") {
    onlyIf { shouldBuild && !nativeSkipped }
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

// Advisory estimator for the per-op cost of the NativeMem accounting
// calls, compiled against the production nativeMem.cpp. Linux-gated: the
// marker reader and libc probe are Linux sources.
val estimatorFlags = listOf("-O3", "-DNDEBUG", "-g", "-std=c++17")
// Resolved lazily like the benchmark compiler above: the probe must not
// run at configuration time.
val estimatorCompiler = providers.provider { PlatformUtils.findCompiler(project) }
val estimatorNativeSkipped = PlatformUtils.isNativeSkipped(project.parent ?: project)
// Separate from obj/benchmark, which linkBenchmark globs.
val estimatorObjDir = file("${layout.buildDirectory.get()}/obj/native-mem-estimator")
val estimatorBinary = file("${layout.buildDirectory.get()}/bin/native_mem_cost_estimator")

val compileEstimator = tasks.register<NativeCompileTask>("compileNativeMemEstimator") {
  onlyIf { shouldBuild && !estimatorNativeSkipped && PlatformUtils.currentPlatform == Platform.LINUX }
  group = "build"
  description = "Compile the native memory accounting cost estimator"

  this.compiler.set(estimatorCompiler)
  compilerArgs.set(estimatorFlags)
  // The report prints the build flags; they match the release preset, so the
  // record() assert is stripped as in shipped builds.
  defines.set(listOf("ESTIMATOR_BUILD_FLAGS=\"" + estimatorFlags.joinToString(" ") + "\""))
  sources.from(
    file("src/nativeMemCostEstimator.cpp"),
    file("src/estimatorSupport_linux.cpp"),
    project(":ddprof-lib").file("src/main/cpp/nativeMem.cpp"),
  )
  includes.from(project(":ddprof-lib").file("src/main/cpp"))
  objectFileDir.set(estimatorObjDir)
}

val linkEstimator = tasks.register<NativeLinkExecutableTask>("linkNativeMemEstimator") {
  onlyIf { shouldBuild && !estimatorNativeSkipped && PlatformUtils.currentPlatform == Platform.LINUX }
  dependsOn(compileEstimator)
  group = "build"
  description = "Link the native memory accounting cost estimator"

  linker.set(estimatorCompiler)
  linkerArgs.set(listOf())
  objectFiles.from(fileTree(estimatorObjDir) { include("*.o") })
  outputFile.set(estimatorBinary)
}

tasks.register<Exec>("runNativeMemEstimator") {
  dependsOn(linkEstimator)
  onlyIf { shouldBuild && !estimatorNativeSkipped && PlatformUtils.currentPlatform == Platform.LINUX }
  group = "verification"
  description = "Run the native memory accounting cost estimator (advisory)"

  executable = estimatorBinary.absolutePath

  // Add any additional arguments passed to the Gradle task
  doFirst {
    if (project.hasProperty("args")) {
      args(project.property("args").toString().split(" "))
    }
    println("Running estimator: ${estimatorBinary.absolutePath}")
  }

  doLast {
    println("Estimator completed.")
  }
}

interface EstimatorExecServices {
  @get:Inject val exec: ExecOperations
}

// Verification for the estimator itself: each test-only fault option must
// exit non-zero, and the demo-length normal run must exit 0 with the full
// report. Advisory, like the estimator: not wired into any CI gate.
tasks.register("verifyNativeMemEstimator") {
  dependsOn(linkEstimator)
  onlyIf { shouldBuild && !estimatorNativeSkipped && PlatformUtils.currentPlatform == Platform.LINUX }
  group = "verification"
  description = "Verify the estimator's fault modes and normal-run report"

  val exec = objects.newInstance<EstimatorExecServices>().exec
  val binaryPath = estimatorBinary.absolutePath

  doLast {
    val failed = mutableListOf<String>()
    // The stderr needle catches a fault option that is parsed but no longer
    // fails: the branch would exit 0 or with an unrelated error text.
    val faultCases = listOf(
      listOf("--demo", "--force-bad-hash") to "trace hash mismatch",
      listOf("--demo", "--skip-accounting-call") to "accounting mismatch",
      listOf("--demo", "--inject-zero") to "self-test",
    )
    for ((faultArgs, needle) in faultCases) {
      val stderr = ByteArrayOutputStream()
      val result = exec.exec {
        commandLine(binaryPath)
        args(faultArgs)
        isIgnoreExitValue = true
        errorOutput = stderr
      }
      val text = stderr.toString()
      when {
        result.exitValue == 0 -> failed += "$faultArgs exited 0 instead of failing"
        !text.contains(needle) -> failed += "$faultArgs failed without '$needle' in stderr"
        else -> logger.lifecycle("verifyNativeMemEstimator: $faultArgs exited ${result.exitValue} as expected")
      }
    }

    val stdout = ByteArrayOutputStream()
    val stderr = ByteArrayOutputStream()
    val result = exec.exec {
      commandLine(binaryPath)
      args("--demo")
      isIgnoreExitValue = true
      standardOutput = stdout
      errorOutput = stderr
    }
    val report = stdout.toString()
    if (result.exitValue != 0) {
      failed += "normal run exited ${result.exitValue}: ${stderr.toString().trim()}"
    } else {
      // ia_ci_contains_magnitude is a calibration report, never a gate.
      val requiredFields = listOf(
        "median_delta_ns_per_op", "delta_ci95_low_ns_per_op", "delta_ci95_high_ns_per_op",
        "sign_test_p", "aa_median_ns_per_op", "aa_ci95_low_ns_per_op", "aa_ci95_high_ns_per_op",
        "ia_median_ns_per_op", "ia_ci95_low_ns_per_op", "ia_ci95_high_ns_per_op",
        "ia_ci_contains_magnitude", "injected_ns_per_op", "self_test", "trace_hash",
        "trace_seed", "pair_seed", "pair_count", "ops", "libc_name", "libc_version",
        "flags", "marker_windows",
      )
      for (field in requiredFields) {
        if (!report.contains("$field=")) {
          failed += "normal run is missing report field $field"
        }
      }
      if (listOf("yes", "no").none { report.contains("ia_ci_contains_magnitude=$it") }) {
        failed += "normal run reports an invalid ia_ci_contains_magnitude value"
      }
      if (!report.contains("self_test=pass")) {
        failed += "normal run does not report self_test=pass"
      }
      if (report.lines().none { it.startsWith("markers: ") }) {
        failed += "normal run reports no window markers"
      }
      logger.lifecycle("verifyNativeMemEstimator: normal run exited 0 with ${report.lines().size} report lines")
    }
    if (failed.isNotEmpty()) {
      throw GradleException("estimator verification failed: ${failed.joinToString("; ")}")
    }
  }
}
