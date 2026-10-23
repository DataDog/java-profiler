<!-- Copyright 2026, Datadog, Inc. -->

# Build and Test JDKs, and JDK Upgrades

## Two-JDK pattern

The build uses two JDKs, chosen by two environment variables:

| Variable | Role | Consumed by |
|---|---|---|
| `JAVA_HOME` | **Build JDK.** Runs the Gradle daemon and `javac`, and provides the JNI headers for the native build | Gradle itself, and `PlatformUtils.javaHome()` (`build-logic/conventions/src/main/kotlin/com/datadoghq/native/util/PlatformUtils.kt:29-33`). `jniIncludePaths()` uses it to build `-I$JAVA_HOME/include{,/linux,/darwin}` (`PlatformUtils.kt:53-63`, `NativeBuildPlugin.kt:114`) |
| `JAVA_TEST_HOME` | **Test JDK.** The JVM that runs the Java tests, which can differ from the build JDK | `PlatformUtils.testJavaHome()`: `JAVA_TEST_HOME`, then `JAVA_HOME`, then `java.home` (`PlatformUtils.kt:39-44`), and `testJavaExecutable()` = `$testJavaHome/bin/java` (`PlatformUtils.kt:49-51`) |

`ProfilerTestPlugin` sets the test executable directly and bypasses Gradle
toolchains:

- glibc/macOS `Test` tasks call `testTask.setExecutable(PlatformUtils.testJavaExecutable())`
  (`build-logic/conventions/src/main/kotlin/com/datadoghq/profiler/ProfilerTestPlugin.kt:248`).
- musl `Exec` tasks, and the unwinding validator/report tasks, set
  `executable = PlatformUtils.testJavaExecutable()` inside `doFirst`, so the
  environment is read when the task runs (`ProfilerTestPlugin.kt:354`,
  `ProfilerTestPlugin.kt:527`, `ProfilerTestPlugin.kt:574`).

Flags that depend on the JDK version must probe the test JVM at execution time,
not at configuration time. At configuration time, `testJavaHome()` can fall
back to the build JDK and report the wrong version (`ProfilerTestPlugin.kt:739-745`).
Existing probes are `PlatformUtils.testJvmMajorVersion()` (`PlatformUtils.kt:444`)
and `isTestJvmJ9()` (`PlatformUtils.kt:463`). They are used, for example, to
gate `HeapBaseMinAddress` for ASan on JDK 12+ (`native/config/ConfigurationPresets.kt:251`)
and to skip J9+ASan (`ProfilerTestPlugin.kt:308`).

### Cross-JDK testing

```bash
# Build with the JDK in JAVA_HOME, run tests on another JDK
JAVA_TEST_HOME=/path/to/test/jdk ./gradlew testDebug
```

CI uses the same pattern:

- **GitHub Actions.** `.github/actions/setup_cached_java/action.yml:70-75`
  exports `JAVA_HOME=jdks/jdk21` (`jdk21-librca` on musl) and
  `JAVA_TEST_HOME=jdks/jdk<version>`.
- **GitLab functional tests.** `.gitlab/scripts/functional-tests.sh:38-53`
  downloads the test JDK separately and exports `JAVA_TEST_HOME`.

## Build JDK requirements

- Gradle version: **9.8.1** (`gradle/wrapper/gradle-wrapper.properties:3`).
- Gradle 9 needs JVM 17 or later to run the daemon (Gradle 9.0 upgrade guide,
  "Upgrading to Gradle 9.0.0"). CI comments say the same:
  `.github/actions/setup_cached_java/action.yml:21` and
  `utils/run-containers-tests.sh:1099-1100`.
- The project uses **JDK 21** (LTS) as its build JDK:
  - GitHub Actions: `setup_cached_java/action.yml:22-27` and `ci.yml:129,172`
    (`java-version: '21'`)
  - GitLab: `sdk install java 21.0.3-tem` (`.gitlab/common.yml:86`,
    `.gitlab/base/{,el7/,el8/}Dockerfile`) and `eclipse-temurin:21-jdk-alpine`
    (`.gitlab/config.env:43-44`, `.gitlab/build-deploy/images.yml:15-16`)
  - Containers: `BUILD_JDK_VERSION="21"` (`utils/run-containers-tests.sh:1101`)
- **No minimum is enforced in the build scripts.** There is no
  `gradle/gradle-daemon-jvm.properties`, and no `JavaVersion.current()` check on
  the build JDK. The only `JavaVersion.current()` calls are in the
  `versioned-sources` plugin, and no project applies that plugin. If the build
  JDK is too old, Gradle itself fails at startup.
- Two sources state the requirement more strictly. `README.md:12` says "JDK 21
  or later (required for building - Gradle 9 requirement)", and the
  `JavaConventionsPlugin.kt:17` KDoc says "Requires JDK 21+ for building
  (Gradle 9 requirement)". Gradle's actual minimum is 17. 21 is this project's
  choice.

## Target bytecode: Java 8

- `JavaConventionsPlugin` (plugin id `com.datadoghq.java-conventions`) adds
  `--release 8 -Xlint:-options` to every `JavaCompile` task
  (`build-logic/conventions/src/main/kotlin/com/datadoghq/profiler/JavaConventionsPlugin.kt:29-33`).
  `-Xlint:-options` suppresses the JDK 21 deprecation warning for release 8.
- Projects that apply it: `ddprof-test` (`ddprof-test/build.gradle.kts:8`),
  `ddprof-test-tracer` (`ddprof-test-tracer/build.gradle.kts:3`), and
  `ddprof-stresstest` (`ddprof-stresstest/build.gradle.kts:21`).
- **`ddprof-lib` does not apply `java-conventions`.** It targets Java 8 through
  `java { sourceCompatibility = JavaVersion.VERSION_1_8; targetCompatibility = JavaVersion.VERSION_1_8 }`
  (`ddprof-lib/build.gradle.kts:107-110`). The shipped library is therefore
  compiled with source/target 8 compatibility, not with `--release 8`.
- JDK 8 runtime coverage comes from the test JDK matrix (`8`, `8-orcl`, `8-j9`,
  `8-ibm`, `8-librca`). See `.github/workflows/test_workflow.yml:56` and
  `.github/workflows/cache_java.yml:152,213`.

## Files to touch

### Upgrading the build JDK (for example, 21 → 25)

| File | What to change |
|---|---|
| `.github/actions/setup_cached_java/action.yml:21-27` | `build_jdk=jdk21` / `jdk21-librca`, and the comment |
| `.github/workflows/ci.yml:129,172` | `java-version: '21'` in the `check-formatting` and `check-javadoc` jobs |
| `.github/workflows/cache_java.yml` | The new build JDK must be in the cached `java_variant` matrices, and in the URLs for musl (`JAVA_<n>_MUSL_URL`) |
| `utils/run-containers-tests.sh:1099-1101` | `BUILD_JDK_VERSION`, and the comment |
| `.gitlab/common.yml:86`, `.gitlab/base/Dockerfile`, `.gitlab/base/el7/Dockerfile`, `.gitlab/base/el8/Dockerfile`, `.gitlab/reliability/*.sh` | `sdk install java 21.0.3-tem` |
| `.gitlab/config.env:43-44`, `.gitlab/build-deploy/images.yml:15-16`, `.gitlab/base/Dockerfile.musl:1` | `eclipse-temurin:21-jdk-alpine@sha256:…` |
| `.gitlab/scripts/prepare.sh:36`, `docker/Dockerfile.fuzz:11` | `openjdk-21-jdk[-headless]` packages |
| `README.md:12` | Prerequisites line |
| `JavaConventionsPlugin.kt:14-17` | KDoc, and check that `-Xlint:-options` is still needed and that `--release 8` is still supported by the new `javac` |
| (implicit) | The native build compiles against the build JDK's `jni.h` (`PlatformUtils.jniIncludePaths()`) |

### Changing the target bytecode level (for example, 8 → 11)

| File | What to change |
|---|---|
| `JavaConventionsPlugin.kt:32` | `--release 8` |
| `ddprof-lib/build.gradle.kts:107-110` | `sourceCompatibility` / `targetCompatibility` |
| `README.md` | Supported runtime versions |
| `.github/workflows/test_workflow.yml`, `.github/workflows/cache_java.yml`, `.gitlab/build-deploy/.gitlab-ci.yml` (`functional:*-jdk8` jobs) | Remove test JDKs that fall below the new target |

### Upgrading Gradle

Change `distributionUrl` in `gradle/wrapper/gradle-wrapper.properties`, then
regenerate the wrapper scripts. `README.md:13` still says "Gradle 9.3.1" and
does not match the wrapper (9.8.1).

## Gradle 9 breaking-API reference

`AGENTS.md` refers to a "Gradle 9 breaking-API reference table" in this file.
The table was in `AGENTS.md` before commit `e22b8f930` and was removed when the
section moved here. It is restored below from `git show e22b8f930^:AGENTS.md`.
The last column shows whether the new API is in the current code:

| Old API | Replacement | Where | Present now |
|---|---|---|---|
| `project.exec { }` in task actions | `ProcessBuilder` | `native/gtest/GtestPlugin.kt` | yes, `GtestPlugin.kt:150-151` ("Gradle 9 removed project.exec in task actions") |
| `String.capitalize()` | `replaceFirstChar { … }` | Kotlin plugins | yes, e.g. `BuildConfiguration.kt:50`, `ProfilerTestPlugin.kt:197` |
| `createTempFile()` | `kotlin.io.path.createTempFile()` | `PlatformUtils.kt` | yes, `PlatformUtils.kt:9,168` |
| Spotless `userData()` | `editorConfigOverride()` | `SpotlessConventionPlugin.kt` | yes, `SpotlessConventionPlugin.kt:46` |
| Spotless `indentWithSpaces()` | `leadingTabsToSpaces()` | `SpotlessConventionPlugin.kt` | yes, `SpotlessConventionPlugin.kt:36,63,103` |

Only the first row is a Gradle API change. The other rows are Kotlin stdlib and
Spotless plugin deprecations that were fixed during the same upgrade
(`f40d4a930`, "Upgrade to Gradle 9.3.1 with JDK 21 build requirement").
