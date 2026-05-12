pluginManagement {
  includeBuild("build-logic")
  val mavenRepositoryProxy = providers.gradleProperty("mavenRepositoryProxy").orNull
  repositories {
    if (mavenRepositoryProxy != null) {
      maven { url = uri(mavenRepositoryProxy) }
    }
    gradlePluginPortal()
    mavenCentral()
  }
}

// Centralized dependency resolution - subprojects should not define their own repositories
dependencyResolutionManagement {
  repositoriesMode.set(RepositoriesMode.PREFER_SETTINGS)
  val mavenRepositoryProxy = providers.gradleProperty("mavenRepositoryProxy").orNull
  repositories {
    if (mavenRepositoryProxy != null) {
      maven { url = uri(mavenRepositoryProxy) }
    }
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
