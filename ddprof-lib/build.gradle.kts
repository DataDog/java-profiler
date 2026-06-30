import com.datadoghq.native.model.Platform
import com.datadoghq.native.tasks.NativeLinkExecutableTask
import com.datadoghq.native.tasks.NativeLinkTask
import com.datadoghq.native.util.PlatformUtils
import org.gradle.api.publish.maven.tasks.AbstractPublishToMaven
import org.gradle.api.tasks.VerificationTask

plugins {
  java
  `maven-publish`
  signing
  id("com.github.ben-manes.versions") version "0.54.0"
  id("de.undercouch.download") version "5.7.0"
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
  cppSourceDirs.set(
    listOf(
      "src/main/cpp",
      "src/main/cpp/support",
      "src/main/cpp/support/hotspot",
      "src/main/cpp/support/j9",
      "src/main/cpp/support/zing",
    ),
  )
  supportCppSourceDirs.set(
    listOf(
      "src/main/cpp/support",
      "src/main/cpp/support/hotspot",
      "src/main/cpp/support/j9",
      "src/main/cpp/support/zing",
    ),
  )
  includeDirectories.set(
    listOf(
      "src/main/cpp",
      "src/main/cpp/support",
      "${project(":malloc-shim").file("src/main/public")}",
    ),
  )
}

// Configure Google Test
gtest {
  testSourceDir.set(layout.projectDirectory.dir("src/test/cpp"))
  mainSourceDir.set(layout.projectDirectory.dir("src/main/cpp"))

  // Include paths for compilation
  val javaHome = PlatformUtils.javaHome()
  val platformInclude = when (PlatformUtils.currentPlatform) {
    Platform.LINUX -> "linux"
    Platform.MACOS -> "darwin"
  }

  includes.from(
    "src/main/cpp",
    "src/main/cpp/support",
    "$javaHome/include",
    "$javaHome/include/$platformInclude",
    project(":malloc-shim").file("src/main/public"),
  )

  failFast.set(true)
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
      minToolchainVersion.set(11) // Compile Java 9 code with JDK 11+
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

// Gradle 9 requires explicit dependency: compileJava9Java uses mainSourceSet.output
// which includes the copyExternalLibs destination directory
afterEvaluate {
  tasks.named("compileJava9Java") {
    dependsOn(copyExternalLibs)
  }
}

// Wire split-mode link tasks: SONAME for the support library, ABI symbol list.
// Runs after NativeBuildPlugin's afterEvaluate has registered the tasks.
afterEvaluate {
  nativeBuild.buildConfigurations.names.forEach { name ->
    val cap = name.replaceFirstChar { it.uppercase() }
    tasks.findByName("linkSupport$cap")?.let {
      (it as NativeLinkTask).apply {
        exportSymbolsFile.set(layout.projectDirectory.file("src/main/cpp/support/vmstructs-abi.symbols"))
        soname.set("libJavaSupport.so")
        // macOS requires explicit opt-in for undefined symbols (resolved at
        // runtime by libjavaProfiler.dylib which loads this library).
        if (PlatformUtils.currentPlatform == Platform.MACOS) {
          linkerArgs.addAll("-undefined", "dynamic_lookup")
        }
      }
    }
  }
}

// Support-only gtest tests link against libJavaSupport.so only.
// These test files depend exclusively on support-side code (dwarf, sframe, safeAccess, libraries/codeCache).
// Only wired in split mode — in monolithic mode there is no separate libJavaSupport.so.
afterEvaluate {
  if (nativeBuild.monolithicBuild.get() || nativeBuild.supportCppSourceDirs.get().isEmpty()) return@afterEvaluate
  val supportOnlyTests = setOf("dwarf_ut", "sframe_ut", "safefetch_ut", "libraries_ut")
  val supportLibName = if (PlatformUtils.currentPlatform == Platform.MACOS) "libJavaSupport.dylib" else "libJavaSupport.so"
  nativeBuild.buildConfigurations.names.forEach { configName ->
    val cap = configName.replaceFirstChar { it.uppercase() }
    val libDir = nativeBuild.librarySourceDir(configName).get().asFile.absolutePath
    supportOnlyTests.forEach { testName ->
      tasks.findByName("linkGtest${cap}_$testName")?.let {
        (it as NativeLinkExecutableTask).apply {
          libPath(libDir)
          lib("JavaSupport")
          when (PlatformUtils.currentPlatform) {
            Platform.LINUX -> runtimePath("\$ORIGIN")
            Platform.MACOS -> linkerArgs.addAll("-rpath", "@loader_path")
          }
        }
        // Copy libJavaSupport next to the test binary so $ORIGIN / @loader_path resolves at runtime.
        val binaryDir = layout.buildDirectory.dir("bin/gtest/${configName}_$testName")
        val copyTask = tasks.register("copySupportLibFor${cap}_$testName", Copy::class) {
          from(libDir) { include(supportLibName) }
          into(binaryDir)
          dependsOn("linkSupport$cap")
        }
        tasks.findByName("gtest${cap}_$testName")?.dependsOn(copyTask)
      }
    }
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

      // Depend on whichever link tasks exist for this config (monolithic or split)
      val supportLinkTask = "linkSupport$capitalizedName"
      val profilerLinkTask = "linkProfiler$capitalizedName"
      val monoLinkTask = "link$capitalizedName"
      if (tasks.names.contains(supportLinkTask)) dependsOn(supportLinkTask)
      if (tasks.names.contains(profilerLinkTask)) dependsOn(profilerLinkTask)
      if (tasks.names.contains(monoLinkTask)) dependsOn(monoLinkTask)
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
tasks.withType<Javadoc>().configureEach {
  dependsOn(copyExternalLibs)
  // Allow javadoc to access internal sun.nio.ch package used by BufferWriter8
  (options as StandardJavadocDocletOptions).addStringOption("-add-exports", "java.base/sun.nio.ch=ALL-UNNAMED")
}

// Javadoc JAR
val javadocJar by tasks.registering(Jar::class) {
  dependsOn(tasks.javadoc)
  archiveBaseName.set(libraryName)
  archiveClassifier.set("javadoc")
  archiveVersion.set(componentVersion)
  from(
    tasks.javadoc.map {
      it.destinationDir ?: throw GradleException("Javadoc task destinationDir is null - task may not have been configured properly")
    },
  )
}

// Publishing configuration
val isGitlabCI = System.getenv("GITLAB_CI") != null
val isCI = System.getenv("CI") != null

publishing {
  publications {
    create<MavenPublication>("assembled") {
      groupId = "com.datadoghq"
      artifactId = "ddprof"

      // Add artifacts from each build configuration
      afterEvaluate {
        nativeBuild.buildConfigurations.names.forEach { name ->
          val capitalizedName = name.replaceFirstChar { it.uppercase() }
          artifact(tasks.named("assemble${capitalizedName}Jar"))
        }
      }
      artifact(sourcesJar)
      artifact(javadocJar)

      pom {
        name.set(project.name)
        description.set("${project.description} ($componentVersion)")
        packaging = "jar"
        url.set("https://github.com/datadog/java-profiler")

        licenses {
          license {
            name.set("The Apache Software License, Version 2.0")
            url.set("http://www.apache.org/licenses/LICENSE-2.0.txt")
            distribution.set("repo")
          }
        }

        scm {
          connection.set("scm:https://datadog@github.com/datadog/java-profiler")
          developerConnection.set("scm:git@github.com:datadog/java-profiler")
          url.set("https://github.com/datadog/java-profiler")
        }

        developers {
          developer {
            id.set("datadog")
            name.set("Datadog")
          }
        }
      }
    }
  }
}

signing {
  useInMemoryPgpKeys(System.getenv("GPG_PRIVATE_KEY"), System.getenv("GPG_PASSWORD"))
  sign(publishing.publications["assembled"])
}

tasks.withType<Sign>().configureEach {
  onlyIf {
    isGitlabCI || (System.getenv("GPG_PRIVATE_KEY") != null && System.getenv("GPG_PASSWORD") != null)
  }
}

// Publication assertions
gradle.taskGraph.whenReady {
  if (hasTask(":ddprof-lib:publish") || hasTask(":publishToSonatype")) {
    check(project.findProperty("removeJarVersionNumbers") != true) {
      "Cannot publish with removeJarVersionNumbers=true"
    }
    if (hasTask(":publishToSonatype")) {
      checkNotNull(System.getenv("SONATYPE_USERNAME")) { "SONATYPE_USERNAME must be set" }
      checkNotNull(System.getenv("SONATYPE_PASSWORD")) { "SONATYPE_PASSWORD must be set" }
      if (isCI) {
        checkNotNull(System.getenv("GPG_PRIVATE_KEY")) { "GPG_PRIVATE_KEY must be set in CI" }
        checkNotNull(System.getenv("GPG_PASSWORD")) { "GPG_PASSWORD must be set in CI" }
      }
    }
  }
}

// Verify project has description (required for published projects)
afterEvaluate {
  requireNotNull(description) { "Project ${project.path} is published, must have a description" }
}

// Ensure published artifacts depend on release JAR
// Note: assembleReleaseJar is registered in afterEvaluate, so use matching instead of named
tasks.withType<AbstractPublishToMaven>().configureEach {
  if (name.contains("AssembledPublication")) {
    dependsOn(tasks.matching { it.name == "assembleReleaseJar" })
  }
  rootProject.subprojects.forEach { subproject ->
    mustRunAfter(subproject.tasks.matching { it is VerificationTask })
  }
}
