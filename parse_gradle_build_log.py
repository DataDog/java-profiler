#!/usr/bin/env python3
"""Parse Gradle build log and generate summary artifacts."""

import re
import json
from datetime import datetime
from collections import defaultdict

def parse_gradle_log(log_path):
    """Parse Gradle log and extract key information."""

    result = {
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
        "actions": []
    }

    with open(log_path, 'r', encoding='utf-8', errors='replace') as f:
        lines = f.readlines()

    # Track test results per module
    gtest_modules = []
    current_gtest_task = None
    task_timings = []
    executed_tasks = []
    uptodate_tasks = []

    i = 0
    while i < len(lines):
        line = lines[i]

        # Final status
        if 'BUILD SUCCESSFUL' in line:
            result["status"] = "SUCCESS"
        elif 'BUILD FAILED' in line:
            result["status"] = "FAILED"

        # Total build time
        match = re.search(r'BUILD SUCCESSFUL in (.+)', line)
        if match:
            result["totalTime"] = match.group(1)
        match = re.search(r'BUILD FAILED in (.+)', line)
        if match:
            result["totalTime"] = match.group(1)

        # Task execution tracking
        match = re.search(r'> Task (:\S+)', line)
        if match:
            task_name = match.group(1)
            if 'FAILED' in line:
                result["failedTasks"].append({"task": task_name, "error": "Task failed"})
            elif 'UP-TO-DATE' in line:
                uptodate_tasks.append(task_name)
            elif 'NO-SOURCE' not in line:
                executed_tasks.append(task_name)

            # Track gtest tasks
            if ':gtest:gtest' in task_name:
                current_gtest_task = task_name

        # GTest results - look for summary lines
        match = re.search(r'\[==========\] (\d+) tests? from \d+ test suites? ran\. \((\d+) ms total\)', line)
        if match and current_gtest_task:
            test_count = int(match.group(1))
            duration_ms = match.group(2)

            # Look ahead for PASSED/FAILED line
            passed = 0
            failed = 0
            if i + 1 < len(lines):
                next_line = lines[i + 1]
                passed_match = re.search(r'\[  PASSED  \] (\d+) tests?', next_line)
                failed_match = re.search(r'\[  FAILED  \] (\d+) tests?', next_line)

                if passed_match:
                    passed = int(passed_match.group(1))
                if failed_match:
                    failed = int(failed_match.group(1))

            gtest_modules.append({
                "module": current_gtest_task,
                "total": test_count,
                "passed": passed,
                "failed": failed,
                "skipped": 0,
                "duration": duration_ms + "ms"
            })

            result["tests"]["total"] += test_count
            result["tests"]["passed"] += passed
            result["tests"]["failed"] += failed

        # Warnings - deprecation
        if 'Deprecated Gradle features' in line:
            result["warnings"].append("Deprecated Gradle features used - incompatible with Gradle 9.0")

        # Dependency issues
        if any(x in line for x in ['Could not resolve', '401', '403', 'timeout', 'Connection refused', 'artifact not found']):
            issue = line.strip()
            if issue and len(issue) < 300:
                result["depIssues"].append(issue)

        # Configuration cache
        if 'Configuration cache' in line:
            result["warnings"].append(line.strip())

        i += 1

    # Add test modules
    result["tests"]["modules"] = gtest_modules

    # Count actionable tasks from the summary line
    for line in reversed(lines[-20:]):
        match = re.search(r'(\d+) actionable tasks?: (\d+) executed, (\d+) up-to-date', line)
        if match:
            actionable = int(match.group(1))
            executed = int(match.group(2))
            uptodate = int(match.group(3))

            result["slowTasks"].append({
                "summary": f"{actionable} actionable tasks: {executed} executed, {uptodate} up-to-date",
                "executed": executed,
                "uptodate": uptodate
            })
            break

    # Deduplicate warnings and issues
    result["warnings"] = list(set(result["warnings"]))[:50]
    result["depIssues"] = list(set(result["depIssues"]))[:20]

    # Generate actions
    if result["status"] == "FAILED":
        result["actions"].append("Review failed tasks and fix compilation/test errors")
    if result["tests"]["failed"] > 0:
        result["actions"].append(f"Fix {result['tests']['failed']} failing test(s)")
    if result["warnings"]:
        result["actions"].append("Address deprecation warnings")
    if result["depIssues"]:
        result["actions"].append("Resolve dependency/network issues")

    return result

def generate_markdown(data, log_path):
    """Generate human-readable markdown summary."""

    md = []
    md.append("# Gradle Build Summary")
    md.append(f"\nGenerated: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    md.append(f"\nLog: `{log_path}`")
    md.append("\n---")

    # Build Status
    md.append("\n## Build Status")
    status_icon = "✓" if data["status"] == "SUCCESS" else "✗"
    md.append(f"\n**Status:** {status_icon} {data['status']}")
    if data["totalTime"]:
        md.append(f"\n**Total Time:** {data['totalTime']}")

    # Task Summary
    if data["slowTasks"]:
        for item in data["slowTasks"]:
            if "summary" in item:
                md.append(f"\n**Tasks:** {item['summary']}")

    # Test Results
    md.append("\n## Test Results")
    tests = data["tests"]
    md.append(f"\n- **Total Tests:** {tests['total']}")
    md.append(f"- **Passed:** {tests['passed']}")
    md.append(f"- **Failed:** {tests['failed']}")
    md.append(f"- **Skipped:** {tests['skipped']}")

    if tests["modules"]:
        md.append("\n### Test Modules (GTest)")
        md.append("\n| Module | Total | Passed | Failed | Duration |")
        md.append("|--------|-------|--------|--------|----------|")
        for mod in tests["modules"]:
            name = mod['module'].replace(':ddprof-lib:gtest:gtest', '')
            md.append(f"| {name} | {mod['total']} | {mod['passed']} | {mod['failed']} | {mod.get('duration', 'N/A')} |")

    # Failed Tasks
    if data["failedTasks"]:
        md.append("\n## Failed Tasks")
        for task in data["failedTasks"]:
            if isinstance(task, dict):
                md.append(f"\n- `{task.get('task', 'unknown')}`: {task.get('error', 'Unknown error')}")
            else:
                md.append(f"\n- `{task}`")

    # Warnings
    if data["warnings"]:
        md.append("\n## Warnings")
        for i, warn in enumerate(data["warnings"][:20], 1):
            md.append(f"\n{i}. {warn}")
        if len(data["warnings"]) > 20:
            md.append(f"\n... and {len(data['warnings']) - 20} more warnings")

    # Dependency Issues
    if data["depIssues"]:
        md.append("\n## Dependency Issues")
        for issue in data["depIssues"][:10]:
            md.append(f"\n- {issue}")

    # Actions
    if data["actions"]:
        md.append("\n## Recommended Actions")
        for i, action in enumerate(data["actions"], 1):
            md.append(f"\n{i}. {action}")

    md.append("\n---")
    md.append("\nEnd of summary")

    return "\n".join(md)

def main():
    log_path = "/home/bits/go/src/github.com/DataDog/java-profiler/build/logs/20260128-120652-testDebug.log"
    output_dir = "/home/bits/go/src/github.com/DataDog/java-profiler/build/reports/claude"

    # Parse log
    data = parse_gradle_log(log_path)

    # Generate markdown
    markdown = generate_markdown(data, log_path)

    # Write outputs
    md_path = f"{output_dir}/gradle-summary.md"
    json_path = f"{output_dir}/gradle-summary.json"

    with open(md_path, 'w') as f:
        f.write(markdown)

    with open(json_path, 'w') as f:
        json.dump(data, f, indent=2)

    print(f"Generated:\n- {md_path}\n- {json_path}")
    print(f"\nStatus: {data['status']}")
    print(f"Tests: {data['tests']['total']} total, {data['tests']['passed']} passed, {data['tests']['failed']} failed")

if __name__ == "__main__":
    main()
