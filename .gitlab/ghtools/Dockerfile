FROM --platform=linux/amd64 registry.ddbuild.io/images/benchmarking-platform-tools-ubuntu:newest
ARG CI_JOB_TOKEN

COPY ./setup.sh /tmp/setup.sh
RUN /tmp/setup.sh $CI_JOB_TOKEN