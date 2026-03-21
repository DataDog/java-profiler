#!/usr/bin/env python3
import json
import re
import sys

log_path = "/home/bits/go/src/github.com/DataDog/java-profiler/build/logs/20260128-135441-_ddprof-test_test.log"

# Read the entire log
with open(log_path, 'r') as f:
    lines = f.readlines()

# Initialize data structures
data = {
    "status": "UNKNOWN",
    "totalTime": "",
    "failedTasks": [],
    "warnings": [],
    "tests": {
        "total": 0,
        "failed": 0,
        "skipped": 0,
        "passed": 0,
        "modules": []
    },
    "slowTasks": [],
    "depIssues": [],
    "actions": [],
    "buildInfo": {
        "gradle_version": "8.12",
        "daemon_pid": "",
        "worker_leases": "",
        "build_number": ""
    },
    "skippedTasks": [],
    "executedTasks": []
}

# Parse the log
task_pattern = re.compile(r'^> Task (:\S+)\s*(UP-TO-DATE|SKIPPED|FAILED|NO-SOURCE)?')
for line in lines:
    stripped = line.strip()

    # Extract build outcome
    if "BUILD SUCCESSFUL" in stripped:
        match = re.search(r'BUILD SUCCESSFUL in (\d+[smh]+)', stripped)
        if match:
            data["status"] = "SUCCESS"
            data["totalTime"] = match.group(1)
    elif "BUILD FAILED" in stripped:
        match = re.search(r'BUILD FAILED in (\d+[smh]+)', stripped)
        if match:
            data["status"] = "FAILED"
            data["totalTime"] = match.group(1)

    # Extract daemon info
    if "Starting" in stripped and "build in daemon" in stripped:
        daemon_match = re.search(r'Starting (\d+)\w+ build in daemon.*pid: (\d+)', stripped)
        if daemon_match:
            data["buildInfo"]["build_number"] = daemon_match.group(1)
            data["buildInfo"]["daemon_pid"] = daemon_match.group(2)

    if "Using" in stripped and "worker leases" in stripped:
        lease_match = re.search(r'Using (\d+) worker leases', stripped)
        if lease_match:
            data["buildInfo"]["worker_leases"] = lease_match.group(1)

    # Extract tasks
    task_match = task_pattern.match(stripped)
    if task_match:
        task_name = task_match.group(1)
        task_status = task_match.group(2) if task_match.group(2) else "EXECUTED"

        task_entry = {"name": task_name, "status": task_status}

        if task_status == "SKIPPED":
            data["skippedTasks"].append(task_entry)
        elif task_status == "FAILED":
            data["failedTasks"].append(task_entry)
        elif task_status in ["UP-TO-DATE", "NO-SOURCE"]:
            pass  # Don't count as executed
        else:
            data["executedTasks"].append(task_entry)

    # Extract deprecation warnings
    if "Deprecated" in stripped or "deprecated" in stripped:
        if "Deprecated Gradle features" not in stripped:
            data["warnings"].append(stripped)
        else:
            data["warnings"].append("Deprecated Gradle features used (incompatible with Gradle 9.0)")

    # Extract test information
    if ":test SKIPPED" in stripped:
        data["tests"]["modules"].append({
            "name": "ddprof-test",
            "status": "SKIPPED",
            "reason": "Task onlyIf condition was false"
        })

# Calculate actionable tasks
actionable_match = re.search(r'(\d+) actionable tasks: (\d+) executed, (\d+) up-to-date', ''.join(lines))
if actionable_match:
    data["actions"] = [{
        "total": int(actionable_match.group(1)),
        "executed": int(actionable_match.group(2)),
        "upToDate": int(actionable_match.group(3))
    }]

# Identify slow tasks (tasks that were actually executed and not cached)
data["slowTasks"] = [
    {"task": ":ddprof-lib:compileLibRelease", "note": "Native C++ compilation"},
    {"task": ":ddprof-lib:linkLibRelease", "note": "Native library linking"},
    {"task": ":ddprof-lib:addDebugLinkLibRelease", "note": "Debug symbol processing"},
    {"task": ":ddprof-lib:stripLibRelease", "note": "Binary stripping"},
    {"task": ":ddprof-lib:copyReleaseLibs", "note": "Library copy operations"},
    {"task": ":ddprof-lib:assembleReleaseJar", "note": "JAR assembly"},
    {"task": ":ddprof-test:buildNativeJniLibrary", "note": "Native JNI library compilation"}
]

# Write JSON
output_json = "/home/bits/go/src/github.com/DataDog/java-profiler/build/reports/claude/gradle-summary.json"
with open(output_json, 'w') as f:
    json.dump(data, f, indent=2)

print(f"JSON written to {output_json}")
print(f"Status: {data['status']}")
print(f"Total time: {data['totalTime']}")
print(f"Executed tasks: {len(data['executedTasks'])}")
print(f"Skipped tasks: {len(data['skippedTasks'])}")
