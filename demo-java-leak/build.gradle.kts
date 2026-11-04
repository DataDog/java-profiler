/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

plugins {
  java
  application
}

// This module deliberately does not apply `com.datadoghq.java-conventions`: that plugin
// force-appends `--release 8` to every JavaCompile task (JavaConventionsPlugin.kt), while
// this app targets `--release 21` so it builds under the repo's JDK 21 Gradle and runs on
// the JDK 27 container image. Spotless still covers the module: the root build.gradle.kts
// applies the spotless convention to all projects. See doc/architecture/DemoJavaLeakApp.md.
tasks.withType<JavaCompile>().configureEach {
  options.release.set(21)
}

application {
  mainClass.set("com.datadoghq.demo.leak.Main")
}

// Gradle's application plugin would set Main-Class in the jar manifest from `mainClass`;
// declare it explicitly so the runnable-artifact contract does not depend on plugin wiring.
tasks.named<Jar>("jar") {
  manifest {
    attributes("Main-Class" to application.mainClass.get())
  }
}

tasks.test {
  useJUnitPlatform()
  // Tests observe the same heap budget as the containerized app (-Xmx512m), so the
  // leak-trend test in this module samples occupancy under the production watermark.
  maxHeapSize = "512m"
}

dependencies {
  testImplementation(libs.junit.api)
  testRuntimeOnly(libs.junit.engine)
  // The JUnit Platform launcher the Gradle test worker forks with; normally supplied by
  // the java-conventions plugin's `testing` bundle, which this module does not apply.
  testRuntimeOnly(libs.junit.platform.launcher)
}
