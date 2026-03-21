#!/usr/bin/env python3
import re
import json
from collections import defaultdict
import sys

log_path = "/home/bits/go/src/github.com/DataDog/java-profiler/build/logs/20260128-142001-_ddprof-test_testDebug.log"

# Initialize data structures
data = {
    "status": "UNKNOWN",
    "totalTime": "",
    "failedTasks": [],
    "warnings": [],
    "tests": {
        "total": 0,
        "passed": 0,
        "failed": 0,
        "skipped": 0,
        "modules": []
    },
    "slowTasks": [],
    "depIssues": [],
    "actions": [],
    "tasks": [],
    "configurationCache": None
}

tasks = {}
test_modules = defaultdict(lambda: {"total": 0, "passed": 0, "failed": 0, "skipped": 0, "failures": []})
warnings = []
dep_issues = []

# Read and parse the log file
with open(log_path, 'r', encoding='utf-8', errors='ignore') as f:
    lines = f.readlines()

# Parse line by line
current_module = None
for i, line in enumerate(lines):
    # Build status
    if "BUILD SUCCESSFUL" in line:
        data["status"] = "SUCCESS"
        match = re.search(r'in (.+)$', line)
        if match:
            data["totalTime"] = match.group(1).strip()
    elif "BUILD FAILED" in line:
        data["status"] = "FAILED"
        match = re.search(r'in (.+)$', line)
        if match:
            data["totalTime"] = match.group(1).strip()

    # Task execution - track current module
    task_match = re.match(r'^> Task (:[^:\s]+):(\w+)', line)
    if task_match:
        task_name = task_match.group(1) + ":" + task_match.group(2)
        task_type = task_match.group(2)

        if task_type == "test":
            current_module = task_match.group(1)

        # Check if task failed
        if "FAILED" in line:
            tasks[task_name] = {"name": task_name, "status": "FAILED"}
            data["failedTasks"].append({"task": task_name, "error": "Task failed"})
        else:
            tasks[task_name] = {"name": task_name, "status": "EXECUTED"}

    # Test results summary
    test_result = re.search(r'(\d+) tests? completed(?:, (\d+) failed)?(?:, (\d+) skipped)?', line)
    if test_result:
        total = int(test_result.group(1))
        failed = int(test_result.group(2)) if test_result.group(2) else 0
        skipped = int(test_result.group(3)) if test_result.group(3) else 0
        passed = total - failed - skipped

        if current_module:
            test_modules[current_module]["total"] = total
            test_modules[current_module]["passed"] = passed
            test_modules[current_module]["failed"] = failed
            test_modules[current_module]["skipped"] = skipped

        data["tests"]["total"] += total
        data["tests"]["failed"] += failed
        data["tests"]["skipped"] += skipped
        data["tests"]["passed"] += passed

    # Individual test failures
    test_fail = re.match(r'^  (.+?) > (.+?) (FAILED)', line)
    if test_fail and current_module:
        test_class = test_fail.group(1).strip()
        test_method = test_fail.group(2).strip()

        test_modules[current_module]["failures"].append({
            "class": test_class,
            "method": test_method
        })

    # Warnings
    if "warning:" in line.lower() or "deprecated" in line.lower():
        if len(line.strip()) > 10:
            warnings.append(line.strip()[:200])

    # Configuration cache
    if "Configuration cache entry" in line:
        if "reused" in line:
            data["configurationCache"] = "reused"
        elif "stored" in line:
            data["configurationCache"] = "stored"

    # Dependency issues
    if any(x in line for x in ["Could not resolve", "timeout", "401", "403", "404"]):
        if any(x in line.lower() for x in ["dependency", "artifact", "http", "repository"]):
            dep_issues.append(line.strip()[:200])

# Build test modules summary
for module, stats in test_modules.items():
    module_data = {
        "name": module,
        "total": stats["total"],
        "passed": stats["passed"],
        "failed": stats["failed"],
        "skipped": stats["skipped"]
    }
    if stats["failures"]:
        module_data["failures"] = stats["failures"][:10]
    data["tests"]["modules"].append(module_data)

# Extract task timing
for line in lines:
    timing_match = re.search(r'Task (:[^\s]+)\s+took\s+([\d.]+)s', line)
    if timing_match:
        task_name = timing_match.group(1)
        duration = float(timing_match.group(2))
        if task_name not in tasks:
            tasks[task_name] = {"name": task_name, "status": "EXECUTED"}
        tasks[task_name]["duration_sec"] = duration

# Sort tasks by duration
slow_tasks = []
for task_name, task_data in tasks.items():
    if "duration_sec" in task_data:
        slow_tasks.append({
            "task": task_name,
            "duration": f"{task_data['duration_sec']:.1f}s",
            "duration_sec": task_data["duration_sec"]
        })

slow_tasks.sort(key=lambda x: x["duration_sec"], reverse=True)
data["slowTasks"] = [{"task": t["task"], "duration": t["duration"]} for t in slow_tasks[:10]]

# Deduplicate and limit
data["warnings"] = list(set(warnings))[:20]
data["depIssues"] = list(set(dep_issues))[:10]
data["tasks"] = [{"name": name, "status": info.get("status", "EXECUTED")} for name, info in tasks.items()]

# Generate actions
if data["status"] == "FAILED":
    data["actions"].append("Investigate failed tasks and fix errors")
if data["tests"]["failed"] > 0:
    data["actions"].append(f"Fix {data['tests']['failed']} failing test(s)")
if data["warnings"]:
    data["actions"].append("Review and address warnings")
if data["depIssues"]:
    data["actions"].append("Resolve dependency issues")

print(json.dumps(data, indent=2))
