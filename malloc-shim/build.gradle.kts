// Copyright 2026, Datadog, Inc

/*
 * Memory allocation interceptor for malloc debugging (Linux only).
 * Uses NativeCompileTask/NativeLinkTask from build-logic.
 */

import com.datadoghq.native.model.Platform
import com.datadoghq.native.tasks.NativeCompileTask
import com.datadoghq.native.tasks.NativeLinkTask
import com.datadoghq.native.util.PlatformUtils

plugins {
  base
  id("com.datadoghq.native-build")
}

group = "com.datadoghq"
version = "0.1"

// malloc-shim is Linux-only
val shouldBuild = PlatformUtils.currentPlatform == Platform.LINUX

if (shouldBuild) {
  val compiler = PlatformUtils.findCompiler(project)

  val compilerArgs = listOf(
    "-O3",
    "-fno-omit-frame-pointer",
    "-fvisibility=hidden",
    "-std=c++17",
    "-DPROFILER_VERSION=\"${project.version}\"",
    "-fPIC"
  )

  // Compile task
  val compileTask = tasks.register<NativeCompileTask>("compileLib") {
    onlyIf { shouldBuild && !project.hasProperty("skip-native") }
    group = "build"
    description = "Compile the malloc-shim library"

    this.compiler.set(compiler)
    this.compilerArgs.set(compilerArgs)
    sources.from(file("src/main/cpp/malloc_intercept.cpp"))
    includes.from(file("src/main/public"))
    objectFileDir.set(file("${layout.buildDirectory.get()}/obj/lib"))
  }

  // Link task
  val libFile = file("${layout.buildDirectory.get()}/lib/libdebug.so")
  val linkTask = tasks.register<NativeLinkTask>("linkLib") {
    onlyIf { shouldBuild && !project.hasProperty("skip-native") }
    dependsOn(compileTask)
    group = "build"
    description = "Link the malloc-shim shared library"

    linker.set(compiler)
    linkerArgs.set(listOf("-ldl"))
    objectFiles.from(fileTree("${layout.buildDirectory.get()}/obj/lib") { include("*.o") })
    outputFile.set(libFile)
  }

  // Wire linkLib into the standard assemble lifecycle
  tasks.named("assemble") {
    dependsOn(linkTask)
  }
}
