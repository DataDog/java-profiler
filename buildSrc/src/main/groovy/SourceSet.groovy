/*
 * Copyright 2026, Datadog, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import org.gradle.api.Named
import org.gradle.api.file.ConfigurableFileCollection
import org.gradle.api.model.ObjectFactory
import org.gradle.api.provider.ListProperty
import org.gradle.api.provider.Property
import org.gradle.api.tasks.Input
import org.gradle.api.tasks.InputFiles
import org.gradle.api.tasks.Internal
import org.gradle.api.tasks.Optional

import javax.inject.Inject

/**
 * Represents a named set of source files for compilation with optional
 * per-set configuration (compiler flags, include/exclude patterns, filtering).
 *
 * <p>Allows fine-grained control over compilation of different source directories:
 * <ul>
 *   <li>Apply different compiler flags to different source trees</li>
 *   <li>Use include/exclude patterns to filter source files</li>
 *   <li>Transform source files before compilation (e.g., template expansion)</li>
 * </ul>
 *
 * <p>Usage example:</p>
 * <pre>
 * tasks.register("compile", SimpleCppCompile) {
 *     sourceSets {
 *         main {
 *             sources = fileTree('src/main/cpp')
 *             compilerArgs = ['-fPIC']
 *         }
 *         legacy {
 *             sources = fileTree('src/legacy')
 *             compilerArgs = ['-Wno-deprecated', '-std=c++11']
 *             excludes = ['**&#47;broken/*.cpp']
 *         }
 *     }
 *     objectFileDir = file("build/obj")
 * }
 * </pre>
 */
class SourceSet implements Named {

    private final String name
    private final ObjectFactory objects

    /**
     * Source files for this source set.
     */
    @InputFiles
    final ConfigurableFileCollection sources

    /**
     * Include patterns for filtering source files (Ant-style patterns).
     * Default: ['**&#47;*.cpp', '**&#47;*.c', '**&#47;*.cc']
     */
    @Input
    @Optional
    final ListProperty<String> includes

    /**
     * Exclude patterns for filtering source files (Ant-style patterns).
     * Default: [] (no exclusions)
     */
    @Input
    @Optional
    final ListProperty<String> excludes

    /**
     * Additional compiler arguments specific to this source set.
     * These are added to the base compiler args from SimpleCppCompile.
     * Default: [] (no additional args)
     */
    @Input
    @Optional
    final ListProperty<String> compilerArgs

    /**
     * Optional file filter/transformation closure.
     * If provided, each source file is passed through this closure before compilation.
     * The closure receives a File and should return a File (can be the same or a transformed copy).
     *
     * <p>Example (template expansion):</p>
     * <pre>
     * fileFilter = { File file ->
     *     def transformed = new File(buildDir, "preprocessed/${file.name}")
     *     transformed.text = file.text.replaceAll('@VERSION@', project.version)
     *     return transformed
     * }
     * </pre>
     */
    @Internal
    final Property<Closure> fileFilter

    @Inject
    SourceSet(String name, ObjectFactory objects) {
        this.name = name
        this.objects = objects

        this.sources = objects.fileCollection()

        this.includes = objects.listProperty(String)
            .convention(['**/*.cpp', '**/*.c', '**/*.cc'])

        this.excludes = objects.listProperty(String)
            .convention([])

        this.compilerArgs = objects.listProperty(String)
            .convention([])

        this.fileFilter = objects.property(Closure)
    }

    @Override
    String getName() {
        return name
    }

    /**
     * Convenience method to set source directory.
     */
    void from(Object... sources) {
        this.sources.from(sources)
    }

    /**
     * Convenience method to add include patterns.
     */
    void include(String... patterns) {
        this.includes.addAll(patterns)
    }

    /**
     * Convenience method to add exclude patterns.
     */
    void exclude(String... patterns) {
        this.excludes.addAll(patterns)
    }

    /**
     * Convenience method to add compiler args.
     */
    void compileWith(String... args) {
        this.compilerArgs.addAll(args)
    }

    /**
     * Convenience method to set file filter.
     */
    void filter(Closure filterClosure) {
        this.fileFilter.set(filterClosure)
    }

    @Override
    String toString() {
        return "SourceSet[name=${name}, sources=${sources.files.size()} files]"
    }
}
