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

RUN yum -y update ca-certificates \
 && ln -sf /usr/lib64/pkcs11/p11-kit-trust.so /usr/lib64/nss/libnssckbi.so
# python3 (3.6.8 on this base repo -- no newer python3/SCL repo exists for
# Oracle Linux 7) runs the quarantine classifier (.github/scripts/
# run_tests_with_retry.sh, quarantine.py, flake_report.py) that
# functional-tests.sh wraps its test run in.
RUN yum -y install git make zip unzip which wget curl jq gcc-c++ python3 \
 && yum -y clean all
# OL7 has no fixed ca-certificates package. Preserve every other p11-kit
# object and its purpose restrictions while removing the compromised roots.
RUN python3 -c 'from pathlib import Path; p=Path("/usr/share/pki/ca-trust-source/ca-bundle.trust.p11-kit"); mark=b"[p11-kit-object-v1]"; parts=p.read_bytes().split(mark); bad=(b"emSign ECC Root CA - G3", b"AAA Certificate Services"); drop=lambda part: any(name in part for name in bad); assert all(any(name in part for part in parts[1:]) for name in bad); p.write_bytes(parts[0] + b"".join(mark + part for part in parts[1:] if not drop(part)))' \
 && update-ca-trust extract

RUN curl -s "https://get.sdkman.io" | bash && \
    bash -c "source /root/.sdkman/bin/sdkman-init.sh && sdk install java 21.0.3-tem"
RUN /root/.sdkman/candidates/java/current/bin/keytool -list -v -cacerts -storepass changeit \
    | awk -F ': ' '/^Alias name:/{alias=$2} /Owner:.*(emSign ECC Root CA - G3|AAA Certificate Services)/{print alias}' \
    | while IFS= read -r alias; do /root/.sdkman/candidates/java/current/bin/keytool -delete -cacerts -storepass changeit -alias "$alias"; done
ENV JAVA_HOME=/root/.sdkman/candidates/java/current
ENV PATH="/root/.sdkman/candidates/java/current/bin:${PATH}"
