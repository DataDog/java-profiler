#! /bin/bash
set +x
# shellcheck disable=SC1091  # path is relative to $0 of the caller's invocation
. "$(dirname "$0")/collect_markers.sh"
ctl_file=$1
out=$2
# Overridable roots let tests drive the sampler against fake trees
markers_proc_root=${MEMWATCH_PROC_ROOT:-/proc}
markers_cgroup_root=${MEMWATCH_CGROUP_ROOT:-/sys/fs/cgroup}
# The harness exports the launched JVM's pid; the ps text match below can
# otherwise select a sibling process carrying the same tokens.
target_pid=${MEMWATCH_TARGET_PID:-}
# shellcheck disable=SC2086  # preserved byte-identical from the original sampler
while [ -f $ctl_file ]; do
    if [ -n "$target_pid" ]; then
        pid=$target_pid
    else
        # shellcheck disable=SC2009  # pid discovery is preserved byte-identical
        pid=$(ps ax | grep 'java' | grep "${ctl_file}" | grep -v 'grep' | grep -v 'time' | sed -e 's/^[[:space:]]*//' | cut -f1 -d' ')
    fi
    if [ -n "${pid}" ]; then
        rss="$(grep 'Rss:' "${markers_proc_root}/${pid}/smaps_rollup" 2>/dev/null | cut -f2 -d':' | sed -e 's/^[[:space:]]*//' | cut -f1 -d' ')"
        if [ -n "$rss" ]; then
            # shellcheck disable=SC2086  # preserved byte-identical from the original sampler
            echo "mem: $rss" | tee -a $out
            # $$ excludes this sampler and its discovery children from the census
            echo "markers: $(collect_markers "$markers_proc_root" "$markers_cgroup_root" "$pid" "$$")" | tee -a "$out"
        fi
    fi
    sleep 5
done