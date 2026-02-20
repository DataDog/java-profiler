/*
 * Native test helper libraries (JNI helpers for Java tests).
 */

import com.datadoghq.native.model.Platform
import com.datadoghq.native.util.PlatformUtils

plugins {
  id("com.datadoghq.simple-native-lib")
}

description = "Native test helper libraries (JNI helpers for Java tests)"

simpleNativeLib {
  libraryName.set("ddproftest")

  // Use C compiler (not C++) for .c files
  compiler.set(if (PlatformUtils.currentPlatform == Platform.MACOS) "clang" else "gcc")
  linker.set(if (PlatformUtils.currentPlatform == Platform.MACOS) "clang" else "gcc")

  includeJni.set(true)

  // Note: No optimization (-O0) to prevent inlining of static functions like do_primes()
  // which need to be visible in stack traces for profiler testing
  compilerArgs.set(
    when (PlatformUtils.currentPlatform) {
      Platform.LINUX -> listOf("-fPIC")
      Platform.MACOS -> emptyList()
    },
  )

  linkerArgs.set(
    when (PlatformUtils.currentPlatform) {
      Platform.LINUX -> listOf("-shared", "-Wl,--build-id")
      Platform.MACOS -> listOf("-dynamiclib")
    },
  )

  // Create consumable configurations for other projects to depend on
  createConfigurations.set(true)
}
