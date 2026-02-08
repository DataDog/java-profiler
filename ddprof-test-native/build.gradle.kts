// Copyright 2026, Datadog, Inc

import com.datadoghq.native.model.Platform
import com.datadoghq.native.tasks.NativeCompileTask
import com.datadoghq.native.tasks.NativeLinkTask
import com.datadoghq.native.util.PlatformUtils

plugins {
    id("com.datadoghq.native-build")
}

description = "Native test helper libraries (JNI helpers for Java tests, potentially linkable by gtests)"

val libraryName = "ddproftest"
val objectDir = layout.buildDirectory.dir("obj")
val libDir = layout.buildDirectory.dir("lib")

// Compile C sources (JNI helpers)
val compileLib = tasks.register<NativeCompileTask>("compileLib") {
    description = "Compiles native test helper sources"
    group = "build"

    // Use C compiler (not C++) for .c files
    compiler.set(if (PlatformUtils.currentPlatform == Platform.MACOS) "clang" else "gcc")
    sources.from(fileTree("src/main/cpp") { include("**/*.c") })
    includes.from(PlatformUtils.jniIncludePaths())
    objectFileDir.set(objectDir)

    // Note: No optimization (-O0) to prevent inlining of static functions like do_primes()
    // which need to be visible in stack traces for profiler testing
    compilerArgs.set(
        when (PlatformUtils.currentPlatform) {
            Platform.LINUX -> listOf("-fPIC")
            Platform.MACOS -> emptyList()
        }
    )
}

// Link shared library
val linkLib = tasks.register<NativeLinkTask>("linkLib") {
    description = "Links native test helper library"
    group = "build"
    dependsOn(compileLib)

    linker.set(if (PlatformUtils.currentPlatform == Platform.MACOS) "clang" else "gcc")
    objectFiles.from(compileLib.flatMap { it.objectFileDir.map { dir -> fileTree(dir) { include("*.o") } } })
    outputFile.set(libDir.map { it.file("lib${libraryName}.${PlatformUtils.sharedLibExtension()}") })

    linkerArgs.set(
        when (PlatformUtils.currentPlatform) {
            Platform.LINUX -> listOf("-shared", "-Wl,--build-id")
            Platform.MACOS -> listOf("-dynamiclib")
        }
    )
}

// Wire into standard lifecycle
tasks.named("assemble") {
    dependsOn(linkLib)
}

// === Consumable Configurations ===
// These allow other projects to depend on different artifacts

// 1. Runtime library - for Java tests (System.loadLibrary) and gtest runtime loading
val nativeLib by configurations.creating {
    isCanBeConsumed = true
    isCanBeResolved = false
    description = "Native shared library for runtime loading"

    outgoing.artifact(linkLib.flatMap { it.outputFile }) {
        type = "native-lib"
    }
}

// 2. Object files - for gtest linking (future use)
val nativeObjects by configurations.creating {
    isCanBeConsumed = true
    isCanBeResolved = false
    description = "Object files for static linking into gtest executables"

    outgoing.artifact(compileLib.flatMap { it.objectFileDir }) {
        type = "native-objects"
    }
}

// 3. Library directory - convenient for setting LD_LIBRARY_PATH / java.library.path
val nativeLibDir by configurations.creating {
    isCanBeConsumed = true
    isCanBeResolved = false
    description = "Directory containing native library (for library path configuration)"

    outgoing.artifact(libDir) {
        type = "native-lib-dir"
    }
}

// 4. Include headers - for gtest compilation (future use)
val nativeHeaders by configurations.creating {
    isCanBeConsumed = true
    isCanBeResolved = false
    description = "Header files for compilation"

    outgoing.artifact(file("src/main/cpp")) {
        type = "native-headers"
    }
}
