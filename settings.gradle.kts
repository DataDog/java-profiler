// Copyright 2026, Datadog, Inc.

pluginManagement {
  includeBuild("build-logic")
  val mavenRepositoryProxy = providers.gradleProperty("mavenRepositoryProxy")
    .orElse(providers.environmentVariable("MAVEN_REPOSITORY_PROXY"))
    .orNull?.takeIf { it.isNotBlank() }
  val gradlePluginProxy = providers.gradleProperty("gradlePluginProxy")
    .orElse(providers.environmentVariable("GRADLE_PLUGIN_PROXY"))
    .orNull?.takeIf { it.isNotBlank() }
  repositories {
    if (mavenRepositoryProxy != null) {
      maven { url = uri(mavenRepositoryProxy) }
    }
    if (gradlePluginProxy != null && gradlePluginProxy != mavenRepositoryProxy) {
      maven { url = uri(gradlePluginProxy) }
    }
    if (mavenRepositoryProxy == null && gradlePluginProxy == null) {
      gradlePluginPortal()
      mavenCentral()
    }
  }
}

// Centralized dependency resolution - subprojects should not define their own repositories
dependencyResolutionManagement {
  repositoriesMode.set(RepositoriesMode.PREFER_SETTINGS)
  val mavenRepositoryProxy = providers.gradleProperty("mavenRepositoryProxy")
    .orElse(providers.environmentVariable("MAVEN_REPOSITORY_PROXY"))
    .orNull?.takeIf { it.isNotBlank() }
  repositories {
    if (mavenRepositoryProxy != null) {
      maven { url = uri(mavenRepositoryProxy) }
    } else {
      mavenCentral()
      gradlePluginPortal()
    }
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
