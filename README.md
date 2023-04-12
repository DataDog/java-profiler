# Datadog Java Profiler Library
_Based on [async-profiler 2.8.3](https://github.com/jvm-profiling-tools/java-profiler/releases/tag/v2.8.3)_

## Disclaimer
This is not a fork of [async-profiler](https://github.com/jvm-profiling-tools/async-profiler). This is a work derived from __async-profiler__ but tailored very specifically for Datadog needs.
If you need a full-fledged Java profiler head back to [async-profiler](https://github.com/jvm-profiling-tools/async-profiler)

## Usage
**!TODO!**


## Build
As simple as `./gradlew build`. The resulting artifact is located in `ddprof-lib/build/libs/ddprof-<version>.jar`

If building and testing on Apple Silicon (M1+), be sure to install an aarch64 OpenJDK distribution, otherwise the architecture used for compilation and the JVM based test suite will not match, which means the tests will not be able to load the dynamic library at runtime.

### Consuming the artifact
For dd-trace-java you just need to set the `java.profiler.jar` project property.
Eg. you can run the gradle build like this - ./gradlew clean -Pjava.profiler.jar=file://<path-to-artifact.jar> :dd-java-agent:shadowJar` - which will result in a custom `dd-java-agent.jar` build containing your test version of Java profiler.
