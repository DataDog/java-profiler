// Standalone reproducer for java-profiler + wasmtime crash.
// Intentionally does NOT apply com.datadoghq.java-conventions — that plugin
// enforces --release 8, but wasmtime-java requires Java 11+ at runtime.
plugins {
  java
  application
}

java {
  toolchain {
    languageVersion.set(JavaLanguageVersion.of(26))
  }
}

dependencies {
  implementation(project(mapOf("path" to ":ddprof-lib", "configuration" to "debug")))
  implementation(libs.wasmtime.java)
}

application {
  mainClass.set("com.datadoghq.profiler.wasmtime.WasmtimeReproducer")
}

tasks.named<Jar>("jar") {
  manifest {
    attributes("Main-Class" to "com.datadoghq.profiler.wasmtime.WasmtimeReproducer")
  }
  // Bundle all runtime dependencies into a fat jar.
  // Preserve native libraries (.so, .dylib) — do NOT use zip64MergeStrategy.EXCLUDE on them.
  from(configurations.runtimeClasspath.get().map { if (it.isDirectory) it else zipTree(it) })
  duplicatesStrategy = DuplicatesStrategy.EXCLUDE
  archiveFileName.set("wasmtime-reproducer.jar")
}
