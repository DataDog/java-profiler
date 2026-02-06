// Copyright 2026, Datadog, Inc

package com.datadoghq.native.config

import com.datadoghq.native.model.Architecture
import com.datadoghq.native.model.BuildConfiguration
import com.datadoghq.native.model.Platform
import com.datadoghq.native.util.PlatformUtils
import java.io.File

/**
 * Provides factory methods for creating standard build configurations
 * (release, debug, asan, tsan, fuzzer) with appropriate compiler and linker flags.
 */
object ConfigurationPresets {

    private fun commonLinuxCompilerArgs(version: String): List<String> = listOf(
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

    private fun commonLinuxLinkerArgs(): List<String> = listOf(
        "-ldl",
        "-Wl,-z,defs",
        "--verbose",
        "-lpthread",
        "-lm",
        "-lrt",
        "-v",
        "-Wl,--build-id"
    )

    private fun commonMacosCompilerArgs(version: String): List<String> =
        commonLinuxCompilerArgs(version) + listOf("-D_XOPEN_SOURCE", "-D_DARWIN_C_SOURCE")

    fun configureRelease(
        config: BuildConfiguration,
        platform: Platform,
        architecture: Architecture,
        version: String,
        rootDir: File
    ) {
        config.platform.set(platform)
        config.architecture.set(architecture)
        config.active.set(true)

        when (platform) {
            Platform.LINUX -> {
                config.compilerArgs.set(
                    listOf("-O3", "-DNDEBUG", "-g") + commonLinuxCompilerArgs(version)
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
                    commonMacosCompilerArgs(version) + listOf("-O3", "-DNDEBUG", "-g")
                )
                config.linkerArgs.set(emptyList())
            }
        }
    }

    fun configureDebug(
        config: BuildConfiguration,
        platform: Platform,
        architecture: Architecture,
        version: String,
        rootDir: File
    ) {
        config.platform.set(platform)
        config.architecture.set(architecture)
        config.active.set(true)

        when (platform) {
            Platform.LINUX -> {
                config.compilerArgs.set(
                    listOf("-O0", "-g", "-DDEBUG") + commonLinuxCompilerArgs(version)
                )
                config.linkerArgs.set(commonLinuxLinkerArgs())
            }
            Platform.MACOS -> {
                config.compilerArgs.set(
                    commonMacosCompilerArgs(version) + listOf("-O0", "-g", "-DDEBUG")
                )
                config.linkerArgs.set(emptyList())
            }
        }
    }

    fun configureAsan(
        config: BuildConfiguration,
        platform: Platform,
        architecture: Architecture,
        version: String,
        rootDir: File,
        compiler: String = "gcc"
    ) {
        config.platform.set(platform)
        config.architecture.set(architecture)
        config.active.set(PlatformUtils.hasAsan(compiler))

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
                config.compilerArgs.set(asanCompilerArgs + commonLinuxCompilerArgs(version))

                val libasan = PlatformUtils.locateLibasan(compiler)
                val asanLinkerArgs = if (libasan != null) {
                    listOf(
                        "-L${File(libasan).parent}",
                        "-lasan",
                        "-lubsan",
                        "-fsanitize=address",
                        "-fsanitize=undefined",
                        "-fno-omit-frame-pointer"
                    )
                } else {
                    emptyList()
                }

                config.linkerArgs.set(commonLinuxLinkerArgs() + asanLinkerArgs)

                if (libasan != null) {
                    config.testEnvironment.apply {
                        put("LD_PRELOAD", libasan)
                        put("ASAN_OPTIONS", "allocator_may_return_null=1:unwind_abort_on_malloc=1:use_sigaltstack=0:detect_stack_use_after_return=0:handle_segv=1:halt_on_error=0:abort_on_error=0:print_stacktrace=1:symbolize=1:suppressions=$rootDir/gradle/sanitizers/asan.supp")
                        put("UBSAN_OPTIONS", "halt_on_error=0:abort_on_error=0:print_stacktrace=1:suppressions=$rootDir/gradle/sanitizers/ubsan.supp")
                        put("LSAN_OPTIONS", "detect_leaks=0")
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
        version: String,
        rootDir: File,
        compiler: String = "gcc"
    ) {
        config.platform.set(platform)
        config.architecture.set(architecture)
        config.active.set(PlatformUtils.hasTsan(compiler))

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
                config.compilerArgs.set(tsanCompilerArgs + commonLinuxCompilerArgs(version))

                val libtsan = PlatformUtils.locateLibtsan(compiler)
                val tsanLinkerArgs = if (libtsan != null) {
                    listOf(
                        "-L${File(libtsan).parent}",
                        "-ltsan",
                        "-fsanitize=thread",
                        "-fno-omit-frame-pointer"
                    )
                } else {
                    emptyList()
                }

                config.linkerArgs.set(commonLinuxLinkerArgs() + tsanLinkerArgs)

                if (libtsan != null) {
                    config.testEnvironment.apply {
                        put("LD_PRELOAD", libtsan)
                        put("TSAN_OPTIONS", "suppressions=$rootDir/gradle/sanitizers/tsan.supp")
                    }
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
        version: String,
        rootDir: File
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
                config.compilerArgs.set(fuzzerCompilerArgs + commonLinuxCompilerArgs(version))
                config.linkerArgs.set(commonLinuxLinkerArgs() + fuzzerLinkerArgs)

                config.testEnvironment.apply {
                    put("ASAN_OPTIONS", "allocator_may_return_null=1:detect_stack_use_after_return=0:handle_segv=0:abort_on_error=1:symbolize=1:suppressions=$rootDir/gradle/sanitizers/asan.supp")
                    put("UBSAN_OPTIONS", "halt_on_error=1:abort_on_error=1:print_stacktrace=1:suppressions=$rootDir/gradle/sanitizers/ubsan.supp")
                }
            }
            Platform.MACOS -> {
                config.compilerArgs.set(fuzzerCompilerArgs + commonMacosCompilerArgs(version))
                config.linkerArgs.set(fuzzerLinkerArgs)

                config.testEnvironment.apply {
                    put("ASAN_OPTIONS", "allocator_may_return_null=1:detect_stack_use_after_return=0:abort_on_error=1:symbolize=1")
                    put("UBSAN_OPTIONS", "halt_on_error=1:abort_on_error=1:print_stacktrace=1")
                }
            }
        }
    }
}
