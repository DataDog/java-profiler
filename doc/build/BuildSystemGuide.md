# Build System Maintenance Guide

This document provides detailed guidance for maintaining and extending the Gradle build system.

## Convention Plugins Overview

All custom build logic lives in `build-logic/conventions/`. The plugins are:

| Plugin ID | Class | Purpose |
|-----------|-------|---------|
| `com.datadoghq.native-build` | `NativeBuildPlugin` | Multi-config C++ compilation |
| `com.datadoghq.native-root` | `RootProjectPlugin` | Root-level config discovery |
| `com.datadoghq.gtest` | `GtestPlugin` | Google Test integration |
| `com.datadoghq.simple-native-lib` | `SimpleNativeLibPlugin` | Simple single-library builds |
| `com.datadoghq.profiler-test` | `ProfilerTestPlugin` | Multi-config Java test generation |
| `com.datadoghq.java-conventions` | `JavaConventionsPlugin` | Java 8 compilation settings |
| `com.datadoghq.versioned-sources` | `VersionedSourcesPlugin` | Java version-specific code |
| `com.datadoghq.fuzz-targets` | `FuzzTargetsPlugin` | libFuzzer integration |
| `com.datadoghq.scanbuild` | `ScanBuildPlugin` | Clang static analysis |
| `com.datadoghq.spotless-convention` | `SpotlessConventionPlugin` | Code formatting |

## Key Files and Their Purposes

```
build-logic/conventions/src/main/kotlin/com/datadoghq/
├── native/
│   ├── NativeBuildPlugin.kt         # Creates compile/link tasks per config
│   ├── NativeBuildExtension.kt      # DSL: nativeBuild { ... }
│   ├── RootProjectPlugin.kt         # Provides configs to all subprojects
│   ├── SimpleNativeLibPlugin.kt     # Simplified single-lib builds
│   ├── config/
│   │   └── ConfigurationPresets.kt  # Defines release/debug/asan/tsan/fuzzer
│   ├── model/
│   │   ├── BuildConfiguration.kt    # Config model (platform, arch, flags)
│   │   ├── Platform.kt              # LINUX, MACOS enum
│   │   └── Architecture.kt          # X64, ARM64, etc.
│   ├── tasks/
│   │   ├── NativeCompileTask.kt     # C++ compilation task
│   │   ├── NativeLinkTask.kt        # Shared library linking
│   │   └── NativeLinkExecutableTask.kt  # Executable linking
│   ├── util/
│   │   └── PlatformUtils.kt         # Platform detection, compiler finding
│   ├── gtest/
│   │   ├── GtestPlugin.kt           # Google Test task generation
│   │   ├── GtestExtension.kt        # DSL: gtest { ... }
│   │   └── GtestTaskBuilder.kt      # Per-test task creation
│   └── fuzz/
│       └── FuzzTargetsPlugin.kt     # Fuzz testing support
├── profiler/
│   ├── ProfilerTestPlugin.kt        # Multi-config test generation
│   ├── JavaConventionsPlugin.kt     # Java 8 --release flag
│   └── SpotlessConventionPlugin.kt  # Code formatting
└── java/versionedsources/
    └── VersionedSourcesPlugin.kt    # Java 9+ version-specific code
```

## How Build Configurations Work

Build configurations (release, debug, asan, tsan, fuzzer) are defined in `ConfigurationPresets.kt`:

1. **Registration**: Configs are registered in `NativeBuildExtension.buildConfigurations`
2. **Activation**: Each config checks if it's available on current platform
   - release/debug: Always active
   - asan: Active if `libasan.so` found via `gcc -print-file-name=libasan.so`
   - tsan: Active if `libtsan.so` found
   - fuzzer: Active if clang supports `-fsanitize=fuzzer`
3. **Discovery**: Subprojects query active configs via `nativeBuild.buildConfigurations.names`

### Configuration Flow Diagram

```
┌─────────────────────────────────────────────────────────────────┐
│                    settings.gradle.kts                          │
│  includeBuild("build-logic") ← loads convention plugins         │
└─────────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────────┐
│                     build.gradle.kts (root)                     │
│  plugins { id("com.datadoghq.native-root") }                    │
│  ↓                                                              │
│  RootProjectPlugin creates nativeBuild extension                │
│  ↓                                                              │
│  afterEvaluate: ConfigurationPresets.setupStandardConfigurations│
│  → Registers: release, debug, asan, tsan, fuzzer                │
│  → Checks availability via PlatformUtils                        │
└─────────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────────┐
│                  ddprof-lib/build.gradle.kts                    │
│  plugins { id("com.datadoghq.native-build") }                   │
│  ↓                                                              │
│  afterEvaluate: queries nativeBuild.buildConfigurations.names   │
│  → Creates tasks: compileRelease, linkRelease, assembleRelease  │
│  → Creates tasks: compileDebug, linkDebug, assembleDebug        │
│  → (only for active configs on current platform)                │
└─────────────────────────────────────────────────────────────────┘
```

## Adding a New Build Configuration

To add a new configuration (e.g., "coverage"):

### Step 1: Add to ConfigurationPresets.kt

```kotlin
// In setupStandardConfigurations()
extension.buildConfigurations.apply {
    // ... existing configs ...
    register("coverage") {
        configureCoverage(this, currentPlatform, currentArch, version, rootDir)
    }
}

// Add configuration function
fun configureCoverage(
    config: BuildConfiguration,
    platform: Platform,
    architecture: Architecture,
    version: String,
    rootDir: File
) {
    config.platform.set(platform)
    config.architecture.set(architecture)
    config.active.set(PlatformUtils.hasGcov())  // Add detection in PlatformUtils

    when (platform) {
        Platform.LINUX -> {
            config.compilerArgs.set(
                listOf("-O0", "-g", "--coverage", "-fprofile-arcs", "-ftest-coverage") +
                commonLinuxCompilerArgs(version)
            )
            config.linkerArgs.set(commonLinuxLinkerArgs() + listOf("--coverage"))
        }
        Platform.MACOS -> {
            config.compilerArgs.set(
                listOf("-O0", "-g", "--coverage") + commonMacosCompilerArgs(version)
            )
            config.linkerArgs.set(listOf("--coverage"))
        }
    }
}
```

### Step 2: Add Detection to PlatformUtils.kt (if needed)

```kotlin
fun hasGcov(): Boolean {
    return isCompilerAvailable("gcov")
}
```

### Step 3: No Changes Needed in Build Scripts

Configurations are discovered dynamically - all subprojects automatically pick up the new config.

## Modifying Compiler/Linker Flags

Flags are centralized in `ConfigurationPresets.kt`:

| Function | Purpose |
|----------|---------|
| `commonLinuxCompilerArgs()` | Shared C++ flags for all Linux configs |
| `commonLinuxLinkerArgs()` | Shared linker flags for Linux |
| `commonMacosCompilerArgs()` | Shared C++ flags for macOS |
| `configureRelease()` | Release-specific flags |
| `configureDebug()` | Debug-specific flags |
| `configureAsan()` | AddressSanitizer flags |
| `configureTsan()` | ThreadSanitizer flags |
| `configureFuzzer()` | libFuzzer flags |

### Example: Adding a Flag to All Configs

```kotlin
private fun commonLinuxCompilerArgs(version: String): List<String> {
    return mutableListOf(
        "-fPIC",
        "-fno-omit-frame-pointer",
        "-momit-leaf-frame-pointer",
        "-fvisibility=hidden",
        "-fdata-sections",
        "-ffunction-sections",
        "-std=c++17",
        // Add new flag here:
        "-fstack-protector-strong",
        "-DPROFILER_VERSION=\"$version\"",
        "-DCOUNTERS"
    )
}
```

### Example: Adding a Flag to One Config

```kotlin
fun configureRelease(...) {
    when (platform) {
        Platform.LINUX -> {
            config.compilerArgs.set(
                listOf("-O3", "-DNDEBUG", "-g", "-flto") +  // Added -flto
                commonLinuxCompilerArgs(version)
            )
        }
    }
}
```

## Creating a New Convention Plugin

### Step 1: Create the Plugin Class

Create in `build-logic/conventions/src/main/kotlin/com/datadoghq/example/`:

```kotlin
package com.datadoghq.example

import org.gradle.api.Plugin
import org.gradle.api.Project
import org.gradle.api.provider.Property
import javax.inject.Inject

class MyPlugin : Plugin<Project> {
    override fun apply(project: Project) {
        // Create extension for DSL configuration
        val extension = project.extensions.create(
            "myPlugin",
            MyExtension::class.java,
            project
        )

        // Create configurations eagerly (so build scripts can reference them)
        val myConfig = project.configurations.create("myConfiguration")

        // Configure tasks in afterEvaluate (when extension values are set)
        project.afterEvaluate {
            if (extension.enabled.get()) {
                createTasks(project, extension)
            }
        }
    }

    private fun createTasks(project: Project, extension: MyExtension) {
        project.tasks.register("myTask") {
            group = "my-group"
            description = "Does something useful"
            doLast {
                println("Setting: ${extension.someSetting.get()}")
            }
        }
    }
}

abstract class MyExtension @Inject constructor(project: Project) {
    val enabled: Property<Boolean> = project.objects.property(Boolean::class.java)
    val someSetting: Property<String> = project.objects.property(String::class.java)

    init {
        enabled.convention(true)
        someSetting.convention("default-value")
    }
}
```

### Step 2: Register in build.gradle.kts

Add to `build-logic/conventions/build.gradle.kts`:

```kotlin
gradlePlugin {
    plugins {
        // ... existing plugins ...
        create("myPlugin") {
            id = "com.datadoghq.my-plugin"
            implementationClass = "com.datadoghq.example.MyPlugin"
        }
    }
}
```

### Step 3: Use in Subproject

```kotlin
plugins {
    id("com.datadoghq.my-plugin")
}

myPlugin {
    enabled.set(true)
    someSetting.set("custom-value")
}
```

## Best Practices for Plugin Development

### Prefer Lazy Configuration

```kotlin
// GOOD - lazy task registration
project.tasks.register("myTask", MyTask::class.java) {
    inputFile.set(extension.someFile)  // Evaluated when task executes
}

// AVOID - eager task creation
project.tasks.create("myTask", MyTask::class.java) {
    inputFile.set(extension.someFile)  // Evaluated immediately
}
```

### Create Configurations Eagerly, Populate Lazily

```kotlin
override fun apply(project: Project) {
    // Create configurations immediately (so build scripts can use them)
    val myConfig = project.configurations.create("myConfiguration").apply {
        isCanBeConsumed = true
        isCanBeResolved = true
    }

    // Populate dependencies in afterEvaluate
    project.afterEvaluate {
        myConfig.dependencies.add(
            project.dependencies.create("com.example:lib:1.0")
        )
    }
}
```

### Use Lazy Task References

```kotlin
// GOOD - lazy reference, doesn't force task creation
val linkTask = tasks.named("linkRelease")
myTask.dependsOn(linkTask)

// AVOID - forces immediate task creation/lookup
val linkTask = tasks.getByName("linkRelease")
```

### Check Task Existence Safely

```kotlin
// GOOD - safe check
if (tasks.names.contains("linkRelease")) {
    dependsOn("linkRelease")
}

// AVOID - throws exception if not found
dependsOn(tasks.getByName("linkRelease"))
```

## Testing Build Changes

After modifying build-logic:

```bash
# Kill Gradle daemon to pick up plugin changes
./gradlew --stop

# Verify configuration loads without errors
./.claude/commands/build-and-summarize tasks --group=build -q

# Verify Java compilation
./.claude/commands/build-and-summarize :ddprof-lib:compileJava :ddprof-test:compileJava -Pskip-native

# Verify native compilation (on Linux)
./.claude/commands/build-and-summarize assembleRelease

# Verify tests can be configured
./.claude/commands/build-and-summarize :ddprof-test:testRelease -Pskip-native

# Verify all tasks are generated correctly
./.claude/commands/build-and-summarize :ddprof-lib:tasks --all
```

## Gradle Properties Reference

All configurable properties (see `gradle.properties.template` for full documentation):

| Property | Default | Description |
|----------|---------|-------------|
| `skip-tests` | false | Skip Java test execution |
| `skip-native` | false | Skip C++ compilation |
| `skip-gtest` | false | Skip Google Test execution |
| `skip-fuzz` | false | Skip fuzz testing |
| `native.forceCompiler` | auto | Force specific C++ compiler path |
| `ddprof_version` | from build.gradle.kts | Override project version |
| `with-libs` | - | Path to pre-built native libraries |
| `keepJFRs` | false | Keep JFR recordings after tests |
| `validatorArgs` | - | Arguments for UnwindingValidator |
| `CI` | from env | CI environment flag |
| `forceLocal` | false | Use local Nexus for testing |

## Troubleshooting

### "Configuration not found"

Configurations are created in `afterEvaluate`. Ensure you're accessing them in `afterEvaluate` or later:

```kotlin
// WRONG - runs during configuration phase
val cfg = configurations.getByName("testReleaseImplementation")  // May not exist yet

// RIGHT - runs after all afterEvaluate blocks
project.afterEvaluate {
    val cfg = configurations.getByName("testReleaseImplementation")
}

// ALSO RIGHT - use gradle.projectsEvaluated for cross-project
gradle.projectsEvaluated {
    val cfg = configurations.getByName("testReleaseImplementation")
}
```

### "Task not found"

Tasks are created dynamically based on active configs. Verify:

1. The config is active: Check `PlatformUtils` detection methods
2. The plugin is applied: Check `plugins { }` block
3. You're in the right phase: Use `afterEvaluate` or `gradle.projectsEvaluated`

### Plugin Changes Not Taking Effect

The Gradle daemon caches compiled plugins:

```bash
./gradlew --stop                    # Kill daemon
./gradlew tasks --no-daemon         # Run without daemon
```

### Circular Dependencies

Avoid cross-project `afterEvaluate` dependencies. Use `gradle.projectsEvaluated` instead:

```kotlin
// WRONG - may cause ordering issues
project.afterEvaluate {
    val otherProject = rootProject.findProject(":other")
    otherProject?.afterEvaluate { ... }  // Nested afterEvaluate
}

// RIGHT - runs after ALL projects are evaluated
gradle.projectsEvaluated {
    val otherProject = rootProject.findProject(":other")
    // Safe to access other project's tasks/configs
}
```

### Debug Gradle Configuration

```bash
# Show task dependencies
./gradlew :ddprof-lib:assembleRelease --dry-run

# Show dependency resolution
./gradlew :ddprof-test:dependencies --configuration testReleaseImplementation

# Enable debug logging
./gradlew build -d 2>&1 | head -500
```

## See Also

- [GRADLE-TASKS.md](GRADLE-TASKS.md) - Task reference and workflows
- [build-logic/README.md](../build-logic/README.md) - Plugin implementation details
- [gradle.properties.template](../gradle.properties.template) - All configurable properties
