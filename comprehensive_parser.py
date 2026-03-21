#!/usr/bin/env python3
"""
Gradle Log Analyst - Comprehensive parser for Gradle build logs and test results.
"""

import json
import re
import glob
import xml.etree.ElementTree as ET
from datetime import datetime
from pathlib import Path
from typing import Dict, List

log_path = Path("/home/bits/go/src/github.com/DataDog/java-profiler/build/logs/20260128-120948-_ddprof-test_testDebug.log")
output_dir = Path("/home/bits/go/src/github.com/DataDog/java-profiler/build/reports/claude")

# Initialize results
status = "UNKNOWN"
total_time = "N/A"
failed_tasks = []
warnings = []
tests = {"total": 0, "passed": 0, "failed": 0, "skipped": 0, "modules": []}
slow_tasks = []
dep_issues = []
errors = []
task_count = 0

# Parse the log file
with open(log_path, 'r', encoding='utf-8', errors='replace') as f:
    lines = f.readlines()

# Track gtest results
gtest_total = 0
gtest_passed = 0

for i, line in enumerate(lines):
    line = line.rstrip()

    # Build outcome
    if "BUILD SUCCESSFUL" in line:
        status = "SUCCESS"
    elif "BUILD FAILED" in line:
        status = "FAILED"

    # Total time
    match = re.search(r'BUILD (SUCCESSFUL|FAILED) in ([\dhms ]+)', line)
    if match:
        total_time = match.group(2).strip()

    # Task count
    if re.match(r'^\d+ actionable tasks:', line):
        task_match = re.search(r'(\d+) actionable tasks', line)
        if task_match:
            task_count = int(task_match.group(1))

    # Failed tasks
    if re.match(r'> Task :[^\s]+ FAILED', line):
        task = line.split()[2]
        failed_tasks.append({"task": task, "reason": "Task failed"})

    # Warnings
    if "Deprecated Gradle features" in line or "warning:" in line.lower():
        warnings.append(line.strip())

    # GTest PASSED results
    gtest_passed_match = re.search(r'\[\s+PASSED\s+\]\s+(\d+)\s+tests?\.', line)
    if gtest_passed_match:
        passed = int(gtest_passed_match.group(1))
        gtest_passed += passed

    # GTest suite totals
    gtest_total_match = re.search(r'\[==========\]\s+(\d+)\s+tests?\s+from\s+(\d+)\s+test\s+suites?\s+ran\.', line)
    if gtest_total_match:
        gtest_total = int(gtest_total_match.group(1))

    # Dependency issues
    if any(keyword in line for keyword in ["Could not resolve", "timeout", "401", "403", "artifact not found"]):
        dep_issues.append(line.strip())

# Parse Java test results from XML
java_test_total = 0
java_test_passed = 0
java_test_failed = 0
java_test_skipped = 0
java_test_suites = []

xml_files = glob.glob('/home/bits/go/src/github.com/DataDog/java-profiler/ddprof-test/build/test-results/testdebug/*.xml')
for xml_file in xml_files:
    try:
        tree = ET.parse(xml_file)
        root = tree.getroot()

        suite_tests = int(root.get('tests', 0))
        suite_failures = int(root.get('failures', 0))
        suite_errors = int(root.get('errors', 0))
        suite_skipped = int(root.get('skipped', 0))
        suite_passed = suite_tests - suite_failures - suite_errors - suite_skipped

        java_test_total += suite_tests
        java_test_passed += suite_passed
        java_test_failed += suite_failures + suite_errors
        java_test_skipped += suite_skipped

        java_test_suites.append({
            'name': root.get('name'),
            'tests': suite_tests,
            'passed': suite_passed,
            'failed': suite_failures + suite_errors,
            'skipped': suite_skipped
        })
    except Exception as e:
        pass

# Combine test results
tests["total"] = gtest_total + java_test_total
tests["passed"] = gtest_passed + java_test_passed
tests["failed"] = java_test_failed
tests["skipped"] = java_test_skipped

# Add modules
if gtest_total > 0:
    tests["modules"].append({
        "type": "C++ (gtest)",
        "total": gtest_total,
        "passed": gtest_passed,
        "failed": 0,
        "skipped": 0
    })

for suite in java_test_suites:
    tests["modules"].append({
        "type": "Java",
        "name": suite['name'],
        "total": suite['tests'],
        "passed": suite['passed'],
        "failed": suite['failed'],
        "skipped": suite['skipped']
    })

# Generate markdown summary
md_lines = [
    "# Gradle Build Summary",
    "",
    f"**Log File:** `{log_path.name}`",
    f"**Generated:** {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}",
    "",
    "## Build Outcome",
    "",
    f"- **Status:** {status}",
    f"- **Total Time:** {total_time}",
    f"- **Actionable Tasks:** {task_count}",
    "",
]

# Test results
if tests["total"] > 0:
    md_lines.extend([
        "## Test Results",
        "",
        f"- **Total Tests:** {tests['total']}",
        f"- **Passed:** {tests['passed']} ({100*tests['passed']//tests['total'] if tests['total'] > 0 else 0}%)",
        f"- **Failed:** {tests['failed']}",
        f"- **Skipped:** {tests['skipped']}",
        "",
    ])

    if tests["modules"]:
        md_lines.append("### Test Breakdown")
        md_lines.append("")
        for module in tests["modules"]:
            if module.get("type") == "C++ (gtest)":
                md_lines.append(f"- **C++ Unit Tests (gtest)**: {module['passed']}/{module['total']} passed")
            else:
                md_lines.append(f"- **{module['name']}**: {module['passed']}/{module['total']} passed")
        md_lines.append("")

# Warnings
if warnings:
    md_lines.extend([
        "## Warnings",
        "",
    ])
    for warning in warnings[:10]:
        md_lines.append(f"- {warning}")
    if len(warnings) > 10:
        md_lines.append(f"- ... and {len(warnings) - 10} more warnings")
    md_lines.append("")

# Failed tasks
if failed_tasks:
    md_lines.extend([
        "## Failed Tasks",
        "",
    ])
    for failure in failed_tasks:
        md_lines.append(f"- `{failure['task']}`: {failure['reason']}")
    md_lines.append("")

# Actions
md_lines.extend([
    "## Summary",
    "",
])

if status == "SUCCESS":
    md_lines.append("Build completed successfully with all tests passing.")
else:
    md_lines.append("Build encountered issues. Review failed tasks and errors above.")

md_lines.append("")

# Write markdown
with open(output_dir / "gradle-summary.md", 'w') as f:
    f.write("\n".join(md_lines))

# Generate JSON
json_data = {
    "log_file": str(log_path),
    "generated_at": datetime.now().isoformat(),
    "status": status,
    "totalTime": total_time,
    "taskCount": task_count,
    "failedTasks": failed_tasks,
    "warnings": warnings,
    "tests": tests,
    "slowTasks": slow_tasks,
    "depIssues": dep_issues,
    "actions": ["No critical actions required"] if status == "SUCCESS" else ["Review build failures"],
    "errors": errors[:5]
}

# Write JSON
with open(output_dir / "gradle-summary.json", 'w') as f:
    json.dump(json_data, f, indent=2)

print(f"Analysis complete:")
print(f"  Status: {status}")
print(f"  Total Time: {total_time}")
print(f"  Tests: {tests['passed']}/{tests['total']} passed")
print(f"  Reports written to build/reports/claude/")
