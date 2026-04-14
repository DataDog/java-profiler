ARG BASE_IMAGE=openjdk:11-slim-buster
FROM ${BASE_IMAGE} as base
ARG CI_JOB_TOKEN
WORKDIR /root

# 1. Replace dead mirrorlist entries with HTTPS vault URLs
RUN set -eux; \
    sed -i -e 's/^mirrorlist/#mirrorlist/' \
           -e 's|^#baseurl=http://mirror.centos.org|baseurl=https://vault.centos.org|' \
           /etc/yum.repos.d/CentOS-*.repo

# 2. Add a vault mirror that still contains Software Collections
RUN cat > /etc/yum.repos.d/CentOS-SCLo-Vault.repo <<'EOF'
[centos-sclo-rh]
name=CentOS-7 - SCLo rh (Rocky Vault)
baseurl=https://dl.rockylinux.org/vault/centos/7.9.2009/sclo/$basearch/rh/
gpgcheck=0
enabled=1

[centos-sclo-sclo]
name=CentOS-7 - SCLo sclo (Rocky Vault)
baseurl=https://dl.rockylinux.org/vault/centos/7.9.2009/sclo/$basearch/sclo/
gpgcheck=0
enabled=1
EOF

# 3. Expose devtoolset-11 binaries & libs by default (they are installed a bit later)
ENV PATH="/opt/rh/devtoolset-11/root/usr/bin:${PATH}" \
    LD_LIBRARY_PATH="/opt/rh/devtoolset-11/root/usr/lib64:${LD_LIBRARY_PATH}"

RUN yum -y clean all
RUN yum -y update && yum -y install scl-utils devtoolset-11 devtoolset-11-toolchain curl zip unzip git libstdc++-static make which wget cmake binutils
RUN yum -y clean all
RUN (curl -s "https://get.sdkman.io" | bash)
RUN (source ~/.sdkman/bin/sdkman-init.sh && sdk install java 21.0.3-tem)
RUN (curl -sL https://rpm.nodesource.com/setup_16.x | bash -)
# installing JQ requires two steps - adding the repo and then installing the tool
RUN yum install -y epel-release
RUN yum install -y jq
# now install nodejs and datadog CI support
RUN yum -y install nodejs
RUN npm install -g --save-dev @datadog/datadog-ci
RUN  rm -rf "/var/lib/apt/lists/*"