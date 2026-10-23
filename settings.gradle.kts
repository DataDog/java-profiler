// Copyright 2026, Datadog, Inc.

pluginManagement {
  includeBuild("build-logic")
  val gitlabCi = providers.environmentVariable("GITLAB_CI").orNull == "true"
  val mavenRepositoryProxy = if (gitlabCi) {
    providers.gradleProperty("mavenRepositoryProxy")
      .orElse(providers.environmentVariable("MAVEN_REPOSITORY_PROXY"))
      .orNull?.takeIf { it.isNotBlank() }
  } else {
    providers.gradleProperty("mavenRepositoryProxy").orNull
  }
  val gradlePluginProxy = if (gitlabCi) {
    providers.gradleProperty("gradlePluginProxy")
      .orElse(providers.environmentVariable("GRADLE_PLUGIN_PROXY"))
      .orNull?.takeIf { it.isNotBlank() }
  } else {
    null
  }
  repositories {
    if (mavenRepositoryProxy != null) {
      maven { url = uri(mavenRepositoryProxy) }
    }
    if (gradlePluginProxy != null && gradlePluginProxy != mavenRepositoryProxy) {
      maven { url = uri(gradlePluginProxy) }
    }
    if (gitlabCi && (mavenRepositoryProxy != null || gradlePluginProxy != null)) {
      // The generic Depot mirror rejects HEAD requests used for Gradle cache revalidation.
      exclusiveContent {
        forRepository { gradlePluginPortal() }
        filter {
          includeGroup("org.gradle.kotlin.kotlin-dsl")
          includeGroup("org.gradle.kotlin")
        }
      }
    }
    if (!gitlabCi || (mavenRepositoryProxy == null && gradlePluginProxy == null)) {
      gradlePluginPortal()
      mavenCentral()
    }
  }
}

// Centralized dependency resolution - subprojects should not define their own repositories
dependencyResolutionManagement {
  repositoriesMode.set(RepositoriesMode.PREFER_SETTINGS)
  val gitlabCi = providers.environmentVariable("GITLAB_CI").orNull == "true"
  val mavenRepositoryProxy = if (gitlabCi) {
    providers.gradleProperty("mavenRepositoryProxy")
      .orElse(providers.environmentVariable("MAVEN_REPOSITORY_PROXY"))
      .orNull?.takeIf { it.isNotBlank() }
  } else {
    providers.gradleProperty("mavenRepositoryProxy").orNull
  }
  repositories {
    if (mavenRepositoryProxy != null) {
      maven { url = uri(mavenRepositoryProxy) }
    }
    if (!gitlabCi || mavenRepositoryProxy == null) {
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
