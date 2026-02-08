
package com.datadoghq.native.util

import com.datadoghq.native.model.Architecture
import com.datadoghq.native.model.Platform
import org.gradle.api.GradleException
import org.gradle.api.Project
import java.io.File
import java.util.concurrent.TimeUnit

object PlatformUtils {
    val currentPlatform: Platform by lazy { Platform.current() }
    val currentArchitecture: Architecture by lazy { Architecture.current() }

    fun isMusl(): Boolean {
        if (currentPlatform != Platform.LINUX) {
            return false
        }

        // Check if running on musl libc by scanning /lib/ld-musl-*.so.1
        return File("/lib").listFiles()?.any {
            it.name.startsWith("ld-musl-") && it.name.endsWith(".so.1")
        } ?: false
    }

    fun javaHome(): String {
        return System.getenv("JAVA_HOME")
            ?: System.getProperty("java.home")
            ?: throw IllegalStateException("Neither JAVA_HOME environment variable nor java.home system property is set")
    }

    /**
     * Resolve JAVA_HOME for test execution, preferring JAVA_TEST_HOME if set.
     * This allows running tests with a different JDK than the build JDK.
     */
    fun testJavaHome(): String {
        return System.getenv("JAVA_TEST_HOME")
            ?: System.getenv("JAVA_HOME")
            ?: System.getProperty("java.home")
            ?: throw IllegalStateException("Neither JAVA_TEST_HOME, JAVA_HOME, nor java.home is set")
    }

    /**
     * Get the java executable path for test execution.
     */
    fun testJavaExecutable(): String {
        return "${testJavaHome()}/bin/java"
    }

    fun jniIncludePaths(): List<String> {
        val javaHome = javaHome()
        val platform = when (currentPlatform) {
            Platform.LINUX -> "linux"
            Platform.MACOS -> "darwin"
        }
        return listOf(
            "$javaHome/include",
            "$javaHome/include/$platform"
        )
    }

    /**
     * Check if a compiler is available and functional
     */
    fun isCompilerAvailable(compiler: String): Boolean {
        return try {
            val process = ProcessBuilder(compiler, "--version")
                .redirectErrorStream(true)
                .start()
            process.waitFor(5, TimeUnit.SECONDS)
            process.exitValue() == 0
        } catch (e: Exception) {
            false
        }
    }

    /**
     * Locate a library using compiler's -print-file-name.
     * Uses the specified compiler, falling back to gcc if not available.
     */
    fun locateLibrary(libName: String, compiler: String = "gcc"): String? {
        if (currentPlatform != Platform.LINUX) {
            return null
        }

        return try {
            // Try the specified compiler first, fall back to gcc
            val compilerToUse = if (isCompilerAvailable(compiler)) {
                compiler
            } else if (compiler != "gcc" && isCompilerAvailable("gcc")) {
                "gcc"
            } else {
                return null
            }

            val process = ProcessBuilder(compilerToUse, "-print-file-name=$libName.so")
                .redirectErrorStream(true)
                .start()

            val output = process.inputStream.bufferedReader().readText().trim()
            process.waitFor()

            if (process.exitValue() == 0 && !output.endsWith("$libName.so")) {
                output
            } else {
                null
            }
        } catch (e: Exception) {
            null
        }
    }

    fun locateLibasan(compiler: String = "gcc"): String? = locateLibrary("libasan", compiler)

    fun locateLibtsan(compiler: String = "gcc"): String? = locateLibrary("libtsan", compiler)

    fun checkFuzzerSupport(): Boolean {
        return try {
            val testFile = createTempFile("fuzzer_check", ".cpp")
            try {
                testFile.writeText("extern \"C\" int LLVMFuzzerTestOneInput(const char*, long) { return 0; }")

                val process = ProcessBuilder(
                    "clang++",
                    "-fsanitize=fuzzer",
                    "-c",
                    testFile.absolutePath,
                    "-o",
                    "/dev/null"
                ).redirectErrorStream(true).start()

                process.waitFor()
                process.exitValue() == 0
            } finally {
                testFile.delete()
            }
        } catch (e: Exception) {
            false
        }
    }

    fun hasAsan(compiler: String = "gcc"): Boolean {
        return !isMusl() && locateLibasan(compiler) != null
    }

    fun hasTsan(compiler: String = "gcc"): Boolean {
        return !isMusl() && locateLibtsan(compiler) != null
    }

    fun hasFuzzer(): Boolean {
        return !isMusl() && checkFuzzerSupport()
    }

    fun sharedLibExtension(): String = when (currentPlatform) {
        Platform.LINUX -> "so"
        Platform.MACOS -> "dylib"
    }

    /**
     * Find Homebrew LLVM installation on macOS.
     * Returns the LLVM installation path or null if not found.
     */
    fun findHomebrewLLVM(): String? {
        if (currentPlatform != Platform.MACOS) {
            return null
        }

        val possiblePaths = listOf(
            "/opt/homebrew/opt/llvm", // Apple Silicon
            "/usr/local/opt/llvm" // Intel Mac
        )

        for (path in possiblePaths) {
            if (File(path).exists() && File("$path/bin/clang++").exists()) {
                return path
            }
        }

        // Try using brew command
        return try {
            val process = ProcessBuilder("brew", "--prefix", "llvm")
                .redirectErrorStream(true)
                .start()
            process.waitFor(5, TimeUnit.SECONDS)
            if (process.exitValue() == 0) {
                val brewPath = process.inputStream.bufferedReader().readText().trim()
                if (File("$brewPath/bin/clang++").exists()) {
                    brewPath
                } else {
                    null
                }
            } else {
                null
            }
        } catch (e: Exception) {
            null
        }
    }

    /**
     * Find the clang resource directory within an LLVM installation.
     * This is needed for locating libFuzzer on macOS with Homebrew LLVM.
     */
    fun findClangResourceDir(llvmPath: String?): String? {
        if (llvmPath == null) {
            return null
        }

        val clangLibDir = File("$llvmPath/lib/clang")
        if (!clangLibDir.exists()) {
            return null
        }

        // Find the version directory (e.g., 18.1.8 or 19)
        val versions = clangLibDir.listFiles()
            ?.filter { it.isDirectory }
            ?.sortedByDescending { it.name }

        return if (versions != null && versions.isNotEmpty()) {
            "$llvmPath/lib/clang/${versions[0].name}"
        } else {
            null
        }
    }

    /**
     * Find a compiler suitable for fuzzing.
     * On macOS, prefers Homebrew LLVM's clang++ for libFuzzer support.
     */
    fun findFuzzerCompiler(project: Project): String {
        if (currentPlatform == Platform.MACOS) {
            val homebrewLLVM = findHomebrewLLVM()
            if (homebrewLLVM != null) {
                return "$homebrewLLVM/bin/clang++"
            }
        }
        return findCompiler(project)
    }

    /**
     * Detect the installed clang-format version.
     * Returns null if clang-format is not available.
     */
    fun clangFormatVersion(): String? {
        return try {
            val process = ProcessBuilder("clang-format", "--version").start()
            process.waitFor(5, TimeUnit.SECONDS)
            if (process.exitValue() == 0) {
                val output = process.inputStream.bufferedReader().readText().trim()
                val match = Regex("""clang-format version (\d+\.\d+\.\d+)""").find(output)
                match?.groupValues?.get(1)
            } else {
                null
            }
        } catch (e: Exception) {
            null
        }
    }

    /**
     * Find a C++ compiler, respecting -Pnative.forceCompiler property.
     * Auto-detects clang++ or g++ if not specified.
     */
    fun findCompiler(project: Project): String {
        // Check for forced compiler override
        val forcedCompiler = project.findProperty("native.forceCompiler") as? String
        if (forcedCompiler != null) {
            if (isCompilerAvailable(forcedCompiler)) {
                project.logger.info("Using forced compiler: $forcedCompiler")
                return forcedCompiler
            }
            throw GradleException(
                "Forced compiler '$forcedCompiler' is not available. " +
                "Verify the path or remove -Pnative.forceCompiler to auto-detect."
            )
        }

        // Auto-detect: prefer clang++, then g++, then c++
        val compilers = listOf("clang++", "g++", "c++")
        for (compiler in compilers) {
            if (isCompilerAvailable(compiler)) {
                project.logger.info("Auto-detected compiler: $compiler")
                return compiler
            }
        }

        throw GradleException(
            "No C++ compiler found. Please install clang++ or g++, " +
            "or specify one with -Pnative.forceCompiler=/path/to/compiler"
        )
    }
}
