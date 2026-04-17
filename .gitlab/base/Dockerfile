ARG BASE_IMAGE=debian:bullseye-slim@sha256:0083feb8da4f624e3a0245e7752af2517d4b81d8b8db50c725644672a132a31b
FROM ${BASE_IMAGE} as base
ARG CI_JOB_TOKEN
WORKDIR /root

RUN mkdir -p /usr/share/man/man1 # https://github.com/debuerreotype/docker-debian-artifacts/issues/24
RUN (apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends curl git moreutils awscli amazon-ecr-credential-helper gnupg2 npm build-essential wget bsdmainutils clang jq zip unzip) || true
RUN (apk update && apk add curl git moreutils aws-cli docker-credential-ecr-login gnupg alpine-sdk build-base wget npm hexdump linux-headers clang compiler-rt bash jq gradle zip unzip) || true
# Install JDK 21 and Maven via SDKMAN (glibc image only; musl uses Dockerfile.musl).
RUN curl -s "https://get.sdkman.io" | bash && \
    bash -c "source /root/.sdkman/bin/sdkman-init.sh && sdk install java 21.0.3-tem && sdk install maven"
ENV JAVA_HOME=/root/.sdkman/candidates/java/current
ENV PATH="/root/.sdkman/candidates/java/current/bin:/root/.sdkman/candidates/maven/current/bin:${PATH}"
RUN npm install -g --save-dev @datadog/datadog-ci
RUN  rm -rf "/var/lib/apt/lists/*"