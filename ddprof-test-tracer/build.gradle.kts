plugins {
  java
}

repositories {
  mavenCentral()
}

dependencies {
  implementation(project(mapOf("path" to ":ddprof-lib", "configuration" to "release")))
}

tasks.withType<JavaCompile>().configureEach {
  options.compilerArgs.addAll(listOf("--release", "8"))
}
