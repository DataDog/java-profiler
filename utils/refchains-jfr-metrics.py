#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc
"""Extracts reference-chains discovery-latency metrics from ALL JFR snapshot
files of one repro run: how many datadog.ReferenceChain/ReferenceChainAbandoned
events got recorded (summed across the files), and the wall-clock time from the
recording's ORIGINAL start to the earliest ReferenceChain event in any file (the
feature's actual "time to first chain").

Each periodic dump() finishes a chunk, so every snapshot file holds one chunk
whose `jfr summary` Start is the previous dump - and cached chains are
re-stamped into every dump. Measuring against each file's chunk Start would
therefore collapse to ~one dump interval. The origin is instead the original
recording start: jdk.ActiveRecording's recordingStart (rewritten into every
chunk), falling back to its startTime, then to the `jfr summary` Start.
Resolution is one dump interval, because chains are stamped at dump time.

`jfr print`/`jfr summary` require a ".jfr" filename extension, which the
repro app's snapshot files (foo.jfr.snapshot) don't have - the caller must
pass paths already renamed/copied to end in .jfr.

The `jfr` tool is taken from $REFCHAINS_JAVA_HOME/bin when that variable is set
(the same JDK the repro ran on; a missing/non-executable tool there is a hard
error, never a silent fallback to PATH), otherwise from PATH.

Usage: refchains-jfr-metrics.py <snap.jfr> [<snap.jfr>...]
Prints one line: "<chain_count> <abandoned_count> <time_to_first_chain_s>"
(time_to_first_chain_s is -1 if no ReferenceChain event or no recording start
was found). An unreadable snapshot is skipped with a warning on stderr; the
exit status is 1 when no file could be read or REFCHAINS_JAVA_HOME is bad.
"""
import json
import os
import re
import subprocess
import sys
from datetime import datetime, timezone

JFR_BIN = "jfr"


class JfrError(Exception):
    """A jfr invocation failed or produced unparseable output for one file."""


def resolve_jfr():
    """Mirror run-refchains-repro.sh's choice of `java`: the JDK selected by
    REFCHAINS_JAVA_HOME when set and non-empty, else PATH."""
    java_home = os.environ.get("REFCHAINS_JAVA_HOME", "")
    if not java_home:
        return "jfr"
    jfr = os.path.join(java_home, "bin", "jfr")
    if not (os.path.isfile(jfr) and os.access(jfr, os.X_OK)):
        print(f"error: {jfr} not found/executable - check REFCHAINS_JAVA_HOME", file=sys.stderr)
        sys.exit(1)
    return jfr


def run_jfr(args, path):
    try:
        result = subprocess.run([JFR_BIN, *args, path], capture_output=True, text=True, check=True)
    except (subprocess.CalledProcessError, OSError) as e:
        stderr = getattr(e, "stderr", None) or str(e)
        print(f"error: '{JFR_BIN} {' '.join(args)} {path}' failed: {stderr}", file=sys.stderr)
        raise JfrError(path) from e
    return result.stdout


_ISO_FRACTION = re.compile(r"^(.*T\d{2}:\d{2}:\d{2})(?:\.(\d+))?(.*)$")


def parse_ts(v):
    """Epoch-millis number or ISO-8601 string -> aware datetime; None if unparseable."""
    if v is None or isinstance(v, bool):
        return None
    if isinstance(v, (int, float)):
        try:
            return datetime.fromtimestamp(v / 1000.0, tz=timezone.utc)
        except (OverflowError, OSError, ValueError):
            return None
    if not isinstance(v, str):
        return None
    s = v.strip().replace("Z", "+00:00")
    # Python < 3.11 fromisoformat accepts only 3 or 6 fraction digits; jfr may
    # print 0-9, so normalise to exactly 6.
    m = _ISO_FRACTION.match(s)
    if m:
        frac = (m.group(2) or "")[:6].ljust(6, "0")
        s = f"{m.group(1)}.{frac}{m.group(3)}"
    try:
        dt = datetime.fromisoformat(s)
    except ValueError:
        return None
    if dt.tzinfo is None:
        dt = dt.replace(tzinfo=timezone.utc)
    return dt


def jfr_events(path, event_name):
    out = run_jfr(["print", "--events", event_name, "--json"], path)
    try:
        data = json.loads(out)
    except json.JSONDecodeError as e:
        print(f"error: could not parse '{JFR_BIN} print --events {event_name} --json {path}' "
              f"output as JSON: {e}", file=sys.stderr)
        raise JfrError(path) from e
    return data.get("recording", {}).get("events", []) or []


def jfr_event_times(path, event_name):
    times = []
    for ev in jfr_events(path, event_name):
        t = parse_ts(ev.get("values", {}).get("startTime") or ev.get("startTime"))
        if t is not None:
            times.append(t)
    return times


def jfr_recording_start(path):
    """The file's chunk Start (1s resolution) - only the last-resort origin."""
    out = run_jfr(["summary"], path)
    m = re.search(r"^ Start:\s+(.+?)\s*\(UTC\)\s*$", out, re.MULTILINE)
    if not m:
        return None
    try:
        return datetime.strptime(m.group(1).strip(), "%Y-%m-%d %H:%M:%S").replace(tzinfo=timezone.utc)
    except ValueError:
        return None


def jfr_recording_origin(path):
    # jdk.ActiveRecording is rewritten into every chunk with the ORIGINAL
    # recording start, which a chunk switch does not reset.
    origins = []
    for ev in jfr_events(path, "jdk.ActiveRecording"):
        vals = ev.get("values", {})
        t = parse_ts(vals.get("recordingStart"))
        if t is None:
            t = parse_ts(vals.get("startTime") or ev.get("startTime"))
        if t is not None:
            origins.append(t)
    if origins:
        return min(origins)
    return jfr_recording_start(path)


def main():
    global JFR_BIN
    paths = sys.argv[1:]
    if not paths:
        print("Usage: refchains-jfr-metrics.py <snap.jfr> [<snap.jfr>...]", file=sys.stderr)
        sys.exit(1)
    JFR_BIN = resolve_jfr()

    chain_count = 0
    abandoned_count = 0
    chain_times = []
    origins = []
    read_ok = 0
    for path in paths:
        try:
            origin = jfr_recording_origin(path)
            times = jfr_event_times(path, "datadog.ReferenceChain")
            abandoned = len(jfr_events(path, "datadog.ReferenceChainAbandoned"))
        except JfrError:
            print(f"warning: skipping unreadable snapshot {path}", file=sys.stderr)
            continue
        read_ok += 1
        if origin is not None:
            origins.append(origin)
        chain_times.extend(times)
        chain_count += len(times)
        abandoned_count += abandoned

    if read_ok == 0:
        print("error: no snapshot file could be read", file=sys.stderr)
        sys.exit(1)

    if chain_times and origins:
        time_to_first_s = max(0.0, (min(chain_times) - min(origins)).total_seconds())
    else:
        time_to_first_s = -1
    print(f"{chain_count} {abandoned_count} {time_to_first_s:.3f}")


if __name__ == "__main__":
    main()
