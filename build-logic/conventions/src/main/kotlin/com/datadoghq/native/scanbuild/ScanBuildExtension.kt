// Copyright 2026, Datadog, Inc

package com.datadoghq.native.scanbuild

import org.gradle.api.Project
import org.gradle.api.file.DirectoryProperty
import org.gradle.api.provider.ListProperty
import org.gradle.api.provider.Property
import javax.inject.Inject

/**
 * Extension for configuring the scan-build static analysis task.
 */
abstract class ScanBuildExtension @Inject constructor(project: Project) {
    /**
     * Directory containing the Makefile for scan-build.
     * Default: src/test/make
     */
    abstract val makefileDir: DirectoryProperty

    /**
     * Output directory for scan-build reports.
     * Default: build/reports/scan-build
     */
    abstract val outputDir: DirectoryProperty

    /**
     * Path to the clang analyzer to use.
     * Default: /usr/bin/clang++
     */
    abstract val analyzer: Property<String>

    /**
     * Number of parallel jobs for make.
     * Default: 4
     */
    abstract val parallelJobs: Property<Int>

    /**
     * Make targets to build.
     * Default: ["all"]
     */
    abstract val makeTargets: ListProperty<String>

    init {
        makefileDir.convention(project.layout.projectDirectory.dir("src/test/make"))
        outputDir.convention(project.layout.buildDirectory.dir("reports/scan-build"))
        analyzer.convention("/usr/bin/clang++")
        parallelJobs.convention(4)
        makeTargets.convention(listOf("all"))
    }
}
