/*
 * Copyright 2026, Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import com.datadoghq.native.model.Platform
import com.datadoghq.native.util.PlatformUtils
import org.gradle.api.publish.maven.tasks.AbstractPublishToMaven
import org.gradle.api.tasks.VerificationTask

plugins {
  java
  `maven-publish`
  signing
  id("com.github.ben-manes.versions") version "0.64.0"
  id("de.undercouch.download") version "5.7.0"
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
      "${project(":malloc-shim").file("src/main/public")}",
    ),
  )
}

// Configure Google Test
gtest {
  testSourceDir.set(layout.projectDirectory.dir("src/test/cpp"))
  mainSourceDir.set(layout.projectDirectory.dir("src/main/cpp"))
  // Without these, buildNativeLibs' onlyIf is false and the helper DSOs are never built.
  nativeLibsSourceDir.set(layout.projectDirectory.dir("src/test/resources/native-libs"))
  nativeLibsOutputDir.set(layout.buildDirectory.dir("test/resources/native-libs"))

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

  failFast.set(true)
}

java {
  sourceCompatibility = JavaVersion.VERSION_1_8
  targetCompatibility = JavaVersion.VERSION_1_8
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
// Uses afterEvaluate to discover configurations dynamically from NativeBuildExtension.
// `coverage` is only packaged with -PenableCoverage: nativeBuild.buildConfigurations.names
// lists every registered config regardless of its `active` flag (the same quirk already
// lets inactive asan/tsan show up here on platforms where they're unsupported). With the
// flag, its jar and consumable configuration are what ddprof-test's testCoverage loads;
// it is still never published (see the publishing block below).
afterEvaluate {
  val packagedConfigNames = nativeBuild.buildConfigurations.names.filter {
    it != "coverage" || project.hasProperty("enableCoverage")
  }
  packagedConfigNames.forEach { name ->
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

      if (!PlatformUtils.isNativeSkipped(project)) {
        dependsOn(copyTask)
      }

      if (name == "debug") {
        manifest {
          attributes("Premain-Class" to "com.datadoghq.profiler.Main")
        }
      }

      from(sourceSets.main.get().output.classesDirs)
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

// Java + C++ coverage report (only meaningful, and only registered, alongside the
// opt-in `coverage` build configuration -- see ConfigurationPresets.configureCoverage).
// The Java half is :ddprof-test:jacocoTestReport (reports/coverage/java); this task
// itself writes the C++ half (reports/coverage/cpp). That needs gcovr
// (`pip install gcovr`), which reads the gcc/clang-compatible .gcno/.gcda files
// directly, so one tool covers both toolchains without a separate lcov+genhtml install.
//
// Two runs feed the C++ report: the gtest binaries (gtestCoverage, objects under
// obj/gtest/coverage) and the Java integration tests (:ddprof-test:testCoverage and
// testSlowCoverage -- the same runs that produce the JaCoCo data, against the
// coverage-instrumented library, objects under obj/main/coverage). gcovr merges both
// into one per-source-file report.
if (project.hasProperty("enableCoverage")) {
  val gtestObjDir = layout.buildDirectory.dir("obj/gtest/coverage")

  // gcov adds to existing .gcda counts, and .gcda files left over from before a
  // recompile no longer match the new .gcno stamps -- so every gtest binary must start
  // from zero. Runs before each gtestCoverage_<test> task rather than in gtestCoverage
  // itself, which is only an aggregate that executes after its test tasks.
  val cleanGtestCoverageData = tasks.register<Delete>("cleanGtestCoverageData") {
    delete(fileTree(gtestObjDir) { include("**/*.gcda") })
  }
  tasks.matching { it.name.startsWith("gtestCoverage_") }.configureEach {
    dependsOn(cleanGtestCoverageData)
  }

  tasks.register("coverageReport") {
    group = "verification"
    description = "Generates the Java (JaCoCo) and C++ (gcovr) coverage reports from gtestCoverage and :ddprof-test:testCoverage/testSlowCoverage (requires gcovr)"
    dependsOn("gtestCoverage", ":ddprof-test:testCoverage", ":ddprof-test:testSlowCoverage", ":ddprof-test:jacocoTestReport")

    val reportDir = layout.buildDirectory.dir("reports/coverage/cpp")
    val libObjDir = layout.buildDirectory.dir("obj/main/coverage")
    val srcRoot = project.file("src/main/cpp")

    doLast {
      // The gcov tool must come from the same toolchain that wrote the .gcno files,
      // so derive it from the compiler (e.g. /usr/bin/g++-13 -> /usr/bin/gcov-13,
      // clang++-17 -> llvm-cov-17 gcov) instead of whatever `gcov` is on PATH.
      val compiler = File(PlatformUtils.findCompiler(project))
      fun siblingOf(tool: String) = compiler.parentFile?.resolve(tool)?.path ?: tool
      val gcovExecutable = when {
        PlatformUtils.currentPlatform == Platform.MACOS -> "xcrun llvm-cov gcov"
        compiler.name.contains("clang") -> siblingOf(compiler.name.replace(Regex("clang(\\+\\+)?"), "llvm-cov")) + " gcov"
        else -> siblingOf(compiler.name.replace(Regex("[gc]\\+\\+"), "gcov"))
      }

      val outDir = reportDir.get().asFile.also { it.mkdirs() }
      val cmd = listOf(
        "gcovr",
        "--root", srcRoot.absolutePath,
        "--gcov-executable", gcovExecutable,
        "--html", "--html-details",
        "-o", "${outDir.absolutePath}/index.html",
        "--print-summary",
        // Safety net only: -fprofile-update=atomic (see configureCoverage) should keep
        // counters consistent, but a stray negative count must not discard a
        // ~20-minute run -- warn and ignore it instead of failing.
        "--gcov-ignore-parse-errors=negative_hits.warn_once_per_file",
        // gcovr flags any count above 2^32 as a GCC-68080 artifact, but the 64-bit atomic
        // counters legitimately pass that on hot paths (e.g. threadLocal.h's isKeyValid()
        // hit ~4.4e9 over testCoverage + testSlowCoverage). Real counts stay far below
        // 1e15 (1e9 hits/s for ~11 days), while wrapped/garbage counts land near 2^64.
        "--gcov-suspicious-hits-threshold=1000000000000000",
        gtestObjDir.get().asFile.absolutePath,
        libObjDir.get().asFile.absolutePath,
      )
      project.logger.lifecycle("Running: ${cmd.joinToString(" ")}")
      val process = ProcessBuilder(cmd)
        .directory(project.projectDir)
        .redirectErrorStream(true)
        .start()
      val output = process.inputStream.bufferedReader().readText()
      val exitCode = process.waitFor()
      println(output)
      if (exitCode != 0) {
        throw GradleException("gcovr failed (exit $exitCode) -- install it with 'pip install gcovr' if missing")
      }
      project.logger.lifecycle("C++ coverage report written to file://${outDir.absolutePath}/index.html")
      val javaReport = outDir.resolveSibling("java/html/index.html")
      if (javaReport.isFile) {
        project.logger.lifecycle("Java coverage report written to file://${javaReport.absolutePath}")
      } else {
        // jacocoTestReport is skipped when no test task wrote JaCoCo execution data.
        project.logger.warn("No Java coverage report: no JaCoCo execution data was recorded")
      }
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
  archiveBaseName.set(libraryName)
  archiveClassifier.set("sources")
  archiveVersion.set(componentVersion)
}

// Javadoc configuration
tasks.withType<Javadoc>().configureEach {
  dependsOn(copyExternalLibs)
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

      // Add artifacts from each build configuration (coverage excluded -- see the
      // packagedConfigNames comment above)
      afterEvaluate {
        nativeBuild.buildConfigurations.names.filterNot { it == "coverage" }.forEach { name ->
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
