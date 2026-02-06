apply(from = rootProject.file("common.gradle.kts"))

// Access functions from common.gradle.kts
val os: () -> org.gradle.internal.os.OperatingSystem = extra["os"] as () -> org.gradle.internal.os.OperatingSystem
val osIdentifier: () -> String = extra["osIdentifier"] as () -> String
val archIdentifier: () -> String = extra["archIdentifier"] as () -> String
val isMusl: () -> Boolean = extra["isMusl"] as () -> Boolean

val buildConfigurations = mutableListOf<Map<String, Any>>()

fun buildConfigNames(): List<String> {
  return buildConfigurations
    .filter { (it["os"] as String) == osIdentifier() && (it["arch"] as String) == archIdentifier() }
    .map { it["name"] as String }
    .toSet()
    .toList()
}

fun buildConfigs(): List<Map<String, Any>> {
  return buildConfigurations.filter {
    (it["os"] as String) == osIdentifier() && (it["arch"] as String) == archIdentifier()
  }
}

fun locate(file: String): String? {
  if (os().isLinux) {
    try {
      val process = ProcessBuilder("locate", file).start()
      process.waitFor()

      if (process.exitValue() == 0) {
        return process.inputStream.bufferedReader().use { it.readText().trim() }
      }
    } catch (e: Exception) {
      logger.warn("Exception when locating $file: ${e.message}")
    }
  }
  return null
}

fun locateLibrary(libName: String): String? {
  if (os().isLinux) {
    try {
      val process = ProcessBuilder("gcc", "-print-file-name=$libName.so").start()
      process.waitFor()

      if (process.exitValue() == 0) {
        val output = process.inputStream.bufferedReader().use { it.readText().trim() }
        if (output.endsWith("$libName.so")) {
          return output
        }
      }
    } catch (e: Exception) {
      logger.warn("Exception when locating $libName library: ${e.message}")
    }
  }
  return null
}

fun locateLibasan(): String? {
  return locateLibrary("libasan")
}

fun locateLibtsan(): String? {
  return locateLibrary("libtsan")
}

fun checkFuzzerSupport(): Boolean {
  // libFuzzer requires clang - check if clang supports -fsanitize=fuzzer
  try {
    val testFile = java.io.File.createTempFile("fuzzer_check", ".cpp")
    testFile.writeText("extern \"C\" int LLVMFuzzerTestOneInput(const char*, long) { return 0; }")
    testFile.deleteOnExit()

    val process = ProcessBuilder(
      "clang++",
      "-fsanitize=fuzzer",
      "-c",
      testFile.absolutePath,
      "-o",
      "/dev/null"
    ).start()
    process.waitFor()
    testFile.delete()

    return process.exitValue() == 0
  } catch (e: Exception) {
    logger.debug("Exception when checking fuzzer support: ${e.message}")
    return false
  }
}

val libasan = locateLibasan()
val libtsan = locateLibtsan()
val hasFuzzerSupport = checkFuzzerSupport()

if (libasan == null) {
  logger.debug("Asan library not found")
}
if (libtsan == null) {
  logger.debug("Tsan library not found")
}
if (!hasFuzzerSupport) {
  logger.debug("libFuzzer not available (requires clang with -fsanitize=fuzzer support)")
}

fun hasAsan(): Boolean {
  return if (isMusl()) false else libasan != null
}

fun hasTsan(): Boolean {
  return if (isMusl()) false else libtsan != null
}

fun hasFuzzer(): Boolean {
  return if (isMusl()) false else hasFuzzerSupport
}

fun isActive(name: String): Boolean {
  return when (name) {
    "asan" -> hasAsan()
    "tsan" -> hasTsan()
    "fuzzer" -> hasFuzzer()
    else -> true // no activation method defined; default to 'true'
  }
}

fun addBuildConfiguration(
  name: String,
  os: String,
  arch: String,
  compilerArgs: List<String>,
  linkerArgs: List<String>,
  testEnv: Map<String, String> = emptyMap()
) {
  buildConfigurations.add(
    mapOf(
      "active" to isActive(name),
      "name" to name,
      "os" to os,
      "arch" to arch,
      "compilerArgs" to compilerArgs,
      "linkerArgs" to linkerArgs,
      "testEnv" to testEnv
    )
  )
}

// Export functions and data to extra
extra["hasAsan"] = ::hasAsan
extra["hasTsan"] = ::hasTsan
extra["hasFuzzer"] = ::hasFuzzer
extra["buildConfigNames"] = ::buildConfigNames
extra["buildConfigs"] = ::buildConfigs
extra["locateLibasan"] = ::locateLibasan
extra["locateLibtsan"] = ::locateLibtsan
extra["buildConfigurations"] = buildConfigurations

// make sure the provided version is correctly propagated to the build
version = project.findProperty("ddprof_version") as? String ?: version

// ======= Define build configurations below ========

val commonLinuxCompilerArgs = listOf(
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

val commonLinuxLinkerArgs = listOf("-ldl", "-Wl,-z,defs", "--verbose", "-lpthread", "-lm", "-lrt", "-v", "-Wl,--build-id")

val commonMacosCompilerArgs = commonLinuxCompilerArgs + listOf("-D_XOPEN_SOURCE", "-D_DARWIN_C_SOURCE")

val asanEnv = if (hasAsan()) {
  mapOf(
    "LD_PRELOAD" to libasan!!,
    // warning: stack use after return can cause slowness on arm64
    "ASAN_OPTIONS" to "allocator_may_return_null=1:unwind_abort_on_malloc=1:use_sigaltstack=0:detect_stack_use_after_return=0:handle_segv=1:halt_on_error=0:abort_on_error=0:print_stacktrace=1:symbolize=1:suppressions=${rootDir}/gradle/sanitizers/asan.supp",
    "UBSAN_OPTIONS" to "halt_on_error=0:abort_on_error=0:print_stacktrace=1:suppressions=${rootDir}/gradle/sanitizers/ubsan.supp",
    // lsan still does not run for all tests - manually trigger on some tests
    "LSAN_OPTIONS" to "detect_leaks=0"
  )
} else {
  emptyMap()
}

val asanCompilerArgs = if (hasAsan()) {
  listOf(
    "-g",
    // Generate debug information
    "-DDEBUG",
    // Enable debug mode
    "-fPIC",
    // Position-independent code
    "-fsanitize=address",
    // AddressSanitizer for memory errors
    "-fsanitize=undefined",
    // UndefinedBehaviorSanitizer for undefined behavior
    "-fno-sanitize-recover=all",
    // Disable recovery to ensure program halts on error
    "-fsanitize=float-divide-by-zero",
    // Catch floating point division by zero
    "-fstack-protector-all",
    // Protect against stack buffer overflows
    "-fsanitize=leak",
    // LeakSanitizer to detect memory leaks
    "-fsanitize=pointer-overflow",
    // Catch pointer overflows
    "-fsanitize=return",
    // Check for uninitialized return values
    "-fsanitize=bounds",
    // BoundsSanitizer for array bounds
    "-fsanitize=alignment",
    // Catch misaligned pointer access
    "-fsanitize=object-size",
    // Catch accesses that are likely out of bounds
    "-fno-omit-frame-pointer",
    // Keep frame pointer for better debugging
    "-fno-optimize-sibling-calls"  // Disable tail call optimization for better stack traces
  )
} else {
  emptyList()
}

val asanLinkerArgs = if (hasAsan()) {
  listOf(
    "-L${file(libasan!!).parent}",
    "-lasan",
    "-lubsan",
    "-fsanitize=address",
    "-fsanitize=undefined",
    "-fno-omit-frame-pointer"  // Often recommended with sanitizers
  )
} else {
  emptyList()
}

val tsanCompilerArgs = if (hasTsan()) {
  listOf(
    "-g",
    // Generate debug information
    "-DDEBUG",
    // Enable debug mode
    "-fPIC",
    // Position-independent code
    "-fsanitize=thread",
    // ThreadSanitizer for
    "-fno-omit-frame-pointer",
    // Keep frame pointer for better debugging
    "-fno-optimize-sibling-calls"  // Disable tail call optimization for better stack traces
  )
} else {
  emptyList()
}

val tsanLinkerArgs = if (hasTsan()) {
  listOf(
    "-L${file(libtsan!!).parent}",
    "-ltsan",
    "-fsanitize=thread",
    "-fno-omit-frame-pointer"  // Often recommended with sanitizers
  )
} else {
  emptyList()
}

val tsanEnv = if (hasTsan()) {
  mapOf(
    "LD_PRELOAD" to libtsan!!,
    "TSAN_OPTIONS" to "suppressions=${rootDir}/gradle/sanitizers/tsan.supp"
  )
} else {
  emptyMap()
}

// Linux
addBuildConfiguration(
  "release", "linux", "x64",
  listOf("-O3", "-DNDEBUG", "-g") + commonLinuxCompilerArgs,
  commonLinuxLinkerArgs + listOf(
    "-Wl,-z,nodelete",
    "-static-libstdc++",
    "-static-libgcc",
    "-Wl,--exclude-libs,ALL",
    "-Wl,--gc-sections"
  )
)
addBuildConfiguration(
  "debug", "linux", "x64",
  listOf("-O0", "-g", "-DDEBUG") + commonLinuxCompilerArgs,
  commonLinuxLinkerArgs
)

addBuildConfiguration(
  "asan", "linux", "x64",
  asanCompilerArgs + commonLinuxCompilerArgs,
  commonLinuxLinkerArgs + asanLinkerArgs,
  asanEnv
)

addBuildConfiguration(
  "tsan", "linux", "x64",
  tsanCompilerArgs + commonLinuxCompilerArgs,
  commonLinuxLinkerArgs + tsanLinkerArgs,
  tsanEnv
)

addBuildConfiguration(
  "release", "linux", "arm64",
  listOf("-O3", "-DNDEBUG", "-g") + commonLinuxCompilerArgs,
  commonLinuxLinkerArgs + listOf(
    "-Wl,-z,nodelete",
    "-static-libstdc++",
    "-static-libgcc",
    "-Wl,--exclude-libs,ALL",
    "-Wl,--gc-sections"
  )
)
addBuildConfiguration(
  "debug", "linux", "arm64",
  listOf("-O0", "-g", "-DDEBUG") + commonLinuxCompilerArgs,
  commonLinuxLinkerArgs
)

addBuildConfiguration(
  "asan", "linux", "arm64",
  asanCompilerArgs + commonLinuxCompilerArgs,
  commonLinuxLinkerArgs + asanLinkerArgs,
  asanEnv
)

addBuildConfiguration(
  "tsan", "linux", "arm64",
  tsanCompilerArgs + commonLinuxCompilerArgs,
  commonLinuxLinkerArgs + tsanLinkerArgs,
  tsanEnv
)

// Fuzzer configuration (requires clang with libFuzzer support)
// Note: Fuzzers are compiled separately and linked as executables, not shared libraries.
// The fuzzer build config provides common compiler flags; actual fuzzer linking happens
// in the fuzz subproject with -fsanitize=fuzzer added at link time.
val fuzzerCompilerArgs = if (hasFuzzer()) {
  listOf(
    "-g",
    // Generate debug information for crash analysis
    "-DDEBUG",
    // Enable debug mode and assertions
    "-fPIC",
    // Position-independent code
    "-fsanitize=address",
    // AddressSanitizer for memory errors
    "-fsanitize=undefined",
    // UndefinedBehaviorSanitizer for undefined behavior
    "-fno-sanitize-recover=all",
    // Halt on sanitizer errors for reliable crash detection
    "-fno-omit-frame-pointer",
    // Keep frame pointer for stack traces
    "-fno-optimize-sibling-calls"
    // Disable tail call optimization for better stack traces
  )
} else {
  emptyList()
}

val fuzzerLinkerArgs = if (hasFuzzer()) listOf("-fsanitize=address", "-fsanitize=undefined", "-fno-omit-frame-pointer") else emptyList()

val fuzzerEnv = if (hasFuzzer()) {
  mapOf(
    "ASAN_OPTIONS" to "allocator_may_return_null=1:detect_stack_use_after_return=0:handle_segv=0:abort_on_error=1:symbolize=1:suppressions=${rootDir}/gradle/sanitizers/asan.supp",
    "UBSAN_OPTIONS" to "halt_on_error=1:abort_on_error=1:print_stacktrace=1:suppressions=${rootDir}/gradle/sanitizers/ubsan.supp"
  )
} else {
  emptyMap()
}

addBuildConfiguration(
  "fuzzer", "linux", "x64",
  fuzzerCompilerArgs + commonLinuxCompilerArgs,
  commonLinuxLinkerArgs + fuzzerLinkerArgs,
  fuzzerEnv
)

addBuildConfiguration(
  "fuzzer", "linux", "arm64",
  fuzzerCompilerArgs + commonLinuxCompilerArgs,
  commonLinuxLinkerArgs + fuzzerLinkerArgs,
  fuzzerEnv
)

// MacOS
addBuildConfiguration(
  "release", "macos", "arm64",
  commonMacosCompilerArgs + listOf("-O3", "-DNDEBUG"),
  emptyList()
)
addBuildConfiguration(
  "debug", "macos", "arm64",
  commonMacosCompilerArgs + listOf("-O0", "-g", "-DDEBUG"),
  emptyList()
)

// macOS fuzzer configuration
val fuzzerMacosCompilerArgs = if (hasFuzzer()) {
  listOf(
    "-g",
    "-DDEBUG",
    "-fPIC",
    "-fsanitize=address",
    "-fsanitize=undefined",
    "-fno-sanitize-recover=all",
    "-fno-omit-frame-pointer",
    "-fno-optimize-sibling-calls"
  )
} else {
  emptyList()
}

val fuzzerMacosLinkerArgs = if (hasFuzzer()) listOf("-fsanitize=address", "-fsanitize=undefined") else emptyList()

val fuzzerMacosEnv = if (hasFuzzer()) {
  mapOf(
    "ASAN_OPTIONS" to "allocator_may_return_null=1:detect_stack_use_after_return=0:abort_on_error=1:symbolize=1",
    "UBSAN_OPTIONS" to "halt_on_error=1:abort_on_error=1:print_stacktrace=1"
  )
} else {
  emptyMap()
}

addBuildConfiguration(
  "fuzzer", "macos", "arm64",
  fuzzerMacosCompilerArgs + commonMacosCompilerArgs,
  fuzzerMacosLinkerArgs,
  fuzzerMacosEnv
)
