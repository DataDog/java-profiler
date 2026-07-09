
package com.datadoghq.native.config

import com.datadoghq.native.model.Architecture
import com.datadoghq.native.model.BuildConfiguration
import com.datadoghq.native.model.Platform
import com.datadoghq.native.util.CompilerInfo
import com.datadoghq.native.util.PlatformUtils
import java.io.File
import org.gradle.api.logging.Logger

/**
 * Provides factory methods for creating standard build configurations
 * (release, debug, asan, tsan, fuzzer) with appropriate compiler and linker flags.
 */
object ConfigurationPresets {

    /**
     * Sets up standard build configurations (release, debug, asan, tsan, fuzzer) on the extension.
     * This is the shared implementation used by both NativeBuildPlugin and RootProjectPlugin.
     *
     * @param extension The NativeBuildExtension to configure
     * @param project The Gradle project (used for rootDir, logger, and compiler detection)
     */
    fun setupStandardConfigurations(
        extension: com.datadoghq.native.NativeBuildExtension,
        project: org.gradle.api.Project
    ) {
        if (extension.buildConfigurations.isNotEmpty()) {
            return // Don't override explicitly defined configurations
        }

        val currentPlatform = PlatformUtils.currentPlatform
        val currentArch = PlatformUtils.currentArchitecture
        val version = extension.version.get()
        val rootDir = project.rootDir
        val compiler = PlatformUtils.findCompiler(project)

        project.logger.lifecycle("Setting up standard build configurations for $currentPlatform-$currentArch")
        project.logger.lifecycle("Using compiler: ${compiler.executable} (version ${compiler.majorVersion})")

        val commonCompilerArgs = commonCompilerArgs(version, compiler, currentArch, currentPlatform, project.logger)

        extension.buildConfigurations.apply {
            register("release") {
                configureRelease(this, currentPlatform, currentArch, commonCompilerArgs)
            }
            register("debug") {
                configureDebug(this, currentPlatform, currentArch, commonCompilerArgs)
            }
            register("asan") {
                configureAsan(this, currentPlatform, currentArch, rootDir, compiler, commonCompilerArgs)
            }
            register("tsan") {
                configureTsan(this, currentPlatform, currentArch, rootDir, compiler, commonCompilerArgs)
            }
            register("fuzzer") {
                configureFuzzer(this, currentPlatform, currentArch, rootDir, commonCompilerArgs)
            }
        }

        val activeConfigs = extension.getActiveConfigurations(currentPlatform, currentArch)
        project.logger.lifecycle("Active configurations: ${activeConfigs.map { it.name }.joinToString(", ")}")
    }

    private fun commonCompilerArgs(
        version: String,
        compiler: CompilerInfo,
        architecture: Architecture,
        platform: Platform,
        logger: Logger
    ): List<String> {
        val args = mutableListOf(
            "-fPIC",
            "-fno-omit-frame-pointer",
            "-momit-leaf-frame-pointer",
            "-fvisibility=hidden",
            "-fdata-sections",
            "-ffunction-sections",
            "-std=c++17",
            "-DPROFILER_VERSION=\"$version\"",
            "-DCOUNTERS"
        )
        // Define __musl__ when building on musl libc (it doesn't define this by default)
        if (PlatformUtils.isMusl()) {
            args.add("-D__musl__")
        }

        // Use TLS descriptors (GNU2 dialect) for thread-local storage on x86_64 Linux,
        // required by thread context (https://github.com/open-telemetry/opentelemetry-specification/pull/4947).
        // The `-mtls-dialect=gnu2` spelling is x86-specific, so gate on platform/arch.
        if (platform == Platform.LINUX && architecture == Architecture.X64) {
            if (compiler.supportsTlsDialectGnu2()) {
                args.add("-mtls-dialect=gnu2")
            } else {
                // Only clang older than 19 reaches here (gcc/others are always supported).
                logger.lifecycle(
                    "GNU2 TLS dialect disabled: -mtls-dialect=gnu2 requires clang >= 19, " +
                    "but detected clang ${compiler.majorVersion} for ${compiler.executable}."
                )
            }
        }

        if (platform == Platform.MACOS) {
            args += listOf("-D_XOPEN_SOURCE", "-D_DARWIN_C_SOURCE")
        }

        return args
    }

    private fun commonLinuxLinkerArgs(): List<String> = listOf(
        "-ldl",
        "-Wl,-z,defs",
        "--verbose",
        "-lpthread",
        "-lm",
        "-lrt",
        "-Wl,--build-id"
    )

    fun configureRelease(
        config: BuildConfiguration,
        platform: Platform,
        architecture: Architecture,
        commonCompilerArgs: List<String>
    ) {
        config.platform.set(platform)
        config.architecture.set(architecture)
        config.active.set(true)

        when (platform) {
            Platform.LINUX -> {
                config.compilerArgs.set(
                    listOf("-O3", "-DNDEBUG", "-g") + commonCompilerArgs
                )
                config.linkerArgs.set(
                    commonLinuxLinkerArgs() + listOf(
                        "-Wl,-z,nodelete",
                        "-static-libstdc++",
                        "-static-libgcc",
                        "-Wl,--exclude-libs,ALL",
                        "-Wl,--gc-sections"
                    )
                )
            }
            Platform.MACOS -> {
                config.compilerArgs.set(
                    commonCompilerArgs + listOf("-O3", "-DNDEBUG", "-g")
                )
                config.linkerArgs.set(emptyList())
            }
        }
    }

    fun configureDebug(
        config: BuildConfiguration,
        platform: Platform,
        architecture: Architecture,
        commonCompilerArgs: List<String>
    ) {
        config.platform.set(platform)
        config.architecture.set(architecture)
        config.active.set(true)

        when (platform) {
            Platform.LINUX -> {
                config.compilerArgs.set(
                    listOf("-O0", "-g", "-DDEBUG") + commonCompilerArgs
                )
                config.linkerArgs.set(commonLinuxLinkerArgs())
            }
            Platform.MACOS -> {
                config.compilerArgs.set(
                    commonCompilerArgs + listOf("-O0", "-g", "-DDEBUG")
                )
                config.linkerArgs.set(emptyList())
            }
        }
    }

    fun configureAsan(
        config: BuildConfiguration,
        platform: Platform,
        architecture: Architecture,
        rootDir: File,
        compiler: CompilerInfo,
        commonCompilerArgs: List<String>
    ) {
        config.platform.set(platform)
        config.architecture.set(architecture)
        config.active.set(PlatformUtils.hasAsan(compiler.executable))

        val asanCompilerArgs = listOf(
            "-g",
            "-DDEBUG",
            "-fPIC",
            "-fsanitize=address",
            "-fsanitize=undefined",
            "-fno-sanitize-recover=all",
            "-fsanitize=float-divide-by-zero",
            "-fstack-protector-all",
            "-fsanitize=leak",
            "-fsanitize=pointer-overflow",
            "-fsanitize=return",
            "-fsanitize=bounds",
            "-fsanitize=alignment",
            "-fsanitize=object-size",
            "-fno-omit-frame-pointer",
            "-fno-optimize-sibling-calls"
        )

        when (platform) {
            Platform.LINUX -> {
                config.compilerArgs.set(asanCompilerArgs + commonCompilerArgs)

                val libasan = PlatformUtils.locateLibasan(compiler.executable)
                // Link against the sanitizer runtime that matches the compiler:
                // - clang: locateLibasan returns libclang_rt.asan-<arch>.so, which
                //   includes UBSan symbols; -lclang_rt.asan-<arch> satisfies -z defs
                //   for both __asan_* and __ubsan_* and matches the runtime that
                //   -fsanitize=address links into executables — one runtime, no conflict.
                // - gcc: locateLibasan returns libasan.so; -lasan + -lubsan as before.
                val asanLinkerArgs = if (libasan != null) {
                    val asanLibDir = File(libasan).parent
                    val asanLibName = File(libasan).nameWithoutExtension.removePrefix("lib")
                    val ubsanLibs = if (asanLibName.startsWith("clang_rt")) emptyList()
                                    else listOf("-lubsan")
                    listOf("-L$asanLibDir", "-l$asanLibName",
                           "-Wl,-rpath,$asanLibDir") +
                    ubsanLibs +
                    listOf("-fsanitize=address", "-fsanitize=undefined", "-fno-omit-frame-pointer")
                } else {
                    listOf("-fsanitize=address", "-fsanitize=undefined", "-fno-omit-frame-pointer")
                }

                config.linkerArgs.set(commonLinuxLinkerArgs() + asanLinkerArgs)

                if (libasan != null) {
                    config.testEnvironment.apply {
                        put("LD_PRELOAD", libasan)
                        put("ASAN_OPTIONS", "allocator_may_return_null=1:unwind_abort_on_malloc=1:use_sigaltstack=0:detect_stack_use_after_return=0:handle_segv=0:halt_on_error=0:abort_on_error=0:print_stacktrace=1:symbolize=1:log_path=/tmp/asan.log:suppressions=$rootDir/gradle/sanitizers/asan.supp")
                        put("UBSAN_OPTIONS", "halt_on_error=0:abort_on_error=0:print_stacktrace=1:suppressions=$rootDir/gradle/sanitizers/ubsan.supp")
                        put("LSAN_OPTIONS", "detect_leaks=0")
                    }
                    // G1GC's heap reservation is placed just below 2 GB (0x7fff7000) by ASLR on
                    // some kernel configurations, which is exactly where ASan needs to mmap its
                    // shadow bytes [0x7fff7000-0x10007fff7fff].  Force the heap to a very low
                    // base address so the entire JVM footprint stays below the shadow range.
                    // HeapBaseMinAddress is not accepted by JDK <= 11 (constraint violation);
                    // those JDKs rely on the vm.mmap_rnd_bits=8 CI-level mitigation instead.
                    if (PlatformUtils.testJvmMajorVersion() >= 12) {
                        // HeapBaseMinAddress=64MB leaves ~1.9GB of address space below the
                        // shadow region (0x7fff7000); 1024m keeps heap+CompressedClassSpace
                        // well within that margin while giving forkEvery-restarted JVMs
                        // enough headroom to avoid "Java heap space" OOMs seen in nightly CI.
                        config.testJvmArgs.addAll(listOf(
                            "-XX:HeapBaseMinAddress=0x4000000",
                            "-Xmx1024m",
                            "-XX:CompressedClassSpaceSize=256m"
                        ))
                    }
                }
            }
            Platform.MACOS -> {
                // ASAN not typically configured for macOS in this project
                config.active.set(false)
            }
        }
    }

    fun configureTsan(
        config: BuildConfiguration,
        platform: Platform,
        architecture: Architecture,
        rootDir: File,
        compiler: CompilerInfo,
        commonCompilerArgs: List<String>
    ) {
        config.platform.set(platform)
        config.architecture.set(architecture)
        config.active.set(PlatformUtils.hasTsan(compiler.executable))

        val tsanCompilerArgs = listOf(
            "-g",
            "-DDEBUG",
            "-fPIC",
            "-fsanitize=thread",
            "-fno-omit-frame-pointer",
            "-fno-optimize-sibling-calls"
        )

        when (platform) {
            Platform.LINUX -> {
                config.compilerArgs.set(tsanCompilerArgs + commonCompilerArgs)

                val libtsan = PlatformUtils.locateLibtsan(compiler.executable)
                // Use the library name from the resolved path so that clang's own
                // libclang_rt.tsan-<arch>.so is linked by name (not as -ltsan).
                val tsanLinkerArgs = if (libtsan != null) {
                    val tsanLibDir = File(libtsan).parent
                    val tsanLibName = File(libtsan).nameWithoutExtension.removePrefix("lib")
                    listOf(
                        "-L$tsanLibDir",
                        "-l$tsanLibName",
                        "-Wl,-rpath,$tsanLibDir",
                        "-fsanitize=thread",
                        "-fno-omit-frame-pointer"
                    )
                } else {
                    listOf("-fsanitize=thread", "-fno-omit-frame-pointer")
                }

                config.linkerArgs.set(commonLinuxLinkerArgs() + tsanLinkerArgs)

                config.testEnvironment.apply {
                    if (libtsan != null) {
                        put("LD_PRELOAD", libtsan)
                        // handle_segv=0 / handle_sigbus=0: let the JVM handle these signals
                        //   (SafeFetch, NullPointerException, memory bus errors).
                        // use_sigaltstack=0: JVM manages its own alternate signal stack.
                        // halt_on_error=0: report all races; process exits with code 66 at end.
                        // abort_on_error=0: use exit() not abort() so Java shutdown hooks run.
                        // io_sync=0: disable TSan's own FD-tracking, which races internally
                        //   when the JVM concurrently closes/reads file descriptors.
                        put("TSAN_OPTIONS", "handle_segv=0:handle_sigbus=0:use_sigaltstack=0:halt_on_error=0:abort_on_error=0:io_sync=0:suppressions=$rootDir/gradle/sanitizers/tsan.supp")
                    }
                    // fork() is unsupported under TSan; threadsafe style uses execve instead.
                    put("GTEST_DEATH_TEST_STYLE", "threadsafe")
                }
            }
            Platform.MACOS -> {
                // TSAN not typically configured for macOS in this project
                config.active.set(false)
            }
        }
    }

    fun configureFuzzer(
        config: BuildConfiguration,
        platform: Platform,
        architecture: Architecture,
        rootDir: File,
        commonCompilerArgs: List<String>
    ) {
        config.platform.set(platform)
        config.architecture.set(architecture)
        config.active.set(PlatformUtils.hasFuzzer())

        val fuzzerCompilerArgs = listOf(
            "-g",
            "-DDEBUG",
            "-fPIC",
            "-fsanitize=address",
            "-fsanitize=undefined",
            "-fno-sanitize-recover=all",
            "-fno-omit-frame-pointer",
            "-fno-optimize-sibling-calls"
        )

        val fuzzerLinkerArgs = listOf(
            "-fsanitize=address",
            "-fsanitize=undefined",
            "-fno-omit-frame-pointer"
        )

        when (platform) {
            Platform.LINUX -> {
                config.compilerArgs.set(fuzzerCompilerArgs + commonCompilerArgs)
                config.linkerArgs.set(commonLinuxLinkerArgs() + fuzzerLinkerArgs)

                config.testEnvironment.apply {
                    put("ASAN_OPTIONS", "allocator_may_return_null=1:detect_stack_use_after_return=0:handle_segv=0:abort_on_error=1:symbolize=1:suppressions=$rootDir/gradle/sanitizers/asan.supp")
                    put("UBSAN_OPTIONS", "halt_on_error=1:abort_on_error=1:print_stacktrace=1:suppressions=$rootDir/gradle/sanitizers/ubsan.supp")
                }
            }
            Platform.MACOS -> {
                config.compilerArgs.set(fuzzerCompilerArgs + commonCompilerArgs)
                config.linkerArgs.set(fuzzerLinkerArgs)

                config.testEnvironment.apply {
                    put("ASAN_OPTIONS", "allocator_may_return_null=1:detect_stack_use_after_return=0:abort_on_error=1:symbolize=1")
                    put("UBSAN_OPTIONS", "halt_on_error=1:abort_on_error=1:print_stacktrace=1")
                }
            }
        }
    }
}
