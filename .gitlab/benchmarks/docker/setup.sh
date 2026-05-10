#!/bin/bash

set -e
set -x

apt update && apt install -y wget curl zip unzip time maven jq git libjemalloc-dev libtcmalloc-minimal4

pip install numpy matplotlib

# debug output
#echo $JAVA_HOME
#mvn -version

# retrieve the standard benchmark apps
mkdir -p /var/lib/benchmarks
wget -q -O /var/lib/benchmarks/renaissance.jar https://github.com/renaissance-benchmarks/renaissance/releases/download/v0.15.0/renaissance-mit-0.15.0.jar
wget -q -O /var/lib/dacapo.jar https://netix.dl.sourceforge.net/project/dacapobench/9.12-bach-MR1/dacapo-9.12-MR1-bach.jar

