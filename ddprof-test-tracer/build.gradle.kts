plugins {
  java
  id("com.datadoghq.java-conventions")
}

dependencies {
  implementation(project(mapOf("path" to ":ddprof-lib", "configuration" to "release")))
}
