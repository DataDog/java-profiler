// Copyright 2026, Datadog, Inc

package com.datadoghq.native.fuzz

import com.datadoghq.native.model.Platform
import com.datadoghq.native.tasks.NativeCompileTask
import com.datadoghq.native.tasks.NativeLinkExecutableTask
import com.datadoghq.native.util.PlatformUtils
import org.gradle.api.Plugin
import org.gradle.api.Project
import org.gradle.api.file.ConfigurableFileCollection
import org.gradle.api.file.DirectoryProperty
import org.gradle.api.provider.ListProperty
import org.gradle.api.provider.Property
import org.gradle.api.tasks.Exec
import java.io.File
import javax.inject.Inject

/**
 * Plugin for libFuzzer-based fuzz testing.
 *
 * Automatically discovers fuzz targets (*.cpp files) in a source directory and generates:
 * - compileFuzz_{name} - Compile task
 * - linkFuzz_{name} - Link task
 * - fuzz_{name} - Execute task
 * - fuzz - Aggregate task running all fuzz targets
 * - listFuzzTargets - Help task
 *
 * Usage:
 * ```kotlin
 * plugins {
 *   id("com.datadoghq.fuzz-targets")
 * }
 *
 * fuzzTargets {
 *   fuzzSourceDir.set(file("src/test/fuzz"))
 *   corpusDir.set(file("src/test/fuzz/corpus"))
 *   profilerSourceDir.set(file("src/main/cpp"))
 *   duration.set(60)
 * }
 * ```
 */
class FuzzTargetsPlugin : Plugin<Project> {
    override fun apply(project: Project) {
        val extension = project.extensions.create(
            "fuzzTargets",
            FuzzTargetsExtension::class.java,
            project
        )

        project.afterEvaluate {
            configureFuzzTargets(project, extension)
        }
    }

    private fun configureFuzzTargets(project: Project, extension: FuzzTargetsExtension) {
        val hasFuzzer = PlatformUtils.hasFuzzer()

        // Master fuzz task
        val fuzzAll = project.tasks.register("fuzz") {
            onlyIf {
                hasFuzzer &&
                    !project.hasProperty("skip-tests") &&
                    !project.hasProperty("skip-native") &&
                    !project.hasProperty("skip-fuzz")
            }
            group = "verification"
            description = "Run all fuzz targets"

            doFirst {
                if (!hasFuzzer) {
                    project.logger.warn("WARNING: libFuzzer not available - skipping fuzz tests (requires clang with -fsanitize=fuzzer)")
                }
            }
        }

        if (!hasFuzzer) {
            createListFuzzTargetsTask(project, extension)
            return
        }

        val compiler = PlatformUtils.findFuzzerCompiler(project)
        val homebrewLLVM = PlatformUtils.findHomebrewLLVM()
        val clangResourceDir = PlatformUtils.findClangResourceDir(homebrewLLVM)

        // Build include paths
        val includeFiles = buildIncludePaths(project, extension, homebrewLLVM)

        // Build compiler/linker args
        val compilerArgs = buildFuzzCompilerArgs()
        val linkerArgs = buildFuzzLinkerArgs(homebrewLLVM, clangResourceDir, project.logger)

        val fuzzSourceDir = extension.fuzzSourceDir.get().asFile
        val corpusBaseDir = extension.corpusDir.get().asFile
        val crashDir = extension.crashDir.get().asFile
        val duration = extension.duration.get()

        // Discover and create tasks for each fuzz target
        if (fuzzSourceDir.exists()) {
            fuzzSourceDir.listFiles()?.filter { file -> file.name.endsWith(".cpp") }?.forEach { fuzzFile ->
                val fullName = fuzzFile.nameWithoutExtension
                val fuzzName = if (fullName.startsWith("fuzz_")) fullName.substring(5) else fullName

                val objDir = project.file("${project.layout.buildDirectory.get()}/obj/fuzz/$fuzzName")
                val binDir = project.file("${project.layout.buildDirectory.get()}/bin/fuzz/$fuzzName")
                val binary = project.file("$binDir/$fuzzName")
                val targetCorpusDir = File(corpusBaseDir, fuzzName)

                // Compile task
                val compileTask = project.tasks.register("compileFuzz_$fuzzName", NativeCompileTask::class.java) {
                    onlyIf { hasFuzzer && !project.hasProperty("skip-tests") && !project.hasProperty("skip-native") && !project.hasProperty("skip-fuzz") }
                    group = "build"
                    description = "Compile the fuzz target $fuzzName"

                    this.compiler.set(compiler)
                    this.compilerArgs.set(compilerArgs)
                    sources.from(
                        extension.profilerSourceDir.map { dir ->
                            project.fileTree(dir) { include("**/*.cpp") }
                        },
                        fuzzFile
                    )
                    includes.from(includeFiles)
                    objectFileDir.set(objDir)
                }

                // Link task
                val linkTask = project.tasks.register("linkFuzz_$fuzzName", NativeLinkExecutableTask::class.java) {
                    onlyIf { hasFuzzer && !project.hasProperty("skip-tests") && !project.hasProperty("skip-native") && !project.hasProperty("skip-fuzz") }
                    dependsOn(compileTask)
                    group = "build"
                    description = "Link the fuzz target $fuzzName"

                    linker.set(compiler)
                    this.linkerArgs.set(linkerArgs)
                    objectFiles.from(project.fileTree(objDir) { include("*.o") })
                    outputFile.set(binary)
                }

                // Execute task
                val executeTask = project.tasks.register("fuzz_$fuzzName", Exec::class.java) {
                    onlyIf { hasFuzzer && !project.hasProperty("skip-tests") && !project.hasProperty("skip-native") && !project.hasProperty("skip-fuzz") }
                    dependsOn(linkTask)
                    group = "verification"
                    description = "Run the fuzz target $fuzzName for $duration seconds"

                    doFirst {
                        crashDir.mkdirs()
                        targetCorpusDir.mkdirs()
                    }

                    executable = binary.absolutePath
                    args(
                        targetCorpusDir.absolutePath,
                        "-max_total_time=$duration",
                        "-artifact_prefix=${crashDir.absolutePath}/$fuzzName-",
                        "-print_final_stats=1"
                    )

                    inputs.files(binary)
                    outputs.upToDateWhen { false }
                }

                fuzzAll.configure { dependsOn(executeTask) }
            }
        }

        createListFuzzTargetsTask(project, extension)
    }

    private fun buildIncludePaths(project: Project, extension: FuzzTargetsExtension, homebrewLLVM: String?): ConfigurableFileCollection {
        val javaHome = PlatformUtils.javaHome()
        val platformInclude = when (PlatformUtils.currentPlatform) {
            Platform.LINUX -> "linux"
            Platform.MACOS -> "darwin"
        }

        val includes = project.files()
        includes.from(
            extension.profilerSourceDir,
            "$javaHome/include",
            "$javaHome/include/$platformInclude"
        )

        // Add additional include directories
        extension.additionalIncludes.get().forEach { dir ->
            includes.from(dir)
        }

        // Add Homebrew LLVM includes on macOS
        if (PlatformUtils.currentPlatform == Platform.MACOS && homebrewLLVM != null) {
            includes.from("$homebrewLLVM/include")
        }

        return includes
    }

    private fun buildFuzzCompilerArgs(): List<String> {
        val args = mutableListOf(
            "-O1",
            "-g",
            "-fno-omit-frame-pointer",
            "-fsanitize=fuzzer,address,undefined",
            "-fvisibility=hidden",
            "-std=c++17",
            "-DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION"
        )
        if (PlatformUtils.currentPlatform == Platform.LINUX && PlatformUtils.isMusl()) {
            args.add("-D__musl__")
        }
        return args
    }

    private fun buildFuzzLinkerArgs(homebrewLLVM: String?, clangResourceDir: String?, logger: org.gradle.api.logging.Logger): List<String> {
        val args = mutableListOf<String>()

        // libFuzzer linking strategy
        if (PlatformUtils.currentPlatform == Platform.MACOS && clangResourceDir != null) {
            val fuzzerLib = "$clangResourceDir/lib/darwin/libclang_rt.fuzzer_osx.a"
            if (File(fuzzerLib).exists()) {
                logger.info("Using Homebrew libFuzzer: $fuzzerLib")
                args.add(fuzzerLib)
                args.add("-L$homebrewLLVM/lib/c++")
                args.add("-lc++")
                args.add("-Wl,-rpath,$homebrewLLVM/lib/c++")
            } else {
                logger.warn("Homebrew libFuzzer not found, falling back to -fsanitize=fuzzer")
                args.add("-fsanitize=fuzzer,address,undefined")
            }
        } else {
            args.add("-fsanitize=fuzzer,address,undefined")
        }

        args.addAll(listOf("-ldl", "-lpthread", "-lm"))
        if (PlatformUtils.currentPlatform == Platform.LINUX) {
            args.add("-lrt")
        }

        return args
    }

    private fun createListFuzzTargetsTask(project: Project, extension: FuzzTargetsExtension) {
        project.tasks.register("listFuzzTargets") {
            group = "help"
            description = "List all available fuzz targets"
            doLast {
                val fuzzSrcDir = extension.fuzzSourceDir.get().asFile
                if (fuzzSrcDir.exists()) {
                    println("Available fuzz targets:")
                    fuzzSrcDir.listFiles()?.filter { file -> file.name.endsWith(".cpp") }?.forEach { fuzzFile ->
                        val fullName = fuzzFile.nameWithoutExtension
                        val fuzzName = if (fullName.startsWith("fuzz_")) fullName.substring(5) else fullName
                        println("  - fuzz_$fuzzName")
                    }
                    println()
                    println("Run individual targets with: ./gradlew :${project.path}:fuzz_<name>")
                    println("Run all targets with: ./gradlew :${project.path}:fuzz")
                    println("Configure duration with: -Pfuzz-duration=<seconds> (default: ${extension.duration.get()})")
                } else {
                    println("No fuzz targets found. Create .cpp files in ${fuzzSrcDir.path}")
                }
            }
        }
    }
}

/**
 * Extension for configuring fuzz targets.
 */
abstract class FuzzTargetsExtension @Inject constructor(project: Project) {
    /**
     * Directory containing fuzz target source files (*.cpp).
     */
    val fuzzSourceDir: DirectoryProperty = project.objects.directoryProperty()

    /**
     * Directory for seed corpus files.
     */
    val corpusDir: DirectoryProperty = project.objects.directoryProperty()

    /**
     * Directory for crash artifacts.
     */
    val crashDir: DirectoryProperty = project.objects.directoryProperty()

    /**
     * Directory containing the profiler C++ sources to compile with fuzz targets.
     */
    val profilerSourceDir: DirectoryProperty = project.objects.directoryProperty()

    /**
     * Additional include directories.
     */
    val additionalIncludes: ListProperty<String> = project.objects.listProperty(String::class.java)

    /**
     * Fuzz duration in seconds.
     */
    val duration: Property<Int> = project.objects.property(Int::class.java)

    init {
        // Set reasonable defaults - these should be overridden by the user
        crashDir.convention(project.layout.buildDirectory.dir("fuzz-crashes"))
        additionalIncludes.convention(emptyList())

        // Duration from property or default
        val propDuration = if (project.hasProperty("fuzz-duration")) {
            project.property("fuzz-duration").toString().toIntOrNull() ?: 60
        } else {
            60
        }
        duration.convention(propDuration)
    }
}
