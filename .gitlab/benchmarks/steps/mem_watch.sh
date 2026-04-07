#! /bin/bash
set +x
ctl_file=$1
out=$2
while [ -f $ctl_file ]; do
    pid=$(ps ax | grep 'java' | grep "${ctl_file}" | grep -v 'grep' | grep -v 'time' | sed -e 's/^[[:space:]]*//' | cut -f1 -d' ')
    if [ -n "${pid}" ]; then
        rss="$(cat /proc/${pid}/smaps_rollup | grep 'Rss:' | cut -f2 -d':' |  sed -e 's/^[[:space:]]*//' | cut -f1 -d' ' 2>/dev/null)"
        if [ -n "$rss" ]; then
            echo "mem: $rss" | tee -a $out
        fi
    fi
    sleep 5
done