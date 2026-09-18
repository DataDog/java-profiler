# Runtime-only image for exercising the shipped x64 binary on its actual
# glibc floor (2.17). Oracle Linux 7 is the best-maintained EL7 derivative —
# live CDN, current package levels, no ELS subscription needed — see PR #790.
#
# This image never compiles anything real: the shipped libjavaProfiler.so is
# built in the AlmaLinux 8 image (.gitlab/base/el8/Dockerfile) and consumed
# here via -Pskip-native -Pwith-libs, which gates every actual compile/link
# task onlyIf. It still needs *a* C++ compiler on PATH, though: Gradle's
# ConfigurationPresets.setupStandardConfigurations() calls
# PlatformUtils.findCompiler() unconditionally at project-configuration time
# (build-logic/conventions/.../ConfigurationPresets.kt:35), before -Pskip-native
# is even consulted — with none present, configuration itself fails with
# "No C++ compiler found." The stock EL7 gcc-c++ (4.8.5) is only here to
# satisfy that `--version` probe; it is never invoked to build anything.
#
# Gradle 9 requires JDK 17+ to run, so JAVA_HOME is a single build JDK (21).
# Suites that test against other JDKs (8, 11, 17, ...) fetch that JDK at job
# runtime into JAVA_TEST_HOME (see .gitlab/scripts/functional-tests.sh) —
# the profiler-test Gradle plugin already runs the test JVM from
# JAVA_TEST_HOME when it is set, independently of the JDK running Gradle
# itself.
ARG BASE_IMAGE=oraclelinux:7
FROM ${BASE_IMAGE} as base
WORKDIR /root

RUN yum -y install git make zip unzip which wget curl jq gcc-c++ \
 && yum -y clean all

RUN curl -s "https://get.sdkman.io" | bash && \
    bash -c "source /root/.sdkman/bin/sdkman-init.sh && sdk install java 21.0.3-tem"
ENV JAVA_HOME=/root/.sdkman/candidates/java/current
ENV PATH="/root/.sdkman/candidates/java/current/bin:${PATH}"
