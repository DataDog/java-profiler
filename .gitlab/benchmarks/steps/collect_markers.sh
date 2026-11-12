#! /bin/sh
# Copyright 2026, Datadog, Inc.
#
# Sourced by mem_watch.sh (POSIX sh only). Reads load markers from the
# proc and cgroup trees without touching the watched JVM; a missing or
# unreadable source yields the literal NA.

# Prints the some avg10= value of a PSI file, or NA when unavailable.
markers_psi_avg10() {
    markers_value=$(sed -n 's/^some avg10=\([0-9][0-9.]*\).*/\1/p' "$1" 2>/dev/null)
    if [ -n "$markers_value" ]; then
        printf '%s\n' "$markers_value"
    else
        printf 'NA\n'
    fi
}

# Prints field 1 of <proc root>/loadavg, or NA when unavailable.
markers_loadavg_1m() {
    markers_value=$(sed -n '1s/^\([^ ][^ ]*\).*/\1/p' "$1/loadavg" 2>/dev/null)
    if [ -n "$markers_value" ]; then
        printf '%s\n' "$markers_value"
    else
        printf 'NA\n'
    fi
}

# Prints nr_throttled from the cgroup cpu.stat, or NA. v2 is detected via
# cgroup.controllers; v1 lives under cpu,cpuacct/ or cpu/.
markers_nr_throttled() {
    markers_stat_file=
    if [ -f "$1/cgroup.controllers" ]; then
        markers_stat_file="$1/cpu.stat"
    elif [ -f "$1/cpu,cpuacct/cpu.stat" ]; then
        markers_stat_file="$1/cpu,cpuacct/cpu.stat"
    elif [ -f "$1/cpu/cpu.stat" ]; then
        markers_stat_file="$1/cpu/cpu.stat"
    fi
    markers_value=$(sed -n 's/^nr_throttled \([0-9][0-9]*\).*/\1/p' "$markers_stat_file" 2>/dev/null)
    if [ -n "$markers_value" ]; then
        printf '%s\n' "$markers_value"
    else
        printf 'NA\n'
    fi
}

# Prints the number of R-state stat entries under the proc root, skipping
# the excluded pids and all their descendants (the JVM, the sampler and the
# sampler's ps/grep discovery pipeline). The census runs inside command
# substitutions, so its own cat|awk collectors are grandchildren of the
# sampler shell and a direct-parent check would count them; each runnable
# entry is therefore kept only when no ancestor on its parent chain is
# excluded. The cat|awk pipeline reads every entry per tick: cat skips entries
# that vanish between glob expansion and open, where a direct awk pass aborts
# fatally.
markers_cotenant_runnable() {
    markers_root=$1
    shift
    markers_exclude=$1
    shift
    for markers_excl in "$@"; do
        markers_exclude="${markers_exclude},${markers_excl}"
    done
    # shellcheck disable=SC2016  # the awk program quotes its own variables
    # shellcheck disable=SC2002  # cat is deliberate: it tolerates unreadable
    # stat entries instead of aborting the awk END rule
    markers_count=$(cat "$markers_root"/[0-9]*/stat 2>/dev/null | awk -v excl="$markers_exclude" '
        BEGIN { n = split(excl, e, ","); for (i = 1; i <= n; i++) ex[e[i]] = 1 }
        {
            seen = 1
            pid = $0
            sub(/ .*/, "", pid)
            # comm may hold spaces and ), so fields restart after the last )
            sub(/.*\)/, "", $0)
            split($0, f, " ")
            parent[pid] = f[2]
            if (f[1] == "R") runnable[pid] = 1
        }
        END {
            if (!seen) { print "NA"; exit }
            for (pid in runnable) {
                ancestor = pid
                while (ancestor && !ex[ancestor] && ancestor != parent[ancestor])
                    ancestor = parent[ancestor]
                if (!ex[ancestor]) count++
            }
            print count + 0
        }
    ')
    if [ -n "$markers_count" ]; then
        printf '%s\n' "$markers_count"
    else
        printf 'NA\n'
    fi
}

# Emits one token string: $1 proc root, $2 cgroup root, $3... pids to
# exclude from the co-tenant census.
collect_markers() {
    markers_proc=$1
    markers_cg=$2
    shift 2
    printf 'psi_cpu_some_avg10=%s psi_memory_some_avg10=%s loadavg_1m=%s cpu_nr_throttled=%s cotenant_runnable=%s\n' \
        "$(markers_psi_avg10 "$markers_proc/pressure/cpu")" \
        "$(markers_psi_avg10 "$markers_proc/pressure/memory")" \
        "$(markers_loadavg_1m "$markers_proc")" \
        "$(markers_nr_throttled "$markers_cg")" \
        "$(markers_cotenant_runnable "$markers_proc" "$@")"
}
