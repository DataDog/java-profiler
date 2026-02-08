// Copyright 2026, Datadog, Inc

pluginManagement {
  includeBuild("build-logic")
}

// Centralized dependency resolution - subprojects should not define their own repositories
dependencyResolutionManagement {
  repositoriesMode.set(RepositoriesMode.PREFER_SETTINGS)
  repositories {
    mavenCentral()
    gradlePluginPortal()
  }
}

rootProject.name = "java-profiler"

include(":ddprof-lib")
include(":ddprof-lib:fuzz")
include(":ddprof-lib:benchmarks")
include(":ddprof-test-tracer")
include(":ddprof-test")
include(":ddprof-test-native")
include(":malloc-shim")
include(":ddprof-stresstest")
