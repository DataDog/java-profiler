
package com.datadoghq.profiler

import com.diffplug.gradle.spotless.SpotlessExtension
import org.gradle.api.Plugin
import org.gradle.api.Project

/**
 * Convention plugin that configures Spotless code formatting for all project types.
 * Supports Java, Groovy, Kotlin, Scala, C++, and miscellaneous file formatting.
 */
class SpotlessConventionPlugin : Plugin<Project> {
  override fun apply(project: Project) {
    project.pluginManager.apply("com.diffplug.spotless")

    val configPath = project.rootProject.file("gradle").absolutePath
    val spotless = project.extensions.getByType(SpotlessExtension::class.java)

    // Java formatting (Google Java Format 1.7 - last version supporting Java 8)
    if (project.plugins.hasPlugin("java")) {
      spotless.java {
        toggleOffOn()
        target("src/**/*.java")
        targetExclude("src/test/resources/**")
        googleJavaFormat("1.7")
      }
    }

    // Groovy Gradle files
    spotless.groovyGradle {
      toggleOffOn()
      target("*.gradle", "gradle/**/*.gradle")
      greclipse().configFile("$configPath/enforcement/spotless-groovy.properties")
    }

    // Kotlin Gradle files
    spotless.kotlinGradle {
      toggleOffOn()
      target("*.gradle.kts")
      // ktlint 0.41.0 is compatible with older Kotlin versions in this build
      ktlint("0.41.0").userData(
        mapOf(
          "indent_size" to "2",
          "continuation_indent_size" to "2"
        )
      )
    }

    // Groovy source files
    if (project.plugins.hasPlugin("groovy")) {
      val skipJavaExclude = project.findProperty("groovySkipJavaExclude") as? Boolean ?: false
      spotless.groovy {
        toggleOffOn()
        if (!skipJavaExclude) {
          excludeJava()
        }
        greclipse().configFile("$configPath/enforcement/spotless-groovy.properties")
      }
    }

    // Scala source files
    if (project.plugins.hasPlugin("scala")) {
      spotless.scala {
        toggleOffOn()
        scalafmt("2.7.5").configFile("$configPath/enforcement/spotless-scalafmt.conf")
      }
    }

    // TODO: Enable C++ formatting in a follow-up PR
    // This requires reformatting all C/C++ source files which would pollute this PR.
    //
    // project.pluginManager.withPlugin("com.datadoghq.native-build") {
    //   val clangVersion = PlatformUtils.clangFormatVersion()
    //   if (clangVersion != null) {
    //     spotless.cpp {
    //       target("src/main/cpp/**")
    //       clangFormat(clangVersion).style("file")
    //     }
    //   }
    // }

    // Miscellaneous files (markdown, shell scripts, etc.)
    spotless.format("misc") {
      toggleOffOn()
      target(
        ".gitignore",
        "*.md",
        ".github/**/*.md",
        "src/**/*.md",
        "application/**/*.md",
        "*.sh",
        "tooling/*.sh",
        ".circleci/*.sh"
      )
      indentWithSpaces()
      trimTrailingWhitespace()
      endWithNewline()
    }

    // Wire spotlessCheck into the check task
    project.tasks.named("check") {
      dependsOn("spotlessCheck")
    }
  }
}
