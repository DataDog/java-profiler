#!/bin/bash
# gcbench.sh <lib> <outdir> <runs> <secs> <Xmn> ; modes none lazy gc bggc bg, interleaved
: "${ASM:?set ASM to an asm-9.x jar}"; R=$(cd "$(dirname "$0")/../.." && pwd)
lib=$1; out=$2; runs=$3; secs=$4; xmn=$5
mkdir -p $out
for r in $(seq 1 $runs); do
  for m in none lazy gc bggc bg; do
    case $m in none) cap=0;; lazy) cap=0;; gc) cap=1;; bggc) cap=2;; bg) cap=3;; esac
    agent=""
    [ $m != none ] && agent="-agentpath:$lib=start,cpu=1ms,cstack=vm,fjmethodid=lazy,jfr,file=$out/$m-$r.jfr"
    DDPROF_CAPTURE_UNLOADING=$cap java -XX:+UseG1GC -Xmx1g -Xmn$xmn -Xlog:safepoint:file=$out/$m-$r-sp.log $agent \
      -cp "$ASM:/tmp/p2" GcBench2 $secs > $out/$m-$r.out 2>&1
  done
done
python3 $R/utils/phase2-proto/analyze_sp.py $out none lazy gc bggc bg
