ARG BASE_IMAGE=openjdk:11-slim-buster
FROM ${BASE_IMAGE} as base
ARG CI_JOB_TOKEN
WORKDIR /root

RUN mkdir -p /usr/share/man/man1 # https://github.com/debuerreotype/docker-debian-artifacts/issues/24
RUN (apt update && DEBIAN_FRONTEND=noninteractive apt install -y --no-install-recommends curl git moreutils awscli amazon-ecr-credential-helper gnupg2 npm build-essential wget bsdmainutils clang libclang-rt-dev jq zip unzip maven) || true
RUN (apk update && apk add curl git moreutils aws-cli docker-credential-ecr-login gnupg alpine-sdk build-base wget npm hexdump linux-headers clang compiler-rt bash jq gradle zip unzip) || true
RUN npm install -g --save-dev @datadog/datadog-ci
RUN  rm -rf "/var/lib/apt/lists/*"