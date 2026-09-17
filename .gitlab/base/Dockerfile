# CI always passes BASE_IMAGE explicitly (OPENJDK_BASE_IMAGE /
# OPENJDK_BASE_IMAGE_ARM64), both of which are this same digest: the shipped
# binaries are built elsewhere (.gitlab/base/el8/Dockerfile), so neither arch
# of this image sets a customer-facing glibc floor. The default matches them,
# so a hand-built image -- or rebuild-images.sh reaching its unset-variable
# fallback -- gets a release whose packages still resolve.
ARG BASE_IMAGE=debian:trixie-slim@sha256:d7e12182ce18b85b93007c1dedf31f2d29e01ccf3182cc4017c709b6259bc132
FROM ${BASE_IMAGE} as base
ARG CI_JOB_TOKEN
WORKDIR /root

RUN mkdir -p /usr/share/man/man1 # https://github.com/debuerreotype/docker-debian-artifacts/issues/24
# Alpine/musl images build from Dockerfile.musl, so this file installs only the
# Debian toolchain.
#
# The second group is what the C++ test and sanitizer jobs need. They live in
# the image rather than in a job's before_script so that a job does not depend
# on the distro archive still serving those packages at run time.
# libclang-rt-dev is the unversioned metapackage: it provides
# sanitizer/asan_interface.h from whichever clang runtime matches this release.
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        curl git moreutils awscli amazon-ecr-credential-helper gnupg2 npm build-essential \
        wget bsdmainutils clang jq zip unzip \
        cmake libgtest-dev libgmock-dev libc6-dbg llvm libclang-rt-dev
# Install JDK 21 and Maven via SDKMAN (glibc image only; musl uses Dockerfile.musl).
RUN curl -s "https://get.sdkman.io" | bash && \
    bash -c "source /root/.sdkman/bin/sdkman-init.sh && sdk install java 21.0.3-tem && sdk install maven"
ENV JAVA_HOME=/root/.sdkman/candidates/java/current
ENV PATH="/root/.sdkman/candidates/java/current/bin:/root/.sdkman/candidates/maven/current/bin:${PATH}"
RUN npm install -g --save-dev @datadog/datadog-ci
RUN  rm -rf "/var/lib/apt/lists/*"