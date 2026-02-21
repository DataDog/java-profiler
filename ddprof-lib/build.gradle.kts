import com.datadoghq.native.model.Platform
import com.datadoghq.native.util.PlatformUtils
import org.gradle.api.publish.maven.tasks.AbstractPublishToMaven
import org.gradle.api.tasks.VerificationTask

plugins {
  java
  `maven-publish`
  signing
  id("com.github.ben-manes.versions") version "0.53.0"
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
  cppSourceDirs.set(listOf("src/main/cpp"))
  includeDirectories.set(
    listOf(
      "src/main/cpp",
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
    "$javaHome/include",
    "$javaHome/include/$platformInclude",
    project(":malloc-shim").file("src/main/public"),
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
tasks.withType<Javadoc>().configureEach {
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
