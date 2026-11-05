/*
 * Memory allocation interceptor for malloc debugging (Linux only).
 */

import com.datadoghq.native.model.Platform
import com.datadoghq.native.util.PlatformUtils

plugins {
  base
  id("com.datadoghq.simple-native-lib")
}

group = "com.datadoghq"

simpleNativeLib {
  // malloc-shim is Linux-only
  enabled.set(PlatformUtils.currentPlatform == Platform.LINUX)

  libraryName.set("debug")
  sourceDir.set(file("src/main/cpp"))
  includeDirs.set(listOf(file("src/main/public").absolutePath))

  compilerArgs.set(
    listOf(
      "-O3",
      "-fno-omit-frame-pointer",
      "-fvisibility=hidden",
      "-std=c++17",
      "-DPROFILER_VERSION=\"${project.version}\"",
      "-fPIC",
    ),
  )
}

// Validation harness for the signal-allocation detector. The harness compiles
// in the production debugSupport.cpp so the Shims wiring chain (dlsym lookup
// and pointer store) is exercised exactly as the profiler builds it.
val harnessBinary = layout.buildDirectory.file("validate/malloc_shim_validate")
val validateOnlyIf = PlatformUtils.currentPlatform == Platform.LINUX && !PlatformUtils.isNativeSkipped(project)

val compileValidateHarness = tasks.register("compileValidateHarness") {
  group = "verification"
  description = "Compile the malloc-shim signal-allocation validation harness"
  onlyIf { validateOnlyIf }

  val harnessSource = file("src/test/cpp/malloc_shim_validate.cpp")
  val debugSupportSource = project(":ddprof-lib").file("src/main/cpp/debugSupport.cpp")

  inputs.files(harnessSource, debugSupportSource)
  inputs.file(project(":ddprof-lib").file("src/main/cpp/debugSupport.h"))
  inputs.file(file("src/main/public/debug.h"))
  outputs.file(harnessBinary)

  doLast {
    // Resolved at execution, not configuration: the probe must not run for
    // e.g. 'help' on a Linux host without a C++ toolchain.
    val compiler = PlatformUtils.findCompiler(project)
    // The harness and debugSupport.cpp use no C++ runtime features, so the
    // C++ standard library is not linked: some minimal toolchains ship clang++
    // without usable libstdc++ link-time paths.
    val args = mutableListOf(
      compiler,
      "-O0",
      "-g",
      "-std=c++17",
      "-DDEBUG",
    )
    if (compiler.contains("clang")) {
      args.add("-nostdlib++")
    }
    args.addAll(
      listOf(
        "-I", file("src/main/public").absolutePath,
        "-I", project(":ddprof-lib").file("src/main/cpp").absolutePath,
        harnessSource.absolutePath,
        debugSupportSource.absolutePath,
        "-ldl",
        "-o", harnessBinary.get().asFile.absolutePath,
      ),
    )
    val proc = ProcessBuilder(args).inheritIO().start()
    if (proc.waitFor() != 0) {
      throw org.gradle.api.GradleException("malloc-shim validate harness compilation failed")
    }
  }

  if (!validateOnlyIf) {
    // Non-Linux or skip-native: never executed (onlyIf { validateOnlyIf });
    // skip the compiler probe so configuration cannot fail.
    enabled = false
  }
}

val validateControl = tasks.register("validateControl", Exec::class) {
  group = "verification"
  description = "Run the malloc-shim harness without LD_PRELOAD (silent-noop control)"
  onlyIf { validateOnlyIf }
  dependsOn(compileValidateHarness)

  commandLine(harnessBinary.get().asFile.absolutePath, "--control")
}

val validateFull = tasks.register("validateFull", Exec::class) {
  group = "verification"
  description = "Run the malloc-shim detection matrix with libdebug.so preloaded"
  onlyIf { validateOnlyIf }
  dependsOn(compileValidateHarness)
  // The simple-native-lib plugin registers "linkLib" only when the extension is
  // enabled (Linux-only here); an unconditional string dependency would fail at
  // graph-calculation time on other platforms.
  if (validateOnlyIf) {
    dependsOn("linkLib")
  }

  val lib = layout.buildDirectory.file("lib/libdebug.${PlatformUtils.sharedLibExtension()}")
  commandLine(harnessBinary.get().asFile.absolutePath)
  environment("LD_PRELOAD", lib.get().asFile.absolutePath)
}

tasks.register("validate") {
  val proj = project
  group = "verification"
  description = "Validate the malloc-shim signal-allocation detector (control + preloaded matrix)"
  onlyIf {
    val platformOk = PlatformUtils.currentPlatform == Platform.LINUX
    val skipped = platformOk && PlatformUtils.isNativeSkipped(proj)
    if (skipped) {
      logger.warn("malloc-shim validate skipped on Linux (skip-native) — signal-allocation detector not exercised")
    }
    validateOnlyIf
  }
  dependsOn(validateControl, validateFull)
}

tasks.named("check") {
  dependsOn("validate")
}
