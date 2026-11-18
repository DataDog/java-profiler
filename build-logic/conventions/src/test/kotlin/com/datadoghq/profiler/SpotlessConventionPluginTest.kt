// Copyright 2026, Datadog, Inc.

package com.datadoghq.profiler

import java.io.DataInputStream
import java.io.File
import org.gradle.testkit.runner.BuildResult
import org.gradle.testkit.runner.GradleRunner
import org.gradle.testkit.runner.TaskOutcome
import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Assertions.assertNotEquals
import org.junit.jupiter.api.Assertions.assertTrue
import org.junit.jupiter.api.Test
import org.junit.jupiter.api.io.TempDir

class SpotlessConventionPluginTest {
    @TempDir
    lateinit var projectDir: File

    @Test
    fun `Java applied after the convention registers Java formatting tasks`() {
        fixture("com.datadoghq.spotless-convention", "java")
        write("src/main/java/example/Example.java", "package example;\n\npublic class Example {}\n")

        val result = run("spotlessJavaCheck")

        assertEquals(TaskOutcome.SUCCESS, result.task(":spotlessJavaCheck")?.outcome)
    }

    @Test
    fun `Java check rejects malformed formatting and fails the aggregate check`() {
        fixture("com.datadoghq.spotless-convention", "java")
        val source = write("src/main/java/example/Example.java", unformattedJava)

        for (task in listOf("spotlessJavaCheck", "spotlessCheck", "check")) {
            val result = run(task, expectFailure = true)

            assertEquals(TaskOutcome.FAILED, result.task(":spotlessJavaCheck")?.outcome)
            assertTrue(result.output.contains("The following files had format violations"), result.output)
            assertTrue(result.output.contains("Example.java"), result.output)
            assertEquals(unformattedJava, source.readText())
        }
    }

    @Test
    fun `Java applied before the convention formats and compiles Java 8 bytecode`() {
        fixture("java", "com.datadoghq.spotless-convention", "com.datadoghq.java-conventions")
        val source = write("src/main/java/example/Example.java", unformattedJava)

        val applied = run("spotlessJavaApply")
        assertEquals(TaskOutcome.SUCCESS, applied.task(":spotlessJavaApply")?.outcome)
        val formatted = source.readText()
        assertNotEquals(unformattedJava, formatted)
        assertTrue(formatted.contains("public class Example {"), formatted)
        assertTrue(formatted.contains("Supplier<String> supplier = () -> \"hello\";"), formatted)

        val checked = run("check", "compileJava")
        assertEquals(TaskOutcome.SUCCESS, checked.task(":spotlessJavaCheck")?.outcome)
        assertEquals(TaskOutcome.SUCCESS, checked.task(":spotlessCheck")?.outcome)
        assertEquals(TaskOutcome.SUCCESS, checked.task(":check")?.outcome)
        assertEquals(TaskOutcome.SUCCESS, checked.task(":compileJava")?.outcome)
        assertEquals(formatted, source.readText())

        DataInputStream(projectDir.resolve("build/classes/java/main/example/Example.class").inputStream()).use {
            assertEquals(0xCAFEBABE.toInt(), it.readInt())
            it.readUnsignedShort()
            assertEquals(52, it.readUnsignedShort(), "Java 8 class file major version")
        }
    }

    /** Use the test worker's JDK for TestKit as well, so a matrix run cannot reuse another JDK. */
    private fun fixture(vararg plugins: String) {
        val javaHome = File(System.getProperty("java.home")).canonicalPath
        System.getenv("JAVA_HOME")?.let { assertEquals(File(it).canonicalPath, javaHome) }
        println("Test worker: java.home=$javaHome java.version=${System.getProperty("java.version")}")
        write("settings.gradle", "rootProject.name = 'spotless-convention-test'\n")
        write("gradle/libs.versions.toml", "[versions]\nlz4 = \"1.10.4\"\n")
        write(
            "build.gradle",
            """
            plugins {
                id 'base'
                ${plugins.joinToString("\n") { "id '$it'" }}
            }
            repositories { mavenCentral() }
            println('Fixture JVM: java.home=' + new File(System.getProperty('java.home')).canonicalPath +
                ' java.version=' + System.getProperty('java.version'))
            """.trimIndent() + "\n"
        )
    }

    private fun write(path: String, content: String): File = projectDir.resolve(path).apply {
        parentFile.mkdirs()
        writeText(content)
    }

    private fun run(vararg tasks: String, expectFailure: Boolean = false): BuildResult {
        val javaHome = File(System.getProperty("java.home")).canonicalPath
        val runner = GradleRunner.create()
            .withProjectDir(projectDir)
            .withPluginClasspath()
            .withArguments(
                *tasks, "--stacktrace", "--max-workers=2", "--no-build-cache",
                "-Dorg.gradle.java.home=$javaHome"
            )
        val result = if (expectFailure) runner.buildAndFail() else runner.build()
        val runtime = "Fixture JVM: java.home=$javaHome java.version=${System.getProperty("java.version")}"
        assertTrue(result.output.contains(runtime), result.output)
        println(runtime)
        return result
    }

    private val unformattedJava = """
        package example;
        import java.util.function.Supplier;
        public class Example{public String message(){Supplier<String> supplier=()->"hello";return supplier.get();}}
    """.trimIndent() + "\n"
}
