# Datadog Java Profiler Library
_Based on [async-profiler 2.8.3](https://github.com/jvm-profiling-tools/java-profiler/releases/tag/v2.8.3)_

## Disclaimer
This is not a fork of [async-profiler](https://github.com/jvm-profiling-tools/async-profiler). This is a work derived from __async-profiler__ but tailored very specifically for Datadog needs.
If you need a full-fledged Java profiler head back to [async-profiler](https://github.com/jvm-profiling-tools/async-profiler)

## Usage
**!TODO!**


## Build
### Building Local Artifacts
In order to ease up consuming of the java-profiler library in downstream projects (eg. dd-trace-java) it is possible to quickly build a maven artifact (jar) which can replace the stable dependency to test the changes.

#### Prerequisites
The local build requires docker and Java 11 to be installed.

#### Build script
Use `./datadog/scripts/build_locally.sh` to build linux-x64 only maven artifact.

After running this script you should see something like
```shell
jaroslav.bachorik@COMP-C02FJ0PSMD6V java-profiler % ./datadog/scripts/build_locally.sh
=== Building Java Profiler
==    Version     : 2.6-DD-jb_local_artifact-bc38fb7712459603349d7a36a90c9d02611a450d
==    Architecture: linux-amd64
==    With tests  : no
-> Building native library
-> Building maven artifact
-> Build done : Artifacts available |
*  file:///tmp/ap-tools-2.6-DD-jb_local_artifact-bc38fb7712459603349d7a36a90c9d02611a450d.jar
```

The artifact version contain the encoded branch name and the HEAD commit hash - which makes it easily identifiable. The actual path of the built artifact depends on your system but you can easily copy-paste it around.

##### Supported arguments
The build script support the following arguments:
- `-a <architecture>` 
  - one of `linux-x64`, `linux-x64-musl` or `linux-arm64` (defaults to `linux-x64`)
- `-f`
  - force docker image rebuild
- `-t`
  - force test run
- `-h`
  - show help

### Consuming the artifact
For dd-trace-java you just need to set the `java.profiler.jar` project property.
Eg. you can run the gradle build like this - ./gradlew clean -Pjava.profiler.jar=file://<path-to-artifact.jar> :dd-java-agent:shadowJar` - which will result in a custom `dd-java-agent.jar` build containing your test version of Java profiler.
