// Copyright 2026, Datadog, Inc

pluginManagement {
  includeBuild("build-logic")
}

rootProject.name = "java-profiler"

include(":ddprof-lib")
include(":ddprof-lib:fuzz")
include(":ddprof-lib:benchmarks")
include(":ddprof-test-tracer")
include(":ddprof-test")
include(":malloc-shim")
include(":ddprof-stresstest")
