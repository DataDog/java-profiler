// Copyright 2026, Datadog, Inc

/*
 * Memory allocation interceptor for malloc debugging (Linux only).
 */

import com.datadoghq.native.model.Platform
import com.datadoghq.native.util.PlatformUtils

plugins {
  base
  id("com.datadoghq.simple-native-lib")
}

group = "com.datadoghq"
version = "0.1"

simpleNativeLib {
  // malloc-shim is Linux-only
  enabled.set(PlatformUtils.currentPlatform == Platform.LINUX)

  libraryName.set("debug")
  sourceDir.set(file("src/main/cpp"))
  includeDirs.set(listOf(file("src/main/public").absolutePath))

  compilerArgs.set(
    listOf(
      "-O3",
      "-fno-omit-frame-pointer",
      "-fvisibility=hidden",
      "-std=c++17",
      "-DPROFILER_VERSION=\"${project.version}\"",
      "-fPIC"
    )
  )

  linkerArgs.set(listOf("-ldl"))
}
