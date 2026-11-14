# Copyright 2026, Datadog, Inc.

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

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y ca-certificates \
 && update-ca-certificates -f
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
        curl git moreutils awscli amazon-ecr-credential-helper gnupg2 build-essential \
        wget bsdmainutils clang jq zip unzip \
        cmake libgtest-dev libgmock-dev libc6-dbg llvm libclang-rt-dev \
 && ln -sf /etc/ssl/certs/ca-certificates.crt /usr/lib/python3/dist-packages/awscli/botocore/cacert.pem
# Debian's packaged Node includes obsolete roots in both libnode and its headers.
# Use the fixed Node 22 release and verify the upstream archive before unpacking.
ARG TARGETARCH
RUN case "${TARGETARCH}" in \
        amd64) node_arch=x64; node_sha=b8492284c76a54baf58d61668dd0e41ee0fc98adabf9503d30f05d08f55b4406 ;; \
        arm64) node_arch=arm64; node_sha=f7a1e486dbc8b286847815b477d4fb5e9fb963ed4489c3e1588853d685f589f9 ;; \
        *) exit 1 ;; \
    esac \
 && curl -fsSLo /tmp/node.tar.gz "https://nodejs.org/dist/v22.23.4/node-v22.23.4-linux-${node_arch}.tar.gz" \
 && echo "${node_sha}  /tmp/node.tar.gz" | sha256sum -c - \
 && tar -xzf /tmp/node.tar.gz -C /usr/local --strip-components=1 \
 && rm /tmp/node.tar.gz
# Install JDK 21 and Maven via SDKMAN (glibc image only; musl uses Dockerfile.musl).
RUN curl -s "https://get.sdkman.io" | bash && \
    bash -c "source /root/.sdkman/bin/sdkman-init.sh && sdk install java 21.0.3-tem && sdk install maven"
# SDKMAN does not yet publish the fixed Temurin update; remove the two roots
# from the bundled JDK trust store until that version is available.
RUN /root/.sdkman/candidates/java/current/bin/keytool -list -v -cacerts -storepass changeit \
    | awk -F ': ' '/^Alias name:/{alias=$2} /Owner:.*(emSign ECC Root CA - G3|AAA Certificate Services)/{print alias}' \
    | while IFS= read -r alias; do /root/.sdkman/candidates/java/current/bin/keytool -delete -cacerts -storepass changeit -alias "$alias"; done
ENV JAVA_HOME=/root/.sdkman/candidates/java/current
ENV PATH="/root/.sdkman/candidates/java/current/bin:/root/.sdkman/candidates/maven/current/bin:${PATH}"
RUN npm install -g --save-dev @datadog/datadog-ci
RUN  rm -rf "/var/lib/apt/lists/*"
