#!/usr/bin/env python3
"""Extracts reference-chains discovery-latency metrics from one repro run's
JFR snapshot: how many datadog.ReferenceChain/ReferenceChainAbandoned events
got recorded, and the wall-clock time from the recording's start to the
first ReferenceChain event (the feature's actual "time to first chain").

`jfr print`/`jfr summary` require a ".jfr" filename extension, which the
repro app's snapshot files (foo.jfr.snapshot) don't have - the caller must
pass a path already renamed/copied to end in .jfr.

Usage: refchains-jfr-metrics.py <path-to.jfr>
Prints one line: "<chain_count> <abandoned_count> <time_to_first_chain_s>"
(time_to_first_chain_s is -1 if no ReferenceChain event was recorded).
"""
import json
import re
import subprocess
import sys
from datetime import datetime, timezone


def run_jfr(args, path):
    try:
        result = subprocess.run(["jfr", *args, path], capture_output=True, text=True, check=True)
    except (subprocess.CalledProcessError, FileNotFoundError) as e:
        stderr = getattr(e, "stderr", None) or str(e)
        print(f"error: 'jfr {' '.join(args)} {path}' failed: {stderr}", file=sys.stderr)
        sys.exit(1)
    return result.stdout


def jfr_recording_start(path):
    out = run_jfr(["summary"], path)
    m = re.search(r"^ Start:\s+(.+?)\s*\(UTC\)\s*$", out, re.MULTILINE)
    if not m:
        return None
    return datetime.strptime(m.group(1).strip(), "%Y-%m-%d %H:%M:%S").replace(tzinfo=timezone.utc)


def jfr_event_times(path, event_name):
    out = run_jfr(["print", "--events", event_name, "--json"], path)
    try:
        data = json.loads(out)
    except json.JSONDecodeError as e:
        print(f"error: could not parse 'jfr print --events {event_name} --json {path}' "
              f"output as JSON: {e}", file=sys.stderr)
        sys.exit(1)
    times = []
    for ev in data.get("recording", {}).get("events", []):
        st = ev.get("values", {}).get("startTime") or ev.get("startTime")
        if st is None:
            continue
        # jfr --json timestamps look like "2026-07-24T11:38:20.123+00:00"
        times.append(datetime.fromisoformat(st.replace("Z", "+00:00")))
    return times


def main():
    if len(sys.argv) < 2:
        print("Usage: refchains-jfr-metrics.py <path-to.jfr>", file=sys.stderr)
        sys.exit(1)
    path = sys.argv[1]
    start = jfr_recording_start(path)
    chain_times = jfr_event_times(path, "datadog.ReferenceChain")
    abandoned_times = jfr_event_times(path, "datadog.ReferenceChainAbandoned")

    chain_count = len(chain_times)
    abandoned_count = len(abandoned_times)
    if chain_times and start is not None:
        first = min(chain_times)
        time_to_first_s = max(0.0, (first - start).total_seconds())
    else:
        time_to_first_s = -1

    print(f"{chain_count} {abandoned_count} {time_to_first_s:.3f}")


if __name__ == "__main__":
    main()
