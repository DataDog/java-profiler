// Copyright 2026, Datadog, Inc.

package com.datadoghq.native.util

import org.gradle.testkit.runner.BuildResult
import org.gradle.testkit.runner.GradleRunner
import org.gradle.testkit.runner.TaskOutcome
import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Assertions.assertNotNull
import org.junit.jupiter.api.Assertions.assertNull
import org.junit.jupiter.api.Assertions.assertTrue
import org.junit.jupiter.api.Test
import org.junit.jupiter.api.io.TempDir
import java.io.File

/** Runs [NativeLibJarCheck.register] in a fixture build whose `jar` task stands in for `jmhJar`. */
class NativeLibJarCheckWiringTest {

    @TempDir
    lateinit var dir: File

    private val lib = "META-INF/native-libs/linux-x64/libjavaProfiler.so"

    private fun fixture(duplicate: Boolean, jarEnabled: Boolean = true, jarFails: Boolean = false) {
        write("settings.gradle.kts", "rootProject.name = \"wiring-test\"\n")
        write("a/$lib", "release")
        if (duplicate) write("b/$lib", "debug")
        write(
            "build.gradle.kts",
            """
            import com.datadoghq.native.util.NativeLibJarCheck
            plugins { java; id("com.datadoghq.native-build") apply false }
            tasks.jar {
              from("a")${if (duplicate) "\n  from(\"b\")" else ""}
              duplicatesStrategy = DuplicatesStrategy.INCLUDE
              isEnabled = $jarEnabled
              ${if (jarFails) "doFirst { throw GradleException(\"jar broke\") }" else ""}
            }
            tasks.register("bench") { doLast { println("bench ran") } }
            NativeLibJarCheck.register(project, tasks.jar, "linux-x64", "bench")
            """.trimIndent() + "\n"
        )
    }

    private fun write(path: String, content: String) {
        dir.resolve(path).apply { parentFile.mkdirs(); writeText(content) }
    }

    private fun run(vararg tasks: String, fail: Boolean): BuildResult {
        val runner = GradleRunner.create()
            .withProjectDir(dir)
            .withPluginClasspath()
            .withArguments(*tasks, "--stacktrace", "--max-workers=2", "--no-build-cache")
        return if (fail) runner.buildAndFail() else runner.build()
    }

    private fun outcome(r: BuildResult, task: String) = r.task(":$task")?.outcome

    @Test
    fun `valid jar is checked before the guarded task runs`() {
        fixture(duplicate = false)
        val r = run("bench", fail = false)
        val order = r.tasks.map { it.path }
        assertEquals(TaskOutcome.SUCCESS, outcome(r, "verifyJmhJarNativeLibs"))
        assertEquals(TaskOutcome.SUCCESS, outcome(r, "bench"))
        assertTrue(order.indexOf(":verifyJmhJarNativeLibs") < order.indexOf(":bench"), order.toString())
    }

    @Test
    fun `duplicate library fails the guarded task before it runs`() {
        fixture(duplicate = true)
        val r = run("bench", fail = true)
        assertEquals(TaskOutcome.FAILED, outcome(r, "verifyJmhJarNativeLibs"))
        assertNull(outcome(r, "bench"), "bench must not run")
        assertTrue(r.output.contains("found 2"), r.output)
    }

    @Test
    fun `jar built alone is checked by the finalizer`() {
        fixture(duplicate = true)
        val r = run("jar", fail = true)
        assertEquals(TaskOutcome.SUCCESS, outcome(r, "jar"))
        assertEquals(TaskOutcome.FAILED, outcome(r, "verifyJmhJarNativeLibs"))
    }

    @Test
    fun `failed jar build reports its own error and does not run the check`() {
        fixture(duplicate = false, jarFails = true)
        val r = run("jar", fail = true)
        assertEquals(TaskOutcome.FAILED, outcome(r, "jar"))
        assertNull(outcome(r, "verifyJmhJarNativeLibs"))
        assertTrue(r.output.contains("jar broke"), r.output)
    }

    @Test
    fun `missing jar fails the check instead of skipping it`() {
        fixture(duplicate = false, jarEnabled = false)
        val r = run("bench", fail = true)
        assertNotNull(r.task(":verifyJmhJarNativeLibs"))
        assertTrue(r.task(":verifyJmhJarNativeLibs")?.outcome != TaskOutcome.SKIPPED)
        assertNull(outcome(r, "bench"))
    }
}
