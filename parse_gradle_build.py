#!/usr/bin/env python3
import json
import re
from datetime import datetime
from pathlib import Path

log_path = Path("/home/bits/go/src/github.com/DataDog/java-profiler/build/logs/20260126-104135-buildDebug.log")

# Read the log file
with open(log_path, 'r', encoding='utf-8', errors='replace') as f:
    log_content = f.read()

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
    "configCache": {},
    "cacheMisses": []
}

# Parse overall build status
if "BUILD SUCCESSFUL" in log_content:
    data["status"] = "SUCCESS"
elif "BUILD FAILED" in log_content:
    data["status"] = "FAILED"

# Extract total build time
time_match = re.search(r'BUILD SUCCESSFUL in (\d+m\s+\d+s|\d+s)', log_content)
if time_match:
    data["totalTime"] = time_match.group(1)

# Extract task execution times
task_pattern = re.compile(r'> Task (:[^\s]+)\s+(\d+ms|\d+s)')
tasks = []
for match in task_pattern.finditer(log_content):
    task_name = match.group(1)
    duration_str = match.group(2)

    # Convert to milliseconds
    if duration_str.endswith('ms'):
        duration_ms = int(duration_str[:-2])
    elif duration_str.endswith('s'):
        duration_ms = int(float(duration_str[:-1]) * 1000)
    else:
        duration_ms = 0

    tasks.append({
        "task": task_name,
        "duration": duration_str,
        "durationMs": duration_ms
    })

# Sort by duration and get top 10 slowest
tasks.sort(key=lambda x: x["durationMs"], reverse=True)
data["slowTasks"] = [{"task": t["task"], "duration": t["duration"]} for t in tasks[:10]]

# Extract warnings and deprecations
warning_patterns = [
    r'WARNING: (.+)',
    r'WARN: (.+)',
    r'deprecated: (.+)',
    r'Deprecated (.+)'
]
warnings_set = set()
for pattern in warning_patterns:
    for match in re.finditer(pattern, log_content, re.IGNORECASE):
        warning = match.group(1).strip()
        if len(warning) < 500:  # Skip overly long warnings
            warnings_set.add(warning)

data["warnings"] = list(warnings_set)[:20]  # Limit to 20 warnings

# Extract failed tasks
failed_task_pattern = re.compile(r'> Task (:[^\s]+) FAILED', re.MULTILINE)
for match in failed_task_pattern.finditer(log_content):
    task_name = match.group(1)
    data["failedTasks"].append({
        "task": task_name,
        "reason": "Task execution failed"
    })

# Extract test results
test_summary_pattern = re.compile(
    r'(\d+) tests? completed(?:, (\d+) failed)?(?:, (\d+) skipped)?',
    re.IGNORECASE
)
for match in test_summary_pattern.finditer(log_content):
    total = int(match.group(1))
    failed = int(match.group(2)) if match.group(2) else 0
    skipped = int(match.group(3)) if match.group(3) else 0
    passed = total - failed - skipped

    data["tests"]["total"] += total
    data["tests"]["failed"] += failed
    data["tests"]["skipped"] += skipped
    data["tests"]["passed"] += passed

# Extract configuration cache info
if "Configuration cache entry" in log_content:
    if "reused" in log_content:
        data["configCache"]["status"] = "HIT"
    elif "stored" in log_content:
        data["configCache"]["status"] = "MISS"

# Extract dependency issues
dep_issue_patterns = [
    r'Could not resolve (.+)',
    r'artifact not found: (.+)',
    r'timeout.+?downloading (.+)',
    r'401.+?(.+)',
    r'403.+?(.+)'
]
for pattern in dep_issue_patterns:
    for match in re.finditer(pattern, log_content, re.IGNORECASE):
        issue = match.group(1).strip()[:200]
        data["depIssues"].append(issue)

# Generate summary actions
if data["status"] == "SUCCESS":
    data["actions"].append("Build completed successfully")
if data["failedTasks"]:
    data["actions"].append(f"Review {len(data['failedTasks'])} failed task(s)")
if data["warnings"]:
    data["actions"].append(f"Address {len(data['warnings'])} warning(s)")
if data["tests"]["failed"] > 0:
    data["actions"].append(f"Fix {data['tests']['failed']} failing test(s)")

# Write JSON output
json_path = Path("/home/bits/go/src/github.com/DataDog/java-profiler/build/reports/claude/gradle-summary.json")
json_path.parent.mkdir(parents=True, exist_ok=True)
with open(json_path, 'w') as f:
    json.dump(data, f, indent=2)

# Generate markdown summary
md_lines = []
md_lines.append("# Gradle Build Summary")
md_lines.append("")
md_lines.append(f"**Build Status:** {data['status']}")
md_lines.append(f"**Total Time:** {data['totalTime']}")
md_lines.append(f"**Log File:** build/logs/20260126-104135-buildDebug.log")
md_lines.append("")

# Failed tasks section
if data["failedTasks"]:
    md_lines.append("## Failed Tasks")
    md_lines.append("")
    for task in data["failedTasks"]:
        md_lines.append(f"- **{task['task']}**: {task['reason']}")
    md_lines.append("")

# Test results section
if data["tests"]["total"] > 0:
    md_lines.append("## Test Results")
    md_lines.append("")
    md_lines.append(f"- **Total:** {data['tests']['total']}")
    md_lines.append(f"- **Passed:** {data['tests']['passed']}")
    md_lines.append(f"- **Failed:** {data['tests']['failed']}")
    md_lines.append(f"- **Skipped:** {data['tests']['skipped']}")
    md_lines.append("")

# Warnings section
if data["warnings"]:
    md_lines.append("## Warnings")
    md_lines.append("")
    for warning in data["warnings"][:10]:  # Top 10 warnings in markdown
        md_lines.append(f"- {warning}")
    if len(data["warnings"]) > 10:
        md_lines.append(f"- ... and {len(data['warnings']) - 10} more warnings")
    md_lines.append("")

# Slow tasks section
if data["slowTasks"]:
    md_lines.append("## Slowest Tasks (Top 10)")
    md_lines.append("")
    md_lines.append("| Task | Duration |")
    md_lines.append("|------|----------|")
    for task in data["slowTasks"]:
        md_lines.append(f"| {task['task']} | {task['duration']} |")
    md_lines.append("")

# Configuration cache section
if data["configCache"]:
    md_lines.append("## Configuration Cache")
    md_lines.append("")
    md_lines.append(f"**Status:** {data['configCache'].get('status', 'N/A')}")
    md_lines.append("")

# Dependency issues section
if data["depIssues"]:
    md_lines.append("## Dependency Issues")
    md_lines.append("")
    for issue in data["depIssues"][:5]:
        md_lines.append(f"- {issue}")
    md_lines.append("")

# Actions section
if data["actions"]:
    md_lines.append("## Recommended Actions")
    md_lines.append("")
    for action in data["actions"]:
        md_lines.append(f"- {action}")
    md_lines.append("")

# Write markdown output
md_path = Path("/home/bits/go/src/github.com/DataDog/java-profiler/build/reports/claude/gradle-summary.md")
with open(md_path, 'w') as f:
    f.write('\n'.join(md_lines))

print("Summary generated successfully")
print(f"JSON: {json_path}")
print(f"Markdown: {md_path}")
