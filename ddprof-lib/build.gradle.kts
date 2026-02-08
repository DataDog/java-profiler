plugins {
  java
  `maven-publish`
  signing
  id("com.github.ben-manes.versions") version "0.27.0"
  id("de.undercouch.download") version "4.1.1"
  id("com.datadoghq.native-build")
  id("com.datadoghq.gtest")
  id("com.datadoghq.scanbuild")
  id("com.datadoghq.versioned-sources")
}

val libraryName = "ddprof"
description = "Datadog Java Profiler Library"

val componentVersion = findProperty("ddprof_version") as? String ?: version.toString()

// Configure native build with the new plugin
nativeBuild {
  version.set(componentVersion)
  cppSourceDirs.set(listOf("src/main/cpp"))
  includeDirectories.set(
    listOf(
      "src/main/cpp",
      "${project(":malloc-shim").file("src/main/public")}"
    )
  )
}

// Configure Google Test
gtest {
  testSourceDir.set(layout.projectDirectory.dir("src/test/cpp"))
  mainSourceDir.set(layout.projectDirectory.dir("src/main/cpp"))

  // Include paths for compilation
  val javaHome = com.datadoghq.native.util.PlatformUtils.javaHome()
  val platformInclude = when (com.datadoghq.native.util.PlatformUtils.currentPlatform) {
    com.datadoghq.native.model.Platform.LINUX -> "linux"
    com.datadoghq.native.model.Platform.MACOS -> "darwin"
  }

  includes.from(
    "src/main/cpp",
    "$javaHome/include",
    "$javaHome/include/$platformInclude",
    project(":malloc-shim").file("src/main/public")
  )
}

// Java configuration - using sourceCompatibility (not --release 8)
// because BufferWriter8 needs access to internal sun.nio.ch package
java {
  sourceCompatibility = JavaVersion.VERSION_1_8
  targetCompatibility = JavaVersion.VERSION_1_8
}

// Configure versioned sources for runtime version-specific implementations
versionedSources {
  versions {
    register("java9") {
      release.set(9)
      minToolchainVersion.set(11)  // Compile Java 9 code with JDK 11+
    }
  }
}

// Test configuration
tasks.test {
  onlyIf {
    !project.hasProperty("skip-tests")
  }
  useJUnitPlatform()
}

// Copy external libs task
val copyExternalLibs by tasks.registering(Copy::class) {
  if (project.hasProperty("with-libs")) {
    from(project.property("with-libs") as String) {
      include("**/*.so", "**/*.dylib", "**/*.debug", "**/*.dSYM/**")
    }
    into("$projectDir/build/classes/java/main/META-INF/native-libs")
  }
}

// Create JAR tasks for each build configuration using nativeBuild extension utilities
// Uses afterEvaluate to discover configurations dynamically from NativeBuildExtension
afterEvaluate {
  nativeBuild.buildConfigurations.names.forEach { name ->
    val capitalizedName = name.replaceFirstChar { it.uppercase() }

    val copyTask = tasks.register("copy${capitalizedName}Libs", Copy::class) {
      from(nativeBuild.librarySourceDir(name)) {
        // Exclude debug symbols from production JAR
        exclude("debug/**", "*.debug", "*.dSYM/**")
      }
      into(nativeBuild.libraryTargetDir(name))

      // Ensure library is built before copying (link task created by NativeBuildPlugin)
      val linkTaskName = "link$capitalizedName"
      if (tasks.names.contains(linkTaskName)) {
        dependsOn(linkTaskName)
      }
    }

    val assembleJarTask = tasks.register("assemble${capitalizedName}Jar", Jar::class) {
      group = "build"
      description = "Assemble the $name build of the library"
      dependsOn(copyExternalLibs)

      if (!project.hasProperty("skip-native")) {
        dependsOn(copyTask)
      }

      if (name == "debug") {
        manifest {
          attributes("Premain-Class" to "com.datadoghq.profiler.Main")
        }
      }

      from(sourceSets.main.get().output.classesDirs)
      versionedSources.configureJar(this)
      from(nativeBuild.libraryTargetBase(name)) {
        include("**/*")
        // Exclude debug symbols from production JAR
        exclude("**/debug/**", "**/*.debug", "**/*.dSYM/**")
      }
      archiveBaseName.set(libraryName)
      archiveClassifier.set(if (name == "release") "" else name)
      archiveVersion.set(componentVersion)
    }

    // Create consumable configuration for inter-project dependencies
    // This allows other projects to depend on specific build configurations
    configurations.create(name) {
      isCanBeConsumed = true
      isCanBeResolved = false
      outgoing.artifact(assembleJarTask)
    }
  }
}

// Add runBenchmarks task
tasks.register("runBenchmarks") {
  dependsOn(":ddprof-lib:benchmarks:runBenchmark")
  group = "verification"
  description = "Run all benchmarks"
}

// Standard JAR task
tasks.jar {
  dependsOn(copyExternalLibs)
}

// Source JAR
val sourcesJar by tasks.registering(Jar::class) {
  from(sourceSets.main.get().allJava)
  versionedSources.configureSourceJar(this)
  archiveBaseName.set(libraryName)
  archiveClassifier.set("sources")
  archiveVersion.set(componentVersion)
}

// Javadoc configuration
tasks.withType<Javadoc> {
  // Allow javadoc to access internal sun.nio.ch package used by BufferWriter8
  (options as StandardJavadocDocletOptions).addStringOption("-add-exports", "java.base/sun.nio.ch=ALL-UNNAMED")
}

// Javadoc JAR
val javadocJar by tasks.registering(Jar::class) {
  dependsOn(tasks.javadoc)
  archiveBaseName.set(libraryName)
  archiveClassifier.set("javadoc")
  archiveVersion.set(componentVersion)
  from(tasks.javadoc.get().destinationDir)
}

// Publishing configuration will be added later
