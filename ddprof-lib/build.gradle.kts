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
  id("com.github.ben-manes.versions") version "0.66.0"
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

// referenceChainJfrRoundtrip_ut writes a .jfr that :ddprof-test's ReferenceChainJfrParserTest
// reads back. Both sides get the path from this env var (set here and in ddprof-test's
// build.gradle.kts). The path is scoped per build configuration (derived from the gtest task
// name, which encodes it) so a multi-configuration invocation cannot delete or overwrite
// another configuration's recording, and the producer deletes the file before it runs, so
// the consumer never parses a recording left behind by an older binary.
val roundtripSuiteSuffix = "_referenceChainJfrRoundtrip_ut"
val roundtripProducers = tasks.withType<Exec>().matching {
  it.name.startsWith("gtest") && it.name.endsWith(roundtripSuiteSuffix)
}
// The gtest plugin registers one producer per build configuration; zero matches can only
// mean the suite id or the gtest task naming changed. Fail the build instead of letting
// ReferenceChainJfrParserTest silently degrade to a skip.
gradle.projectsEvaluated {
  check(roundtripProducers.isNotEmpty()) {
    "No gtest task matching 'gtest*$roundtripSuiteSuffix' was registered - the " +
      "reference-chain JFR roundtrip wiring is stale (suite renamed?)"
  }
}
roundtripProducers.configureEach {
  val config = name.removePrefix("gtest").removeSuffix(roundtripSuiteSuffix).lowercase()
  val jfr = rootProject.layout.buildDirectory
    .file("tmp/reference-chain-roundtrip/$config/datadog_reference_chain_roundtrip.jfr")
    .get()
    .asFile
  environment("DDPROF_REFERENCE_CHAIN_ROUNDTRIP_JFR", jfr.absolutePath)
  doFirst {
    jfr.parentFile.mkdirs()
    jfr.delete()
  }
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
// Every publishable config is packaged, even an inactive one (inactive asan/tsan on
// platforms where they're unsupported still get a jar). An unpublishable config (e.g.
// `coverage`) is packaged only while active: its jar and consumable configuration are
// what ddprof-test's testCoverage loads, and it is never published (see the publishing
// block below).
afterEvaluate {
  val packagedConfigNames = nativeBuild.buildConfigurations
    .filter { it.publishable.get() || it.active.get() }
    .map { it.name }
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

  // The compiler's `--version` output, or "" if it cannot be run.
  fun compilerBanner(compilerPath: String): String = try {
    val process = ProcessBuilder(compilerPath, "--version").redirectErrorStream(true).start()
    val output = process.inputStream.bufferedReader().use { it.readText() }
    process.waitFor()
    output
  } catch (e: java.io.IOException) {
    ""
  }

  // The gcov tool must come from the same toolchain that wrote the .gcno files: GCC's
  // gcov cannot read clang's .gcno format. Whether the compiler is clang is decided from
  // its `--version` banner, never from its name -- /usr/bin/c++ may be clang through
  // update-alternatives, and macOS's /usr/bin/g++ is an Apple clang shim. The tool is
  // then derived from the compiler's path (e.g. /usr/bin/g++-13 -> /usr/bin/gcov-13,
  // clang++-17 -> llvm-cov-17 gcov) instead of whatever `gcov` is on PATH.
  fun gcovCommand(compilerPath: String): List<String> {
    val banner = compilerBanner(compilerPath)
    if (banner.contains("Apple clang")) {
      return listOf("xcrun", "llvm-cov", "gcov")
    }
    val compiler = File(compilerPath)
    fun siblingOf(file: File, tool: String) = file.parentFile?.resolve(tool)?.path ?: tool
    if (!banner.contains("clang version")) {
      return listOf(siblingOf(compiler, compiler.name.replace(Regex("[gc]\\+\\+"), "gcov")))
    }
    val clangNamePattern = Regex("clang(\\+\\+)?")
    if (clangNamePattern.containsMatchIn(compiler.name)) {
      return listOf(siblingOf(compiler, compiler.name.replace(clangNamePattern, "llvm-cov")), "gcov")
    }
    // A clang under another name (c++ via update-alternatives) symlinks to the real clang
    // binary (e.g. /usr/lib/llvm-17/bin/clang); that directory holds the matching
    // llvm-cov when the llvm-<N> package is installed. Otherwise, and for wrappers that
    // do not resolve to clang (ccache), fall back to llvm-cov on PATH.
    val llvmCov = compiler.takeIf { it.isAbsolute && it.exists() }?.canonicalFile
      ?.takeIf { clangNamePattern.containsMatchIn(it.name) }
      ?.let { File(siblingOf(it, it.name.replace(clangNamePattern, "llvm-cov"))) }
      ?.takeIf { it.canExecute() }?.path ?: "llvm-cov"
    return listOf(llvmCov, "gcov")
  }

  // gcovr flags coverageReport depends on (see its command line below); 8.3 is the
  // first gcovr that accepts all of them.
  val requiredGcovrFlags = listOf("--gcov-ignore-parse-errors", "negative_hits.warn_once_per_file", "--gcov-suspicious-hits-threshold")

  // Fails fast -- before ~30 minutes of instrumented builds and test runs -- when a tool
  // the coverage run needs is missing, reporting every problem at once with how to fix it.
  // Every coverage task depends on it (below, and :ddprof-test's coverage test tasks and
  // cleanLibCoverageData).
  val checkCoverageTools = tasks.register("checkCoverageTools") {
    group = "verification"
    description = "Checks that the tools needed for the coverage build and report are installed"
    val reportRequested = provider { gradle.taskGraph.hasTask("${project.path}:coverageReport") }

    doLast {
      // Fetched here, not at configuration time: temporaryDir (re)creates the directory,
      // which a `clean` in the same invocation would otherwise have deleted by now.
      val probeDir = temporaryDir
      val isMacos = PlatformUtils.currentPlatform == Platform.MACOS
      val isMusl = PlatformUtils.isMusl()
      fun hint(musl: String, glibc: String, macos: String) = when {
        isMacos -> macos
        isMusl -> musl
        else -> glibc
      }

      // Runs cmd and returns (exit code, combined output), or null if it cannot be started.
      fun run(cmd: List<String>): Pair<Int, String>? = try {
        val process = ProcessBuilder(cmd).directory(probeDir).redirectErrorStream(true).start()
        val output = process.inputStream.bufferedReader().use { it.readText() }
        process.waitFor() to output.trim()
      } catch (e: java.io.IOException) {
        null
      }
      // The first line carrying a version number, which isn't always the first line
      // (llvm-cov starts with "LLVM (http://llvm.org/):").
      val versionNumber = Regex("\\d+\\.\\d+")
      fun firstLine(output: String) = output.lineSequence().map { it.trim() }.filter { it.isNotEmpty() }
        .let { lines -> lines.firstOrNull { versionNumber.containsMatchIn(it) } ?: lines.firstOrNull() }.orEmpty()

      val found = mutableListOf<String>()
      val problems = mutableListOf<String>()

      // 1. C++ compiler able to build *and link* --coverage code (clang needs its profile
      //    runtime, gcc its libgcov -- both shipped separately on some distros).
      val compiler = try {
        PlatformUtils.findCompiler(project)
      } catch (e: GradleException) {
        problems += "C++ compiler: ${e.message}"
        null
      }
      if (compiler != null) {
        val src = probeDir.resolve("probe.cpp").apply { writeText("int main() { return 0; }\n") }
        val result = run(listOf(compiler, "--coverage", "-fprofile-update=atomic", src.path, "-o", probeDir.resolve("probe").path))
        if (result != null && result.first == 0) {
          found += "compiler: $compiler (links with --coverage)"
        } else {
          problems += "C++ compiler '$compiler' cannot build with --coverage -fprofile-update=atomic " +
            "(needed for the instrumented library and gtests):\n" +
            (result?.second ?: "could not run '$compiler'").prependIndent("      ") + "\n" +
            "    Install the coverage runtime: " +
            hint(
              musl = "'apk add compiler-rt' (clang) or 'apk add g++' (gcc)",
              glibc = "'apt install libclang-rt-dev' or the libclang-rt-<N>-dev matching your clang (clang), or libgcc-<N>-dev (gcc)",
              macos = "Xcode command line tools: 'xcode-select --install'",
            ) + ", or pick another compiler with -Pnative.forceCompiler=<path>"
        }

        // 2. gcov tool matching that compiler (used by gcovr to read the .gcda files).
        val gcov = gcovCommand(compiler)
        val gcovResult = run(gcov + "--version")
        if (gcovResult != null && gcovResult.first == 0) {
          found += "gcov: ${gcov.joinToString(" ")} (${firstLine(gcovResult.second)})"
        } else {
          problems += "gcov tool '${gcov.joinToString(" ")}' (must match compiler '$compiler') " +
            (if (gcovResult == null) "not found" else "failed: ${firstLine(gcovResult.second)}") + "\n" +
            "    Install it: " +
            hint(
              musl = "'apk add llvm' (clang) or 'apk add gcc' (gcc)",
              glibc = "'apt install llvm' or the llvm-<N> matching your clang (clang), or gcc-<N> (gcc)",
              macos = "Xcode command line tools: 'xcode-select --install'",
            )
        }
      }

      // 3. Google Test: without it the gtest tasks are skipped with only a warning, and
      //    the C++ report silently loses the gtest half of its coverage.
      if (PlatformUtils.isGtestAvailable()) {
        found += "gtest: ${PlatformUtils.gtestLocations.first { File(it).exists() }}"
      } else {
        problems += "Google Test not found (looked in ${PlatformUtils.gtestLocations.joinToString()}); " +
          "gtestCoverage would be skipped\n" +
          "    Install it: " +
          hint(musl = "'apk add gtest-dev gmock'", glibc = "'apt install libgtest-dev libgmock-dev'", macos = "'brew install googletest'")
      }

      // 4. make: buildNativeLibs builds the gtests' helper libraries with it (Linux only).
      if (!isMacos) {
        val makeResult = run(listOf("make", "--version"))
        if (makeResult != null && makeResult.first == 0) {
          found += "make: ${firstLine(makeResult.second)}"
        } else {
          problems += "make not found (buildNativeLibs needs it for the gtests' native libraries)\n" +
            "    Install it: " + hint(musl = "'apk add make'", glibc = "'apt install make'", macos = "")
        }
      }

      // 5. gcovr, only when the report is actually requested (gtestCoverage/testCoverage
      //    alone just produce .gcda files).
      if (reportRequested.get()) {
        val gcovrInstall = hint(
          musl = "'apk add py3-pip && pip install --break-system-packages gcovr'",
          glibc = "'pip install gcovr' (distro packages are usually too old)",
          macos = "'pip install gcovr' or 'brew install gcovr'",
        )
        val version = run(listOf("gcovr", "--version"))
        if (version == null || version.first != 0) {
          problems += "gcovr not found (generates the C++ report)\n    Install it: $gcovrInstall"
        } else {
          val help = run(listOf("gcovr", "--help"))?.second.orEmpty()
          val missingFlags = requiredGcovrFlags.filterNot { help.contains(it) }
          if (missingFlags.isEmpty()) {
            found += "gcovr: ${firstLine(version.second)}"
          } else {
            problems += "${firstLine(version.second)} is too old: it lacks ${missingFlags.joinToString()} (gcovr 8.3+ needed)\n" +
              "    Upgrade it: ${gcovrInstall.replace("pip install", "pip install --upgrade")}"
          }
        }
      }

      found.forEach { project.logger.lifecycle("  [ok] $it") }
      if (problems.isNotEmpty()) {
        throw GradleException(
          "Coverage tools check failed -- ${problems.size} problem(s), no coverage build or test was run:\n" +
            problems.joinToString("\n") { "  - $it" },
        )
      }
    }
  }
  tasks.named { it != "checkCoverageTools" && it.contains("Coverage") }.configureEach {
    dependsOn(checkCoverageTools)
  }
  // Not a coverage task by name, but gtestCoverage needs it and it fails without make --
  // let the check report that instead.
  tasks.named { it == "buildNativeLibs" }.configureEach {
    mustRunAfter(checkCoverageTools)
  }

  // gcov adds to existing .gcda counts, and .gcda files left over from before a
  // recompile no longer match the new .gcno stamps -- so every gtest binary must start
  // from zero. Runs before each gtestCoverage_<test> task rather than in gtestCoverage
  // itself, which is only an aggregate that executes after its test tasks.
  val cleanGtestCoverageData = tasks.register<Delete>("cleanGtestCoverageData") {
    delete(fileTree(gtestObjDir) { include("**/*.gcda") })
  }
  tasks.named { it.startsWith("gtestCoverage_") }.configureEach {
    dependsOn(cleanGtestCoverageData)
  }

  tasks.register("coverageReport") {
    group = "verification"
    description = "Generates the Java (JaCoCo) and C++ (gcovr) coverage reports from gtestCoverage and :ddprof-test:testCoverage/testSlowCoverage (requires gcovr 8.3+; see checkCoverageTools)"
    dependsOn("gtestCoverage", ":ddprof-test:testCoverage", ":ddprof-test:testSlowCoverage", ":ddprof-test:jacocoTestReport")
    // The Java test tasks defer their failures while this report runs; the finalizer
    // fails the build on them once both reports are written.
    finalizedBy(":ddprof-test:checkCoverageTestFailures")

    val reportDir = layout.buildDirectory.dir("reports/coverage/cpp")
    val libObjDir = layout.buildDirectory.dir("obj/main/coverage")
    val srcRoot = project.file("src/main/cpp")

    doLast {
      val gcovExecutable = gcovCommand(PlatformUtils.findCompiler(project)).joinToString(" ")

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
      // checkCoverageTools has already verified gcovr is installed and new enough.
      val process = ProcessBuilder(cmd)
        .directory(project.projectDir)
        .redirectErrorStream(true)
        .start()
      val output = process.inputStream.bufferedReader().use { it.readText() }
      val exitCode = process.waitFor()
      println(output)
      if (exitCode != 0) {
        throw GradleException("gcovr failed (exit $exitCode) -- see its output above")
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

val debugObjDir: File = layout.buildDirectory.dir("obj/main/debug").get().asFile
val signalReachabilityScript: File = rootProject.file("utils/check-signal-reachability.py")

// The reachability checker reads ELF objects only (Linux); Mach-O objects are skipped.
fun hasElfObjects(dir: File): Boolean {
  val obj = dir.listFiles { f -> f.name.endsWith(".o") }?.firstOrNull() ?: return false
  val magic = ByteArray(4)
  return obj.inputStream().use { it.read(magic) } == 4 &&
    magic.contentEquals(byteArrayOf(0x7f, 'E'.code.toByte(), 'L'.code.toByte(), 'F'.code.toByte()))
}

// Static async-signal-safety reachability check over the debug objects; see
// utils/check-signal-reachability.py. Not wired into check/build: run
// `./gradlew :ddprof-lib:checkSignalReachability` (fails fast), or via
// qualityChecks. The checker reads ELF objects only, so the task is skipped
// when the debug objects are absent or not ELF.
tasks.register<Exec>("checkSignalReachability") {
  group = "verification"
  description = "Checks that no async-signal-unsafe function is reachable from the signal handlers and malloc hooks"
  // Compile task exists for every active configuration; named lookup fails loudly on rename.
  dependsOn(tasks.named("compileDebug"))

  commandLine("python3", signalReachabilityScript.absolutePath, "--obj-dir", debugObjDir.absolutePath)

  onlyIf("debug objects are ELF") { hasElfObjects(debugObjDir) }
}

// Quality checks: the signal-reachability check (ELF hosts only) and its
// fixture self-test (Linux only), plus the source-level utils/check-*.py
// scripts, each also runnable on its own. Not wired into check/build; CI runs
// `./gradlew :ddprof-lib:qualityChecks` in the source-invariant-checks job of
// .github/workflows/ci.yml. Runs every check, collects every failure, and
// fails once at the end.
interface QualityCheckServices {
  @get:Inject val exec: ExecOperations
}

tasks.register("qualityChecks") {
  group = "verification"
  description = "Runs the signal-reachability check and the source-level quality checks in utils/"
  // Depends on the debug objects, not on checkSignalReachability: that Exec
  // task fails fast, which would stop the remaining checks from running.
  dependsOn(tasks.named("compileDebug"))

  val exec = objects.newInstance<QualityCheckServices>().exec
  val root = rootProject.projectDir
  val scripts = listOf(
    "check-jvm-boundary-includes.py",
    "check-doc-index.py",
    "check-sigsetjmp-shape.py",
    "check-tracked-artifacts.py",
  ).map { File(root, "utils/$it") }

  doLast {
    val failed = mutableListOf<String>()
    // Compile-and-assert the planted-violation fixture first: it pins the
    // checker's most fragile assumptions (section symbols, ctor aliases, TLS,
    // std-library attribution) and catches toolchain/objdump drift. The
    // checker is ELF-only, so the self-test runs on Linux hosts only (macOS
    // produces Mach-O fixture objects by design).
    val onLinux = System.getProperty("os.name").lowercase().contains("linux")
    if (onLinux) {
      exec.exec {
        commandLine("python3", signalReachabilityScript.absolutePath, "--self-test")
        isIgnoreExitValue = true
      }.exitValue.takeIf { it != 0 }?.let { failed += "self-test (check-signal-reachability.py --self-test)" }
    }
    if (hasElfObjects(debugObjDir)) {
      exec.exec {
        commandLine("python3", signalReachabilityScript.absolutePath, "--obj-dir", debugObjDir.absolutePath)
        isIgnoreExitValue = true
      }.exitValue.takeIf { it != 0 }?.let { failed += "check-signal-reachability.py" }
    } else {
      logger.lifecycle("qualityChecks: check-signal-reachability.py skipped (debug objects are not ELF)")
    }
    failed += scripts.filter { script ->
      exec.exec {
        commandLine("python3", script.absolutePath, "--root", root.absolutePath)
        isIgnoreExitValue = true
      }.exitValue != 0
    }.map { it.name }
    if (failed.isNotEmpty()) {
      throw GradleException("quality checks failed: ${failed.joinToString { it }}")
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

      // Add artifacts from each publishable build configuration (see the
      // packagedConfigNames comment above)
      afterEvaluate {
        nativeBuild.buildConfigurations.filter { it.publishable.get() }.map { it.name }.forEach { name ->
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
