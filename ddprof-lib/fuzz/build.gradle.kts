/*
 * Gradle build file for libFuzzer-based fuzz testing.
 * This module compiles and runs fuzz targets against the profiler's C++ code
 * to discover bugs through automated input generation.
 */

plugins {
  base
  id("com.datadoghq.fuzz-targets")
}

fuzzTargets {
  // Source directory containing fuzz target files (fuzz_*.cpp)
  fuzzSourceDir.set(project(":ddprof-lib").file("src/test/fuzz"))

  // Seed corpus directory for each target (subdirectories named by target)
  corpusDir.set(project(":ddprof-lib").file("src/test/fuzz/corpus"))

  // Main profiler sources to compile with fuzz targets
  profilerSourceDir.set(project(":ddprof-lib").file("src/main/cpp"))

  // Additional include directories
  additionalIncludes.set(
    listOf(
      project(":malloc-shim").file("src/main/public").absolutePath
    )
  )
}
