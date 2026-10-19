#!/bin/bash
# bench3.sh <lib> <out_prefix> <capture 0-3> <dump_s> <gen_ms> <run_s> [extra jvm opts]; G1 unless opts pick a GC
: "${ASM:?set ASM to an asm-9.x jar}"; : "${CLS:?set CLS to ddprof-lib/build/classes/java/main}"
lib=$1; out=$2; cap=$3; d=$4; g=$5; r=$6; shift 6
gc=-XX:+UseG1GC; case "$*" in *Use*GC*) gc=;; esac
DDPROF_CAPTURE_UNLOADING=$cap java $gc "$@" -cp "$ASM:$CLS:/tmp/p2" Bench3 $lib $d $g $r > $out.txt 2>&1
