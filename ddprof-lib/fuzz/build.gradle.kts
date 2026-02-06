// Copyright 2026, Datadog, Inc

/*
 * Gradle build file for libFuzzer-based fuzz testing.
 * This module compiles and runs fuzz targets against the profiler's C++ code
 * to discover bugs through automated input generation.
 *
 * Uses NativeCompileTask/NativeLinkExecutableTask from build-logic.
 */

import com.datadoghq.native.model.Platform
import com.datadoghq.native.tasks.NativeCompileTask
import com.datadoghq.native.tasks.NativeLinkExecutableTask
import com.datadoghq.native.util.PlatformUtils
import java.io.File
import java.util.concurrent.TimeUnit

plugins {
  base
  id("com.datadoghq.native-build")
}

// Default fuzz duration in seconds (can be overridden with -Pfuzz-duration=N)
val fuzzDuration = if (project.hasProperty("fuzz-duration")) {
  project.property("fuzz-duration").toString().toInt()
} else {
  60
}

// Directory for crash artifacts
val crashDir = file("${layout.buildDirectory.get()}/fuzz-crashes")

// Directory for seed corpus
val corpusDir = project(":ddprof-lib").file("src/test/fuzz/corpus")

// Helper to detect Homebrew LLVM on macOS
fun findHomebrewLLVM(): String? {
  if (PlatformUtils.currentPlatform != Platform.MACOS) {
    return null
  }

  val possiblePaths = listOf(
    "/opt/homebrew/opt/llvm", // Apple Silicon
    "/usr/local/opt/llvm" // Intel Mac
  )

  for (path in possiblePaths) {
    val llvmDir = File(path)
    if (llvmDir.exists() && File("$path/bin/clang++").exists()) {
      logger.info("Found Homebrew LLVM at: $path")
      return path
    }
  }

  // Try using brew command
  try {
    val process = ProcessBuilder("brew", "--prefix", "llvm")
      .redirectErrorStream(true)
      .start()
    process.waitFor(5, TimeUnit.SECONDS)
    if (process.exitValue() == 0) {
      val brewPath = process.inputStream.bufferedReader().readText().trim()
      if (File("$brewPath/bin/clang++").exists()) {
        logger.info("Found Homebrew LLVM via brew command at: $brewPath")
        return brewPath
      }
    }
  } catch (e: Exception) {
    // brew not available or failed
  }

  return null
}

val homebrewLLVM = findHomebrewLLVM()

// Find the clang version directory within Homebrew LLVM
fun findClangResourceDir(llvmPath: String?): String? {
  if (llvmPath == null) {
    return null
  }

  val clangLibDir = File("$llvmPath/lib/clang")
  if (!clangLibDir.exists()) {
    return null
  }

  // Find the version directory (e.g., 18.1.8 or 19)
  val versions = clangLibDir.listFiles()
    ?.filter { it.isDirectory }
    ?.sortedByDescending { it.name }

  if (versions != null && versions.isNotEmpty()) {
    val resourceDir = "$llvmPath/lib/clang/${versions[0].name}"
    logger.info("Using clang resource directory: $resourceDir")
    return resourceDir
  }

  return null
}

val clangResourceDir = findClangResourceDir(homebrewLLVM)

// Helper to find fuzzer-capable clang++ (prefers Homebrew on macOS)
fun findFuzzerCompiler(): String {
  if (PlatformUtils.currentPlatform == Platform.MACOS && homebrewLLVM != null) {
    return "$homebrewLLVM/bin/clang++"
  }
  // Fall back to standard compiler detection
  return PlatformUtils.findCompiler(project)
}

// Check if fuzzer is available
val hasFuzzer = PlatformUtils.hasFuzzer()

// Master fuzz task
val fuzzAll = tasks.register("fuzz") {
  onlyIf {
    hasFuzzer &&
      !project.hasProperty("skip-tests") &&
      !project.hasProperty("skip-native") &&
      !project.hasProperty("skip-fuzz")
  }
  group = "verification"
  description = "Run all fuzz targets"

  doFirst {
    if (!hasFuzzer) {
      logger.warn("WARNING: libFuzzer not available - skipping fuzz tests (requires clang with -fsanitize=fuzzer)")
    }
  }
}

// Only create fuzz tasks if fuzzer is available
if (hasFuzzer) {
  val compiler = findFuzzerCompiler()

  // Java home for JNI includes
  val javaHome = PlatformUtils.javaHome()
  val platformInclude = when (PlatformUtils.currentPlatform) {
    Platform.LINUX -> "linux"
    Platform.MACOS -> "darwin"
  }

  // Build include paths
  val includeFiles = files(
    project(":ddprof-lib").file("src/main/cpp"),
    "$javaHome/include",
    "$javaHome/include/$platformInclude",
    project(":malloc-shim").file("src/main/public")
  ).let { baseIncludes ->
    if (PlatformUtils.currentPlatform == Platform.MACOS && homebrewLLVM != null) {
      baseIncludes + files("$homebrewLLVM/include")
    } else {
      baseIncludes
    }
  }

  // Build compiler args for fuzzing
  val fuzzCompilerArgs = mutableListOf(
    "-O1",
    "-g",
    "-fno-omit-frame-pointer",
    "-fsanitize=fuzzer,address,undefined",
    "-fvisibility=hidden",
    "-std=c++17",
    "-DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION"
  )
  if (PlatformUtils.currentPlatform == Platform.LINUX && PlatformUtils.isMusl()) {
    fuzzCompilerArgs.add("-D__musl__")
  }

  // Build linker args
  val fuzzLinkerArgs = mutableListOf<String>()

  // libFuzzer linking strategy:
  // On macOS with Homebrew LLVM, explicitly link the library file
  // because system clang looks in the wrong location
  if (PlatformUtils.currentPlatform == Platform.MACOS && clangResourceDir != null) {
    val fuzzerLib = "$clangResourceDir/lib/darwin/libclang_rt.fuzzer_osx.a"
    if (File(fuzzerLib).exists()) {
      logger.info("Using Homebrew libFuzzer: $fuzzerLib")
      fuzzLinkerArgs.add(fuzzerLib)
      // Also link Homebrew's libc++ to match the fuzzer library's ABI
      fuzzLinkerArgs.add("-L$homebrewLLVM/lib/c++")
      fuzzLinkerArgs.add("-lc++")
      fuzzLinkerArgs.add("-Wl,-rpath,$homebrewLLVM/lib/c++")
    } else {
      logger.warn("Homebrew libFuzzer not found, falling back to -fsanitize=fuzzer")
      fuzzLinkerArgs.add("-fsanitize=fuzzer,address,undefined")
    }
  } else {
    // Standard libFuzzer linkage for Linux or when Homebrew not available
    fuzzLinkerArgs.add("-fsanitize=fuzzer,address,undefined")
  }
  fuzzLinkerArgs.addAll(listOf("-ldl", "-lpthread", "-lm"))
  if (PlatformUtils.currentPlatform == Platform.LINUX) {
    fuzzLinkerArgs.add("-lrt")
  }

  // Discover fuzz targets
  val fuzzSrcDir = project(":ddprof-lib").file("src/test/fuzz/")
  if (fuzzSrcDir.exists()) {
    fuzzSrcDir.listFiles()?.filter { it.name.endsWith(".cpp") }?.forEach { fuzzFile ->
      val fullName = fuzzFile.nameWithoutExtension
      // Strip "fuzz_" prefix from filename to get the target name
      val fuzzName = if (fullName.startsWith("fuzz_")) fullName.substring(5) else fullName

      // Compile task
      val compileTask = tasks.register<NativeCompileTask>("compileFuzz_$fuzzName") {
        onlyIf {
          hasFuzzer &&
            !project.hasProperty("skip-tests") &&
            !project.hasProperty("skip-native") &&
            !project.hasProperty("skip-fuzz")
        }
        group = "build"
        description = "Compile the fuzz target $fuzzName"

        this.compiler.set(compiler)
        this.compilerArgs.set(fuzzCompilerArgs)
        // Compile main profiler sources (needed for fuzzing the actual code)
        sources.from(
          project(":ddprof-lib").fileTree("src/main/cpp") { include("**/*.cpp") },
          fuzzFile
        )
        includes.from(includeFiles)
        objectFileDir.set(file("${layout.buildDirectory.get()}/obj/fuzz/$fuzzName"))
      }

      // Link task
      val binary = file("${layout.buildDirectory.get()}/bin/fuzz/$fuzzName/$fuzzName")
      val linkTask = tasks.register<NativeLinkExecutableTask>("linkFuzz_$fuzzName") {
        onlyIf {
          hasFuzzer &&
            !project.hasProperty("skip-tests") &&
            !project.hasProperty("skip-native") &&
            !project.hasProperty("skip-fuzz")
        }
        dependsOn(compileTask)
        group = "build"
        description = "Link the fuzz target $fuzzName"

        linker.set(compiler)
        linkerArgs.set(fuzzLinkerArgs)
        objectFiles.from(
          fileTree("${layout.buildDirectory.get()}/obj/fuzz/$fuzzName") { include("*.o") }
        )
        outputFile.set(binary)
      }

      // Create corpus directory for this fuzz target
      val targetCorpusDir = file("$corpusDir/$fuzzName")

      // Execute task
      val executeTask = tasks.register<Exec>("fuzz_$fuzzName") {
        onlyIf {
          hasFuzzer &&
            !project.hasProperty("skip-tests") &&
            !project.hasProperty("skip-native") &&
            !project.hasProperty("skip-fuzz")
        }
        dependsOn(linkTask)
        group = "verification"
        description = "Run the fuzz target $fuzzName for $fuzzDuration seconds"

        doFirst {
          // Ensure crash directory exists
          crashDir.mkdirs()
          // Ensure corpus directory exists (even if empty)
          targetCorpusDir.mkdirs()
        }

        executable = binary.absolutePath
        // libFuzzer arguments:
        // - corpus directory (positional)
        // - max_total_time: stop after N seconds
        // - artifact_prefix: where to save crash files
        // - print_final_stats: show coverage stats at end
        args(
          targetCorpusDir.absolutePath,
          "-max_total_time=$fuzzDuration",
          "-artifact_prefix=${crashDir.absolutePath}/$fuzzName-",
          "-print_final_stats=1"
        )

        inputs.files(binary)
        // Fuzz tasks should run every time
        outputs.upToDateWhen { false }
      }

      fuzzAll.configure { dependsOn(executeTask) }
    }
  }
}

// Task to list available fuzz targets
tasks.register("listFuzzTargets") {
  group = "help"
  description = "List all available fuzz targets"
  doLast {
    val fuzzSrcDir = project(":ddprof-lib").file("src/test/fuzz/")
    if (fuzzSrcDir.exists()) {
      println("Available fuzz targets:")
      fuzzSrcDir.listFiles()?.filter { it.name.endsWith(".cpp") }?.forEach { fuzzFile ->
        val fullName = fuzzFile.nameWithoutExtension
        val fuzzName = if (fullName.startsWith("fuzz_")) fullName.substring(5) else fullName
        println("  - fuzz_$fuzzName")
      }
      println()
      println("Run individual targets with: ./gradlew :ddprof-lib:fuzz:fuzz_<name>")
      println("Run all targets with: ./gradlew :ddprof-lib:fuzz:fuzz")
      println("Configure duration with: -Pfuzz-duration=<seconds> (default: 60)")
    } else {
      println("No fuzz targets found. Create .cpp files in ddprof-lib/src/test/fuzz/")
    }
  }
}
