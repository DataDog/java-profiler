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
    "actions": []
}

# Parse log file
with open(log_path, 'r', encoding='utf-8', errors='ignore') as f:
    lines = f.readlines()

# Track state
task_times = {}
failure_details = []
test_modules = defaultdict(lambda: {"total": 0, "failed": 0, "skipped": 0, "passed": 0, "failures": []})
current_module = None

for i, line in enumerate(lines):
    line = line.rstrip()

    # Build status
    if 'BUILD SUCCESSFUL' in line:
        data["status"] = "SUCCESS"
    elif 'BUILD FAILED' in line:
        data["status"] = "FAILED"

    # Total build time
    match = re.search(r'Total time:\s+([\d.]+\s+\w+)', line)
    if match:
        data["totalTime"] = match.group(1)

    # Task timing
    match = re.search(r'Executed task \'(:\S+)\' in ([\d.]+\s+\w+)', line)
    if match:
        task_name = match.group(1)
        task_time = match.group(2)
        task_times[task_name] = task_time

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
        failure_details.append(f"{exception_type}: {exception_msg}")

    # Warnings
    if 'WARNING' in line or 'deprecated' in line.lower():
        if line.strip() and len(data["warnings"]) < 50:
            data["warnings"].append(line.strip())

    # Dependency issues
    if any(x in line for x in ['Could not resolve', 'not found', '401', '403', 'timeout', 'Failed to download']):
        data["depIssues"].append(line.strip())

# Extract failed tasks
for line in lines:
    if 'FAILED' in line and '> Task' in line:
        match = re.search(r'> Task (:\S+)', line)
        if match:
            task = match.group(1)
            if task not in data["failedTasks"]:
                data["failedTasks"].append(task)

# Sort tasks by time (convert to seconds for proper sorting)
def parse_time(time_str):
    if 'ms' in time_str:
        return float(time_str.replace('ms', '').strip()) / 1000
    elif 's' in time_str:
        return float(time_str.replace('s', '').strip())
    elif 'mins' in time_str:
        parts = time_str.split()
        mins = float(parts[0])
        secs = float(parts[2]) if len(parts) > 2 else 0
        return mins * 60 + secs
    return 0

sorted_tasks = sorted(task_times.items(), key=lambda x: parse_time(x[1]), reverse=True)
data["slowTasks"] = [{"task": t[0], "time": t[1]} for t in sorted_tasks[:10]]

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

# Add actions if build failed
if data["status"] == "FAILED":
    data["actions"].append("Review test failures in detail")
    data["actions"].append("Check test reports in build/reports/tests/")
    if failure_details:
        data["actions"].append(f"Focus on {len(failure_details)} failing test(s)")
elif data["status"] == "SUCCESS":
    data["actions"].append("Build completed successfully")

# Write JSON output
with open(json_path, 'w') as f:
    json.dump(data, f, indent=2)

# Generate Markdown summary
md_lines = []
md_lines.append("# Gradle Build Summary\n")
md_lines.append(f"**Status:** {data['status']}\n")
md_lines.append(f"**Total Time:** {data['totalTime'] or 'N/A'}\n")
md_lines.append(f"**Log File:** build/logs/20260129-121048-_ddprof-test_test.log\n")
md_lines.append("\n## Test Results\n")
md_lines.append(f"- **Total:** {data['tests']['total']}")
md_lines.append(f"- **Passed:** {data['tests']['passed']}")
md_lines.append(f"- **Failed:** {data['tests']['failed']}")
md_lines.append(f"- **Skipped:** {data['tests']['skipped']}\n")

if data['tests']['modules']:
    md_lines.append("\n### Test Results by Module\n")
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

if data['failedTasks']:
    md_lines.append("\n## Failed Tasks\n")
    for task in data['failedTasks']:
        md_lines.append(f"- {task}")
    md_lines.append("")

if failure_details:
    md_lines.append("\n## Test Failures\n")
    for failure in failure_details[:20]:
        md_lines.append(f"- {failure}")
    if len(failure_details) > 20:
        md_lines.append(f"\n... and {len(failure_details) - 20} more failures")
    md_lines.append("")

if data['slowTasks']:
    md_lines.append("\n## Slowest Tasks (Top 10)\n")
    for task in data['slowTasks']:
        md_lines.append(f"- {task['task']}: {task['time']}")
    md_lines.append("")

if data['warnings']:
    md_lines.append(f"\n## Warnings ({len(data['warnings'])} total)\n")
    for warning in data['warnings'][:10]:
        md_lines.append(f"- {warning}")
    if len(data['warnings']) > 10:
        md_lines.append(f"\n... and {len(data['warnings']) - 10} more warnings")
    md_lines.append("")

if data['depIssues']:
    md_lines.append("\n## Dependency Issues\n")
    for issue in data['depIssues']:
        md_lines.append(f"- {issue}")
    md_lines.append("")

if data['actions']:
    md_lines.append("\n## Recommended Actions\n")
    for action in data['actions']:
        md_lines.append(f"- {action}")
    md_lines.append("")

# Write Markdown output
with open(md_path, 'w') as f:
    f.write('\n'.join(md_lines))

print(f"Generated summaries:")
print(f"  - {json_path}")
print(f"  - {md_path}")
