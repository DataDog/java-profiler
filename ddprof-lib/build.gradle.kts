// Copyright 2026, Datadog, Inc

plugins {
  java
  `maven-publish`
  signing
  id("com.github.ben-manes.versions") version "0.27.0"
  id("de.undercouch.download") version "4.1.1"
  id("com.datadoghq.native-build")
  id("com.datadoghq.gtest")
  id("com.datadoghq.scanbuild")
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

// Java configuration
java {
  sourceCompatibility = JavaVersion.VERSION_1_8
  targetCompatibility = JavaVersion.VERSION_1_8
}

// Configure Java 9+ source set for multi-release JAR
sourceSets {
  val java9 by creating {
    java {
      srcDirs("src/main/java9")
    }
  }
}

val current = JavaVersion.current().majorVersion.toInt()
val requested = if (current >= 11) current else 11

// Configure Java 9 compilation with Java 11 toolchain
tasks.named<JavaCompile>("compileJava9Java") {
  javaCompiler.set(
    javaToolchains.compilerFor {
      languageVersion.set(JavaLanguageVersion.of(requested))
    }
  )
  options.release.set(9)

  // Add main source set output to classpath
  classpath = sourceSets.main.get().output + configurations.compileClasspath.get()
  dependsOn(tasks.named("compileJava"))
}

// Test configuration
tasks.test {
  onlyIf {
    !project.hasProperty("skip-tests")
  }
  useJUnitPlatform()
}

// Utility functions for library paths
fun libraryTargetBase(type: String): String {
  return "$projectDir/build/native/$type"
}

fun libraryTargetPath(type: String): String {
  val platform = com.datadoghq.native.util.PlatformUtils.currentPlatform
  val arch = com.datadoghq.native.util.PlatformUtils.currentArchitecture
  val isMusl = com.datadoghq.native.util.PlatformUtils.isMusl()
  val muslSuffix = if (isMusl) "-musl" else ""
  return "${libraryTargetBase(type)}/META-INF/native-libs/$platform-$arch$muslSuffix"
}

fun librarySourcePath(type: String, qualifier: String = ""): String {
  val platform = com.datadoghq.native.util.PlatformUtils.currentPlatform
  val arch = com.datadoghq.native.util.PlatformUtils.currentArchitecture
  val ext = com.datadoghq.native.util.PlatformUtils.sharedLibExtension()
  // New plugin uses build/lib/main/{config}/{os}/{arch}/ structure
  val qualifierPath = if (qualifier.isNotEmpty()) "/$qualifier" else ""
  return "$projectDir/build/lib/main/$type/$platform/$arch$qualifierPath/libjavaProfiler.$ext"
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

// Create JAR tasks for each build configuration
val buildConfigNames = listOf("release", "debug", "asan", "tsan", "fuzzer")
buildConfigNames.forEach { name ->
  val copyTask = tasks.register("copy${name.replaceFirstChar { it.uppercase() }}Libs", Copy::class) {
    from(file(librarySourcePath(name, "")).parent) {
      // Exclude debug symbols from production JAR
      exclude("debug/**", "*.debug", "*.dSYM/**")
    }
    into(file(libraryTargetPath(name)))

    // Ensure library is built before copying
    val linkTask = tasks.findByName("link${name.replaceFirstChar { it.uppercase() }}")
    if (linkTask != null) {
      dependsOn(linkTask)
    }
  }

  val assembleJarTask = tasks.register("assemble${name.replaceFirstChar { it.uppercase() }}Jar", Jar::class) {
    group = "build"
    description = "Assemble the $name build of the library"
    dependsOn(copyExternalLibs)
    dependsOn(tasks.named("compileJava9Java"))

    if (!project.hasProperty("skip-native")) {
      dependsOn(copyTask)
    }

    if (name == "debug") {
      manifest {
        attributes("Premain-Class" to "com.datadoghq.profiler.Main")
      }
    }

    from(sourceSets.main.get().output.classesDirs)
    from(sourceSets["java9"].output.classesDirs)
    from(files(libraryTargetBase(name))) {
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

// Add runBenchmarks task
tasks.register("runBenchmarks") {
  dependsOn(":ddprof-lib:benchmarks:runBenchmark")
  group = "verification"
  description = "Run all benchmarks"
}

// Standard JAR task
tasks.jar {
  dependsOn(copyExternalLibs)
  dependsOn(tasks.named("compileJava9Java"))
}

// Source JAR
val sourcesJar by tasks.registering(Jar::class) {
  from(sourceSets.main.get().allJava)
  from(sourceSets["java9"].allJava)
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
// TODO: Add publishing, signing, etc.
