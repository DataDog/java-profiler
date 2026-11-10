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

# True when $1 (pid) or $2 (ppid) equals one of the remaining arguments.
markers_excluded() {
    markers_ex_pid=$1
    markers_ex_ppid=$2
    shift 2
    for markers_excl in "$@"; do
        [ "$markers_ex_pid" = "$markers_excl" ] && return 0
        [ "$markers_ex_ppid" = "$markers_excl" ] && return 0
    done
    return 1
}

# Prints the number of R-state stat entries under the proc root, skipping
# the excluded pids and their direct children (the JVM, the sampler and
# the sampler's ps/grep discovery pipeline).
markers_cotenant_runnable() {
    markers_root=$1
    shift
    markers_count=0
    markers_seen=0
    for markers_entry in "$markers_root"/[0-9]*; do
        [ -f "$markers_entry/stat" ] || continue
        markers_seen=1
        read -r markers_line < "$markers_entry/stat" 2>/dev/null
        [ -n "$markers_line" ] || continue
        # comm may hold spaces and ')', so fields restart after the last ') '
        markers_fields=${markers_line##*) }
        markers_state=${markers_fields%% *}
        [ "$markers_state" = "R" ] || continue
        markers_pid=${markers_line%% *}
        markers_after=${markers_fields#* }
        markers_ppid=${markers_after%% *}
        if markers_excluded "$markers_pid" "$markers_ppid" "$@"; then
            continue
        fi
        markers_count=$((markers_count + 1))
    done
    if [ "$markers_seen" -eq 0 ]; then
        printf 'NA\n'
    else
        printf '%s\n' "$markers_count"
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
