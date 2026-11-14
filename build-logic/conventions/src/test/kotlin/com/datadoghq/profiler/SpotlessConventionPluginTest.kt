// Copyright 2026, Datadog, Inc.
package com.datadoghq.profiler

import java.io.File
import java.nio.file.Files
import java.nio.file.Path
import org.gradle.testkit.runner.BuildResult
import org.gradle.testkit.runner.GradleRunner
import org.gradle.testkit.runner.TaskOutcome
import org.junit.jupiter.api.Assertions.assertArrayEquals
import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Assertions.assertFalse
import org.junit.jupiter.api.Assertions.assertNotEquals
import org.junit.jupiter.api.Assertions.assertTrue
import org.junit.jupiter.api.Test
import org.junit.jupiter.api.io.TempDir

/** Exercises the production convention with real Gradle tasks and formatter dependencies. */
class SpotlessConventionPluginTest {
  @TempDir lateinit var root: Path

  @Test
  fun `convention before Java registers the real formatter`() {
    singleProject(javaFirst = false)
    registeredJavaTasks()
    write("src/main/java/Dirty.java", "class Dirty{int x=1;}\n")
    formattingFailure(run("spotlessJavaCheck", fails = true))
  }

  @Test
  fun `Java before convention registers the real formatter`() {
    singleProject(javaFirst = true)
    registeredJavaTasks()
    write("src/main/java/Dirty.java", "class Dirty{int x=1;}\n")
    formattingFailure(run("spotlessJavaCheck", fails = true))
  }

  @Test
  fun `root application before child Java does not configure non Java projects`() {
    settings("include 'child', 'plain'")
    write("build.gradle", """
      plugins {
        id 'base'
        id 'com.datadoghq.spotless-convention'
      }
      allprojects {
        apply plugin: 'base'
        apply plugin: 'com.datadoghq.spotless-convention'
      }
    """.trimIndent() + "\n")
    write("child/build.gradle", "apply plugin: 'java'\n")
    write("plain/build.gradle", "")
    write("child/src/main/java/Dirty.java", "class Dirty{int x=1;}\n")
    write("plain/src/main/java/Untargeted.java", "not Java\n")
    registeredJavaTasks(":child:")
    assertFalse(run(":plain:tasks", "--all").output.contains("spotlessJava"))
    formattingFailure(run(":child:spotlessJavaCheck", fails = true), ":child:spotlessJavaCheck")
    assertEquals(TaskOutcome.SUCCESS, run(":child:spotlessJavaApply").task(":child:spotlessJavaApply")?.outcome)
    assertEquals(TaskOutcome.SUCCESS, run(":child:spotlessJavaCheck").task(":child:spotlessJavaCheck")?.outcome)
  }

  @Test
  fun `check rejects dirty Java apply fixes imports and compilation stays Java 8`() {
    singleProject(javaFirst = false, javaConventions = true)
    write("src/main/java/Java8Fixture.java", JAVA8)
    val before = read("src/main/java/Java8Fixture.java")
    for (task in listOf("spotlessJavaCheck", "spotlessCheck", "check")) {
      formattingFailure(run(task, fails = true))
      assertEquals(before, read("src/main/java/Java8Fixture.java"))
    }
    assertEquals(TaskOutcome.SUCCESS, run("spotlessJavaApply").task(":spotlessJavaApply")?.outcome)
    val formatted = read("src/main/java/Java8Fixture.java")
    assertNotEquals(before, formatted)
    assertEquals(
      listOf(
        "import static java.util.Collections.singletonList;",
        "import java.util.Arrays;",
        "import java.util.List;",
        "import java.util.function.Function;",
        "import java.util.function.Supplier;"
      ),
      formatted.lineSequence().filter { it.startsWith("import ") }.toList()
    )
    assertTrue(formatted.contains("singletonList;\n\nimport java.util.Arrays;"), formatted)
    assertFalse(formatted.contains("java.util.Map"), formatted)
    assertTrue(formatted.contains("String::trim"), formatted)
    assertTrue(formatted.contains("() ->"), formatted)
    assertTrue(formatted.contains("default String name()"), formatted)
    val checked = run("check", "verifyJava8Options")
    assertEquals(TaskOutcome.SUCCESS, checked.task(":spotlessJavaCheck")?.outcome)
    assertEquals(TaskOutcome.SUCCESS, checked.task(":spotlessCheck")?.outcome)
    assertEquals(TaskOutcome.SUCCESS, checked.task(":check")?.outcome)
    assertEquals(TaskOutcome.SUCCESS, checked.task(":compileJava")?.outcome)
    assertEquals(TaskOutcome.SUCCESS, checked.task(":verifyJava8Options")?.outcome)
    val classfile = Files.readAllBytes(root.resolve("build/classes/java/main/Java8Fixture.class"))
    assertTrue(classfile.size > 8)
    assertEquals(listOf(0xca, 0xfe, 0xba, 0xbe), classfile.take(4).map { it.toInt() and 0xff })
    assertEquals(52, ((classfile[6].toInt() and 0xff) shl 8) or (classfile[7].toInt() and 0xff))
    val firstApply = Files.readAllBytes(root.resolve("src/main/java/Java8Fixture.java"))
    assertEquals(TaskOutcome.SUCCESS, run("spotlessJavaApply").task(":spotlessJavaApply")?.outcome)
    assertArrayEquals(firstApply, Files.readAllBytes(root.resolve("src/main/java/Java8Fixture.java")))
  }

  @Test
  fun `both check and apply propagate a malformed source diagnostic`() {
    singleProject(javaFirst = true)
    val broken = "class Broken { void method( { }\n"
    write("src/main/java/Broken.java", broken)
    for (task in listOf("spotlessJavaCheck", "spotlessJavaApply")) {
      val failed = run(task, fails = true)
      assertFormatterTaskFailed(failed, task)
      assertTrue(failed.output.contains("Broken.java"), failed.output)
      assertTrue(failed.output.contains("FormatterException"), failed.output)
      assertNoInfrastructureFailure(failed)
      assertEquals(broken, read("src/main/java/Broken.java"))
    }
  }

  @Test
  fun `invalid formatter configuration fails check and apply without changing source`() {
    singleProject(javaFirst = true)
    write("build.gradle", read("build.gradle") + """
      spotless {
        java {
          replaceRegex('invalid-regex', '[', '')
        }
      }
    """.trimIndent() + "\n")
    val source = "class Clean {}\n"
    write("src/main/java/Clean.java", source)
    for (task in listOf("spotlessJavaCheck", "spotlessJavaApply")) {
      val failed = run(task, fails = true)
      assertFormatterTaskFailed(failed, task)
      assertTrue(failed.output.contains("PatternSyntaxException"), failed.output)
      assertTrue(failed.output.contains("Unclosed character class"), failed.output)
      assertNoInfrastructureFailure(failed)
      assertEquals(source, read("src/main/java/Clean.java"))
    }
  }

  @Test
  fun `resource exclusion and explicit toggle keep their existing scope`() {
    singleProject(javaFirst = false)
    val excluded = "this is deliberately not valid Java\n"
    val disabled = "  // spotless:off\n  int    retained =  7;\n  // spotless:on\n"
    write("src/test/resources/nested/Broken.java", excluded)
    write("src/main/java/Toggle.java", "class Toggle {\n${disabled}int x=1;\n}\n")
    write("outside-src/Untargeted.java", excluded)
    assertEquals(TaskOutcome.SUCCESS, run("spotlessJavaApply").task(":spotlessJavaApply")?.outcome)
    assertTrue(read("src/main/java/Toggle.java").contains(disabled))
    assertTrue(read("src/main/java/Toggle.java").contains("int x = 1;"))
    assertEquals(excluded, read("src/test/resources/nested/Broken.java"))
    assertEquals(excluded, read("outside-src/Untargeted.java"))
    assertEquals(TaskOutcome.SUCCESS, run("spotlessJavaCheck").task(":spotlessJavaCheck")?.outcome)
    write("src/custom/java/IncludedBroken.java", excluded)
    val failed = run("spotlessJavaCheck", fails = true)
    assertFormatterTaskFailed(failed, "spotlessJavaCheck")
    assertTrue(failed.output.contains("IncludedBroken.java"), failed.output)
    assertTrue(failed.output.contains("FormatterException"), failed.output)
    assertNoInfrastructureFailure(failed)
  }

  /** Applies the actual Java convention when checking the release target, not a copied compiler setup. */
  private fun singleProject(javaFirst: Boolean, javaConventions: Boolean = false) {
    settings()
    val plugins = if (javaFirst) {
      "id 'java'\n  id 'com.datadoghq.spotless-convention'"
    } else {
      "id 'base'\n  id 'com.datadoghq.spotless-convention'\n  id 'java'"
    }
    val compilation = if (javaConventions) """
      apply plugin: 'com.datadoghq.java-conventions'
      tasks.register('verifyJava8Options') {
        dependsOn tasks.named('compileJava')
        doLast {
          def args = tasks.named('compileJava').get().options.compilerArgs
          def index = args.indexOf('--release')
          assert index >= 0 && args[index + 1] == '8' : args
        }
      }
    """.trimIndent() else ""
    write("build.gradle", "plugins {\n  $plugins\n}\n$compilation\n")
  }

  private fun settings(extra: String = "") {
    write("settings.gradle", """
      rootProject.name = 'formatter-fixture'
      dependencyResolutionManagement {
        repositories { mavenCentral() }
        versionCatalogs { libs { version('lz4', '1.12.0') } }
      }
      $extra
    """.trimIndent().trimEnd() + "\n")
  }

  /** Task discovery must pass before formatting, so registration RED cannot be a formatter failure. */
  private fun registeredJavaTasks(prefix: String = ":") {
    val output = run("${prefix}tasks", "--all").output
    for (name in listOf("spotlessJava", "spotlessJavaCheck", "spotlessJavaApply")) {
      assertTrue(Regex("(?m)^$name(?:\\s|$)").containsMatchIn(output), output)
    }
  }

  /** Optional cache/offline controls let the same real plugin tests run in isolated matrix cells. */
  private fun run(vararg arguments: String, fails: Boolean = false): BuildResult {
    val javaHome = File(System.getProperty("java.home")).canonicalPath
    System.getenv("JAVA_HOME")?.let { assertEquals(File(it).canonicalPath, javaHome) }
    val expected = System.getenv("FORMATTER_EXPECTED_BUILD_JVM") ?: System.getProperty("java.specification.version")
    require(expected.toInt() >= 21) { "The formatter requires a build JDK of 21 or newer" }
    val testKitDir = System.getenv("FORMATTER_TESTKIT_DIR")
    val offline = if (System.getenv("FORMATTER_TESTKIT_OFFLINE") == "true") listOf("--offline") else emptyList()
    write("jvm-receipt.init.gradle", """
      gradle.settingsEvaluated {
        println('FORMATTER_BUILD_JVM=' + System.getProperty('java.specification.version'))
        println('FORMATTER_JAVA_HOME=' + new File(System.getProperty('java.home')).canonicalPath)
        println('FORMATTER_GRADLE=' + gradle.gradleVersion)
        println('FORMATTER_GRADLE_USER_HOME=' + gradle.gradleUserHomeDir)
      }
    """.trimIndent() + "\n")
    val runner = GradleRunner.create()
      .withProjectDir(root.toFile())
      .withPluginClasspath()
      .forwardOutput()
      .withArguments(arguments.toList() + offline + listOf(
        "--stacktrace", "--no-build-cache", "--rerun-tasks", "--no-configuration-cache",
        "--max-workers=1", "--init-script", "jvm-receipt.init.gradle", "-Dorg.gradle.java.home=$javaHome"
      ))
    if (testKitDir != null) runner.withTestKitDir(File(testKitDir))
    val result = if (fails) runner.buildAndFail() else runner.build()
    assertTrue(result.output.lineSequence().any { it == "FORMATTER_BUILD_JVM=$expected" }, result.output)
    assertTrue(result.output.lineSequence().any { it == "FORMATTER_JAVA_HOME=$javaHome" }, result.output)
    return result
  }

  private fun formattingFailure(result: BuildResult, task: String = ":spotlessJavaCheck") {
    assertEquals(TaskOutcome.FAILED, result.task(task)?.outcome)
    assertTrue(result.output.contains("The following files had format violations:"), result.output)
    assertNoInfrastructureFailure(result)
  }

  /** A parser failure may stop the shared format task before its requested check/apply consumer. */
  private fun assertFormatterTaskFailed(result: BuildResult, requestedTask: String) {
    assertTrue(result.tasks.any {
      it.outcome == TaskOutcome.FAILED && it.path in setOf(":spotlessJava", ":$requestedTask")
    }, result.output)
  }

  private fun assertNoInfrastructureFailure(result: BuildResult) {
    for (text in listOf(
      "NoSuchMethodError", "UnsupportedClassVersionError", "requires google-java-format", "Could not resolve"
    )) {
      assertFalse(result.output.contains(text), result.output)
    }
  }

  private fun write(relative: String, body: String) {
    val path = root.resolve(relative)
    Files.createDirectories(path.parent)
    Files.write(path, body.toByteArray(Charsets.UTF_8))
  }

  private fun read(relative: String): String = String(Files.readAllBytes(root.resolve(relative)), Charsets.UTF_8)

  companion object {
    private val JAVA8 = """
      import java.util.function.Supplier;
      import java.util.Map;
      import java.util.List;
      import static java.util.Collections.singletonList;
      import java.util.function.Function;
      import java.util.Arrays;
      import java.util.List;
      interface Named{default String name(){return "x";}}
      public class Java8Fixture implements Named{
      public List<String> values(){Function<String,String> trim=String::trim;Supplier<List<String>> supplier=()->Arrays.asList(" a ",name());return singletonList(trim.apply(supplier.get().get(0)));}
      }
    """.trimIndent() + "\n"
  }
}
