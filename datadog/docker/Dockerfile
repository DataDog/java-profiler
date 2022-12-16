ARG IMAGE

FROM $IMAGE

COPY build_in_docker.sh /devtools/build_in_docker.sh

RUN mkdir -p /usr/share/man/man1 # https://github.com/debuerreotype/docker-debian-artifacts/issues/24 || true
RUN apt update && DEBIAN_FRONTEND=noninteractive apt install -y --no-install-recommends curl git moreutils build-essential make wget bsdmainutils maven cppcheck unzip zip jq bash