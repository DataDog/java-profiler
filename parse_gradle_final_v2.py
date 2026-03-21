#!/usr/bin/env python3
import json
import re
from collections import defaultdict

log_path = "/home/bits/go/src/github.com/DataDog/java-profiler/build/logs/20260129-121048-_ddprof-test_test.log"
json_path = "/home/bits/go/src/github.com/DataDog/java-profiler/build/reports/claude/gradle-summary.json"
md_path = "/home/bits/go/src/github.com/DataDog/java-profiler/build/reports/claude/gradle-summary.md"

# Initialize data structures
data = {
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
    "actions": [],
    "tasksSummary": {
        "executed": 0,
        "upToDate": 0,
        "skipped": 0,
        "noSource": 0
    }
}

# Parse log file
with open(log_path, 'r', encoding='utf-8', errors='ignore') as f:
    lines = f.readlines()

# Track state
task_times = {}
failure_details = []
test_modules = defaultdict(lambda: {"total": 0, "failed": 0, "skipped": 0, "passed": 0, "failures": []})
current_module = None
tasks_executed = []

for i, line in enumerate(lines):
    line = line.rstrip()

    # Build status and time
    match = re.search(r'BUILD SUCCESSFUL in ([\d.]+\w+)', line)
    if match:
        data["status"] = "SUCCESS"
        data["totalTime"] = match.group(1)

    match = re.search(r'BUILD FAILED in ([\d.]+\w+)', line)
    if match:
        data["status"] = "FAILED"
        data["totalTime"] = match.group(1)

    # Alternative time format
    match = re.search(r'Total time:\s+([\d.]+\s+\w+)', line)
    if match and not data["totalTime"]:
        data["totalTime"] = match.group(1)

    # Task execution status
    match = re.search(r'> Task (:\S+)\s+(UP-TO-DATE|SKIPPED|NO-SOURCE|FAILED)?', line)
    if match:
        task_name = match.group(1)
        task_status = match.group(2) if match.group(2) else "EXECUTED"
        tasks_executed.append({"task": task_name, "status": task_status})

        if task_status == "EXECUTED" or not task_status:
            data["tasksSummary"]["executed"] += 1
        elif task_status == "UP-TO-DATE":
            data["tasksSummary"]["upToDate"] += 1
        elif task_status == "SKIPPED":
            data["tasksSummary"]["skipped"] += 1
        elif task_status == "NO-SOURCE":
            data["tasksSummary"]["noSource"] += 1
        elif task_status == "FAILED":
            data["failedTasks"].append(task_name)

    # Task summary line at end
    match = re.search(r'(\d+) actionable tasks: (\d+) executed(?:, (\d+) up-to-date)?', line)
    if match:
        total = int(match.group(1))
        executed = int(match.group(2))
        up_to_date = int(match.group(3)) if match.group(3) else 0

    # Module detection
    match = re.search(r'> Task (:\S+?):(\w+)', line)
    if match:
        current_module = match.group(1)

    # Test results - summary line
    match = re.search(r'(\d+) tests completed, (\d+) failed, (\d+) skipped', line)
    if match:
        total = int(match.group(1))
        failed = int(match.group(2))
        skipped = int(match.group(3))
        passed = total - failed - skipped
        data["tests"]["total"] += total
        data["tests"]["failed"] += failed
        data["tests"]["skipped"] += skipped
        data["tests"]["passed"] += passed

        if current_module:
            test_modules[current_module]["total"] = total
            test_modules[current_module]["failed"] = failed
            test_modules[current_module]["skipped"] = skipped
            test_modules[current_module]["passed"] = passed

    # Failed test detection
    match = re.search(r'(\S+Test)\s+>\s+(\S+)\s+FAILED', line)
    if match:
        test_class = match.group(1)
        test_method = match.group(2)
        failure_name = f"{test_class}.{test_method}"
        failure_details.append(failure_name)
        if current_module:
            test_modules[current_module]["failures"].append(failure_name)

    # Exception detection
    match = re.search(r'(java\.\S+Exception|Error):\s+(.+)', line)
    if match and i < len(lines) - 1:
        exception_type = match.group(1)
        exception_msg = match.group(2)
        if exception_msg not in [f["message"] for f in failure_details if isinstance(f, dict)]:
            failure_details.append({"type": exception_type, "message": exception_msg})

    # Warnings (deduplicate repeated warnings)
    if 'warning:' in line.lower():
        warning = line.strip()
        if warning not in data["warnings"] and len(data["warnings"]) < 10:
            data["warnings"].append(warning)

    # Count repeated warnings
    match = re.search(r'(\d+) warnings', line)
    if match:
        warning_count = int(match.group(1))
        if warning_count > len(data["warnings"]):
            data["warnings"].append(f"(Plus {warning_count - len(data['warnings'])} more similar warnings)")

    # Deprecation warnings
    if 'Deprecated Gradle features' in line:
        data["warnings"].append(line.strip())

    # Dependency issues
    if any(x in line for x in ['Could not resolve', 'not found', '401', '403', 'timeout', 'Failed to download']):
        if 'class file for' in line and 'not found' in line:
            data["depIssues"].append(line.strip())
        else:
            data["depIssues"].append(line.strip())

# Add module details
for module, stats in test_modules.items():
    data["tests"]["modules"].append({
        "name": module,
        "total": stats["total"],
        "passed": stats["passed"],
        "failed": stats["failed"],
        "skipped": stats["skipped"],
        "failures": stats["failures"]
    })

# Add actions
if data["status"] == "FAILED":
    data["actions"].append("Review test failures in detail")
    data["actions"].append("Check test reports in build/reports/tests/")
    if failure_details:
        data["actions"].append(f"Focus on {len(failure_details)} failing test(s)")
elif data["status"] == "SUCCESS":
    if data["tasksSummary"]["skipped"] > 0:
        data["actions"].append(f"Build completed successfully ({data['tasksSummary']['skipped']} tasks skipped)")
    else:
        data["actions"].append("Build completed successfully")
    if data["warnings"]:
        data["actions"].append(f"Review {len(data['warnings'])} warning(s)")

# Write JSON output
with open(json_path, 'w') as f:
    json.dump(data, f, indent=2)

# Generate Markdown summary
md_lines = []
md_lines.append("# Gradle Build Summary\n")
md_lines.append(f"**Status:** {data['status']}")
md_lines.append(f"**Total Time:** {data['totalTime'] or 'N/A'}")
md_lines.append(f"**Log File:** build/logs/20260129-121048-_ddprof-test_test.log\n")

# Task summary
md_lines.append("## Task Summary\n")
md_lines.append(f"- Executed: {data['tasksSummary']['executed']}")
md_lines.append(f"- Up-to-date: {data['tasksSummary']['upToDate']}")
md_lines.append(f"- Skipped: {data['tasksSummary']['skipped']}")
md_lines.append(f"- No source: {data['tasksSummary']['noSource']}\n")

# Test results
if data['tests']['total'] > 0:
    md_lines.append("## Test Results\n")
    md_lines.append(f"- **Total:** {data['tests']['total']}")
    md_lines.append(f"- **Passed:** {data['tests']['passed']}")
    md_lines.append(f"- **Failed:** {data['tests']['failed']}")
    md_lines.append(f"- **Skipped:** {data['tests']['skipped']}\n")

    if data['tests']['modules']:
        md_lines.append("### Test Results by Module\n")
        for module in data['tests']['modules']:
            md_lines.append(f"#### {module['name']}")
            md_lines.append(f"- Total: {module['total']}, Passed: {module['passed']}, Failed: {module['failed']}, Skipped: {module['skipped']}")
            if module['failures']:
                md_lines.append(f"- **Failures:**")
                for failure in module['failures'][:10]:
                    md_lines.append(f"  - {failure}")
                if len(module['failures']) > 10:
                    md_lines.append(f"  - ... and {len(module['failures']) - 10} more")
            md_lines.append("")
else:
    md_lines.append("## Test Results\n")
    md_lines.append("No tests were executed (tests were skipped or not triggered).\n")

if data['failedTasks']:
    md_lines.append("## Failed Tasks\n")
    for task in data['failedTasks']:
        md_lines.append(f"- {task}")
    md_lines.append("")

if failure_details:
    md_lines.append("## Test Failures\n")
    for failure in failure_details[:20]:
        if isinstance(failure, dict):
            md_lines.append(f"- {failure['type']}: {failure['message']}")
        else:
            md_lines.append(f"- {failure}")
    if len(failure_details) > 20:
        md_lines.append(f"\n... and {len(failure_details) - 20} more failures")
    md_lines.append("")

if data['warnings']:
    md_lines.append(f"## Warnings\n")
    for warning in data['warnings']:
        md_lines.append(f"- {warning}")
    md_lines.append("")

if data['depIssues']:
    md_lines.append("## Dependency Issues\n")
    for issue in data['depIssues']:
        md_lines.append(f"- {issue}")
    md_lines.append("")

# Key tasks executed
if tasks_executed:
    md_lines.append("## Key Tasks\n")
    important_tasks = [t for t in tasks_executed if t['status'] in ['EXECUTED', 'FAILED', 'SKIPPED']]
    for task in important_tasks[:20]:
        status_emoji = {
            'EXECUTED': '',
            'FAILED': 'FAILED',
            'SKIPPED': 'SKIPPED'
        }.get(task['status'], '')
        md_lines.append(f"- {task['task']} {status_emoji}")
    md_lines.append("")

if data['actions']:
    md_lines.append("## Recommended Actions\n")
    for action in data['actions']:
        md_lines.append(f"- {action}")
    md_lines.append("")

# Write Markdown output
with open(md_path, 'w') as f:
    f.write('\n'.join(md_lines))

print(f"Analysis complete:")
print(f"  Status: {data['status']}")
print(f"  Time: {data['totalTime']}")
print(f"  Tasks: {data['tasksSummary']['executed']} executed, {data['tasksSummary']['skipped']} skipped")
print(f"\nOutputs:")
print(f"  - {json_path}")
print(f"  - {md_path}")
