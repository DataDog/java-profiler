# Build image for the shipped glibc binaries, both architectures.
#
# AlmaLinux 8 (glibc 2.28) with gcc-toolset-14. Release builds link
# -static-libstdc++ -static-libgcc (see ConfigurationPresets.kt), so the C++
# runtime and unwinder in the shipped libjavaProfiler.so come out of this
# image: the toolchain has to be one that still receives security rebuilds,
# which rules out the EL7 software collections (frozen at CentOS 7.9, and with
# no gcc newer than devtoolset-10 ever built for aarch64).
#
# almalinux:8 is a multi-arch manifest, so BASE_IMAGE is the same for both
# platforms (BASE_IMAGE_GLIBC_2_28 in .gitlab/build-deploy/images.yml) and
# `docker build --platform` selects the architecture. gcc-toolset-14 is
# published for x86_64 and aarch64 alike, so both arches compile with one
# compiler version.
ARG BASE_IMAGE=almalinux:8
FROM ${BASE_IMAGE} as base
ARG CI_JOB_TOKEN
WORKDIR /root

# gcc-toolset-14 carries its own libstdc++.a/libgcc.a, which is what
# -static-libstdc++ resolves against; no separate *-static package is needed.
RUN dnf -y install gcc-toolset-14 \
                   git make cmake zip unzip which wget jq \
 && dnf -y clean all

# Put the toolset ahead of the distro gcc for every shell, including the
# non-login shells GitLab uses to run job scripts (the `scl enable` /
# /opt/rh/gcc-toolset-14/enable wrappers only affect interactive use).
ENV PATH="/opt/rh/gcc-toolset-14/root/usr/bin:${PATH}" \
    LD_LIBRARY_PATH="/opt/rh/gcc-toolset-14/root/usr/lib64:${LD_LIBRARY_PATH}"

# The build scripts locate a JDK through JAVA_HOME, falling back to SDKMAN's
# current candidate (.gitlab/scripts/build.sh).
RUN curl -s "https://get.sdkman.io" | bash && \
    bash -c "source /root/.sdkman/bin/sdkman-init.sh && sdk install java 21.0.3-tem && sdk install maven"
ENV JAVA_HOME=/root/.sdkman/candidates/java/current
ENV PATH="/root/.sdkman/candidates/java/current/bin:/root/.sdkman/candidates/maven/current/bin:${PATH}"
