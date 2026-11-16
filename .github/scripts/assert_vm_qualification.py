#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Require real-VM methods to pass, distinguishing unavailable delegated JVM support."""
import argparse
from pathlib import Path
import sys
import xml.etree.ElementTree as ET

PREFIX = "com.datadoghq.profiler.wallclock."
DELEGATED_METHOD = (PREFIX + "HotSpotDelegatedProducerLifecycleTest",
                    "originalJvmStacksAndDirectTaskBlocksSurviveRestart")
EXTENSION_UNAVAILABLE = "HOTSPOT_REQUEST_STACK_TRACE_UNAVAILABLE"
EXPECTED_METHODS = {
    "hotspot": {
        "HotSpotProducerLifecycleTest": "hotspotRecordingAndJniLifecycleSurviveRestart",
        "HotSpotDelegatedProducerLifecycleTest": "originalJvmStacksAndDirectTaskBlocksSurviveRestart",
        "RealVmThreadClassifierTest": "liveJniNullPlatformAndVirtualClassification",
    },
    "openj9": {
        "OpenJ9ProducerLifecycleTest": "genuineOpenJ9RecordingAndJniLifecycleSurviveRestart",
        "OpenJ9CpuProducerLifecycleTest": "genuineOpenJ9CpuSamplesSurviveRestart",
        "RealVmThreadClassifierTest": "liveJniNullPlatformAndVirtualClassification",
    },
}


def verify(vm, results):
    """Check each intended method, not suite totals that can hide skipped qualifications."""
    expected = {(PREFIX + cls, method) for cls, method in EXPECTED_METHODS[vm].items()}
    observed = set()
    deferred = False
    for path in sorted(results.glob("TEST-*.xml")):
        root = ET.parse(path).getroot()
        for case in root.iter("testcase"):
            key = (case.get("classname"), case.get("name", "").removesuffix("()"))
            if key not in expected:
                continue
            failed = any(case.find(tag) is not None for tag in ("failure", "error"))
            skipped = case.find("skipped") is not None
            # Gradle writes empty <skipped/> elements; the test also retains its reason in stdout.
            unavailable = any(EXTENSION_UNAVAILABLE in (out.text or "")
                              for out in root.iter("system-out"))
            if not failed and skipped and key == DELEGATED_METHOD and unavailable:
                deferred = True
            elif failed or skipped:
                raise ValueError("{}#{} did not pass without skips ({})".format(*key, path))
            observed.add(key)
    missing = expected - observed
    if missing:
        raise ValueError("Missing qualification methods: " + ", ".join(
            "{}#{}".format(*key) for key in sorted(missing)))
    return len(observed) - int(deferred), deferred


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--vm", required=True, choices=EXPECTED_METHODS)
    parser.add_argument("--results", required=True, type=Path)
    args = parser.parse_args()
    try:
        count, deferred = verify(args.vm, args.results)
    except (OSError, ET.ParseError, ValueError) as error:
        print("Real-VM qualification failed: " + str(error), file=sys.stderr)
        return 1
    print("Real-VM qualification: {} intended {} methods passed without skips".format(count, args.vm))
    if deferred:
        print("Delegated JVM-stack qualification deferred: " + EXTENSION_UNAVAILABLE)
    return 0


if __name__ == "__main__":
    sys.exit(main())
