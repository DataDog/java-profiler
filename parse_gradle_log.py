#!/usr/bin/env python3
import re
import json
from datetime import datetime
from pathlib import Path

log_path = "/home/bits/go/src/github.com/DataDog/java-profiler/build/logs/20260126-094600-_ddprof-test_test.log"

# Data structure for JSON output
result = {
    "status": "UNKNOWN",
    "totalTime": None,
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
    "actions": []
}

# Track tasks and their outcomes
tasks = {}
current_task = None
test_output = []
in_test_output = False
build_success = False

with open(log_path, 'r', encoding='utf-8', errors='replace') as f:
    for line in f:
        line = line.rstrip()

        # Task execution patterns
        task_match = re.match(r'^> Task (:[^\s]+)', line)
        if task_match:
            current_task = task_match.group(1)
            if current_task not in tasks:
                tasks[current_task] = {"status": "SUCCESS", "errors": []}

        # Failed task patterns
        if re.match(r'^> Task .* FAILED', line):
            task_failed = re.match(r'^> Task ([^\s]+) FAILED', line)
            if task_failed:
                task_name = task_failed.group(1)
                tasks[task_name] = {"status": "FAILED", "errors": []}
                result["failedTasks"].append({"task": task_name, "errors": []})

        # Test result patterns
        test_summary = re.search(r'(\d+) tests? completed, (\d+) failed, (\d+) skipped', line)
        if test_summary:
            total = int(test_summary.group(1))
            failed = int(test_summary.group(2))
            skipped = int(test_summary.group(3))
            passed = total - failed - skipped

            result["tests"]["total"] += total
            result["tests"]["failed"] += failed
            result["tests"]["skipped"] += skipped
            result["tests"]["passed"] += passed

            if current_task:
                result["tests"]["modules"].append({
                    "task": current_task,
                    "total": total,
                    "failed": failed,
                    "skipped": skipped,
                    "passed": passed
                })

        # Test failure details
        test_fail = re.match(r'^([A-Za-z0-9_$.]+) > ([A-Za-z0-9_$.() ]+) FAILED', line)
        if test_fail:
            test_class = test_fail.group(1)
            test_method = test_fail.group(2)
            test_output.append(f"{test_class}.{test_method}")

        # Exception/error patterns
        if current_task and ("Exception" in line or "Error:" in line or "FAILURE:" in line):
            if current_task in tasks:
                tasks[current_task]["errors"].append(line.strip())
            for ft in result["failedTasks"]:
                if ft["task"] == current_task:
                    ft["errors"].append(line.strip())

        # Deprecation warnings
        if "deprecated" in line.lower() or "deprecation" in line.lower():
            result["warnings"].append(line.strip())

        # Build time
        time_match = re.search(r'BUILD (SUCCESSFUL|FAILED) in (.+)', line)
        if time_match:
            result["status"] = time_match.group(1)
            result["totalTime"] = time_match.group(2)
            build_success = (time_match.group(1) == "SUCCESSFUL")

        # Task timing patterns
        timing_match = re.search(r'Finished .* took (.+)', line)
        if timing_match and current_task:
            result["slowTasks"].append({
                "task": current_task,
                "duration": timing_match.group(1)
            })

        # Dependency/network issues
        if re.search(r'(timeout|401|403|404|artifact not found|could not resolve)', line, re.I):
            result["depIssues"].append(line.strip())

# Extract unique failed tests
if test_output:
    result["tests"]["failedTests"] = test_output

# Generate actionable items
if result["status"] == "FAILED":
    result["actions"].append("Fix failing tests before proceeding")
if result["tests"]["failed"] > 0:
    result["actions"].append(f"Investigate {result['tests']['failed']} test failure(s)")
if result["warnings"]:
    result["actions"].append("Review deprecation warnings")

# Write JSON
Path("/home/bits/go/src/github.com/DataDog/java-profiler/build/reports/claude").mkdir(parents=True, exist_ok=True)
json_path = "/home/bits/go/src/github.com/DataDog/java-profiler/build/reports/claude/gradle-summary.json"
with open(json_path, 'w') as jf:
    json.dump(result, jf, indent=2)

# Generate Markdown summary
md_lines = []
md_lines.append("# Gradle Build Summary")
md_lines.append("")
md_lines.append(f"**Status:** {result['status']}")
md_lines.append(f"**Total Time:** {result['totalTime']}")
md_lines.append("")

# Test summary
md_lines.append("## Test Results")
md_lines.append("")
if result["tests"]["total"] > 0:
    md_lines.append(f"- Total: {result['tests']['total']}")
    md_lines.append(f"- Passed: {result['tests']['passed']}")
    md_lines.append(f"- Failed: {result['tests']['failed']}")
    md_lines.append(f"- Skipped: {result['tests']['skipped']}")
    md_lines.append("")

    if result["tests"]["modules"]:
        md_lines.append("### Test Results by Module")
        md_lines.append("")
        for mod in result["tests"]["modules"]:
            md_lines.append(f"**{mod['task']}**")
            md_lines.append(f"- Total: {mod['total']}, Passed: {mod['passed']}, Failed: {mod['failed']}, Skipped: {mod['skipped']}")
            md_lines.append("")

    if test_output:
        md_lines.append("### Failed Tests")
        md_lines.append("")
        for test in test_output[:20]:  # Limit to first 20
            md_lines.append(f"- {test}")
        if len(test_output) > 20:
            md_lines.append(f"- ... and {len(test_output) - 20} more")
        md_lines.append("")
else:
    md_lines.append("No tests were executed.")
    md_lines.append("")

# Failed tasks
if result["failedTasks"]:
    md_lines.append("## Failed Tasks")
    md_lines.append("")
    for ft in result["failedTasks"]:
        md_lines.append(f"### {ft['task']}")
        md_lines.append("")
        if ft["errors"]:
            for err in ft["errors"][:5]:  # Limit errors
                md_lines.append(f"```")
                md_lines.append(err)
                md_lines.append(f"```")
                md_lines.append("")
        md_lines.append("")

# Warnings
if result["warnings"]:
    md_lines.append("## Warnings")
    md_lines.append("")
    for warn in result["warnings"][:10]:  # Limit warnings
        md_lines.append(f"- {warn}")
    if len(result["warnings"]) > 10:
        md_lines.append(f"- ... and {len(result['warnings']) - 10} more")
    md_lines.append("")

# Dependency issues
if result["depIssues"]:
    md_lines.append("## Dependency/Network Issues")
    md_lines.append("")
    for issue in result["depIssues"][:5]:
        md_lines.append(f"- {issue}")
    md_lines.append("")

# Actions
if result["actions"]:
    md_lines.append("## Recommended Actions")
    md_lines.append("")
    for action in result["actions"]:
        md_lines.append(f"- {action}")
    md_lines.append("")

# Write markdown
md_path = "/home/bits/go/src/github.com/DataDog/java-profiler/build/reports/claude/gradle-summary.md"
with open(md_path, 'w') as mf:
    mf.write('\n'.join(md_lines))

print(f"Analysis complete. Generated {len(md_lines)} lines in summary.")
