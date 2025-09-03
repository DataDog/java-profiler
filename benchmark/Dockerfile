# Dacapo download
FROM debian:bookworm-slim as benchmarks
RUN apt-get update \
  && apt-get -y install wget unzip libc6 \
  && apt-get -y clean \
  && rm -rf /var/lib/apt/lists/*

ARG DACAPO_VERSION=23.11-chopin
# The data for the big benchmarks is removed too ensure the final docker image is not too big
RUN wget -nv -O dacapo.zip https://download.dacapobench.org/chopin/dacapo-$DACAPO_VERSION.zip \
	&& mkdir /dacapo \
	&& unzip dacapo.zip -d /dacapo/ \
	&& rm -rf /dacapo/dacapo-$DACAPO_VERSION/dat/luindex \
	&& rm -rf /dacapo/dacapo-$DACAPO_VERSION/dat/lusearch \
	&& rm -rf /dacapo/dacapo-$DACAPO_VERSION/dat/graphchi \
	&& rm dacapo.zip

# Download and install renaissance benchmark
ARG RENAISSANCE_VERSION=0.16.0
RUN mkdir /renaissance \
    && wget -nv -O  ./renaissance/renaissance-gpl.jar https://github.com/renaissance-benchmarks/renaissance/releases/download/v${RENAISSANCE_VERSION}/renaissance-gpl-${RENAISSANCE_VERSION}.jar

FROM debian:bookworm-slim

RUN apt-get update \
  && apt-get -y install git curl wget procps gettext-base \
  && apt-get -y clean \
  && rm -rf /var/lib/apt/lists/*

COPY --from=eclipse-temurin:8-jammy /opt/java/openjdk /usr/lib/jvm/8
COPY --from=eclipse-temurin:11-jammy /opt/java/openjdk /usr/lib/jvm/11
COPY --from=eclipse-temurin:17-jammy /opt/java/openjdk /usr/lib/jvm/17

RUN rm -rf \
    /usr/lib/jvm/*/man \
    /usr/lib/jvm/*/src.zip \
    /usr/lib/jvm/*/lib/src.zip \
    /usr/lib/jvm/*/demo \
    /usr/lib/jvm/*/sample

ENV JAVA_8_HOME=/usr/lib/jvm/8
ENV JAVA_11_HOME=/usr/lib/jvm/11
ENV JAVA_17_HOME=/usr/lib/jvm/17
ENV JAVA_HOME=${JAVA_8_HOME}
ENV PATH=${PATH}:${JAVA_HOME}/bin

ARG SIRUN_VERSION=0.1.11
RUN wget -O sirun.tar.gz https://github.com/DataDog/sirun/releases/download/v$SIRUN_VERSION/sirun-v$SIRUN_VERSION-x86_64-unknown-linux-musl.tar.gz \
	&& tar -xzf sirun.tar.gz \
	&& rm sirun.tar.gz \
  && mv sirun /usr/bin/sirun

ARG K6_VERSION=0.45.1
RUN wget -O k6.tar.gz https://github.com/grafana/k6/releases/download/v$K6_VERSION/k6-v$K6_VERSION-linux-amd64.tar.gz \
	&& tar --strip-components=1 -xzf k6.tar.gz \
	&& rm k6.tar.gz \
  && mv k6 /usr/bin/k6

RUN mkdir -p /app

COPY --from=benchmarks /dacapo/ /app/
ARG DACAPO_VERSION=23.11-chopin
ENV DACAPO=/app/dacapo-$DACAPO_VERSION.jar

COPY --from=benchmarks /renaissance/ /app/
ENV RENAISSANCE=/app/renaissance-gpl.jar
