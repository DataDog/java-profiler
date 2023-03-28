#!/bin/bash

set -e  # exit on any failure
set -x  # print all executed lines

if [ -z "${JAVA_HOME}" ]; then
  echo "JAVA_HOME is not set"
  exit 1
fi

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

source ${HERE}/include.sh

cd ${HERE}/loadlibs
# build some dynamic libraries to load
g++ -c -fPIC -o increment.o increment.cpp
gcc -shared -o libincrement.so increment.o

g++ -ldl -c -fPIC -I$JAVA_HOME/include/linux/ -I$JAVA_HOME/include/ com_datadoghq_loader_DynamicLibraryLoader.cpp -o com_datadoghq_loader_DynamicLibraryLoader.o
g++ -shared -fPIC -o libloader.so com_datadoghq_loader_DynamicLibraryLoader.o -lc

JFR=/tmp/load-libraries-test.jfr
rm -f $JFR

# need to package the profiler JAR with the native artifacts
# will skip tests and native build because they will be initiated elsewhere
if [ -f ${HERE}/../build/libjavaProfielr.so ]; then
  SKIP_NATIVE_ARG="-Dskip-native"
fi

CLASSPATH=$(find ${HERE}/../target -name 'ddprof-*.jar')

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
$JAVA_HOME/bin/javac -cp $CLASSPATH com/datadoghq/loader/DynamicLibraryLoader.java
$JAVA_HOME/bin/java -cp .:$CLASSPATH \
  -Djava.library.path=. com.datadoghq.loader.DynamicLibraryLoader \
  $JFR ./libincrement.so:increment

# $JAVA_HOME/bin/jfr print --json $JFR
# $JAVA_HOME/bin/jfr summary $JFR


