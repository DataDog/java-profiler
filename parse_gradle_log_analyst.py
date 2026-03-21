#!/usr/bin/env python3
"""
Gradle Log Analyst - Parses Gradle build logs and generates summary reports.
Outputs:
  1. build/reports/claude/gradle-summary.md (human summary, <150 lines)
  2. build/reports/claude/gradle-summary.json (structured data)
"""

import json
import re
import sys
from pathlib import Path
from datetime import datetime
from collections import defaultdict

def parse_gradle_log(log_path):
    """Parse Gradle log file and extract key information."""

    log_path = Path(log_path)
    if not log_path.exists():
        return {"error": f"Log file not found: {log_path}"}

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
        "tasks": []
    }

    try:
        with open(log_path, 'r', encoding='utf-8', errors='ignore') as f:
            lines = f.readlines()
    except Exception as e:
        return {"error": f"Failed to read log file: {e}"}

    if not lines:
        return {"error": "Log file is empty"}

    # Track task execution times
    task_times = {}
    current_task = None
    current_test_module = None
    test_failures = []

    # Parse line by line
    for i, line in enumerate(lines):
        line = line.rstrip()

        # Build status
        if "BUILD SUCCESSFUL" in line:
            data["status"] = "SUCCESS"
        elif "BUILD FAILED" in line:
            data["status"] = "FAILED"

        # Total build time
        match = re.search(r'Total time:\s+([\d.]+\s+\w+)', line)
        if match:
            data["totalTime"] = match.group(1)

        # Task execution
        match = re.search(r'^> Task (:[^\s]+)', line)
        if match:
            current_task = match.group(1)
            data["tasks"].append(current_task)

        # Failed task
        match = re.search(r'^> Task (:[^\s]+)\s+FAILED', line)
        if match:
            task_name = match.group(1)
            data["failedTasks"].append({
                "task": task_name,
                "line": i + 1
            })

        # Task execution times (from Gradle's task timing output)
        match = re.search(r'Execution time:\s+([\d.]+)s for (:[^\s]+)', line)
        if match:
            time_sec = float(match.group(1))
            task_name = match.group(2)
            task_times[task_name] = time_sec

        # Test module detection
        match = re.search(r'> Task (:[^:]+:test\w*)', line)
        if match:
            current_test_module = match.group(1)

        # Test results summary
        match = re.search(r'(\d+) tests completed, (\d+) failed, (\d+) skipped', line)
        if match:
            completed = int(match.group(1))
            failed = int(match.group(2))
            skipped = int(match.group(3))
            passed = completed - failed - skipped

            if current_test_module:
                data["tests"]["modules"].append({
                    "module": current_test_module,
                    "total": completed,
                    "passed": passed,
                    "failed": failed,
                    "skipped": skipped
                })

            data["tests"]["total"] += completed
            data["tests"]["failed"] += failed
            data["tests"]["skipped"] += skipped
            data["tests"]["passed"] += passed

        # Individual test failures
        match = re.search(r'^\s*([A-Za-z0-9_.]+)\s+>\s+([A-Za-z0-9_]+)\s+FAILED', line)
        if match:
            test_class = match.group(1)
            test_method = match.group(2)
            test_failures.append({
                "class": test_class,
                "method": test_method,
                "module": current_test_module or "unknown",
                "line": i + 1
            })

        # Warnings and deprecations
        if "warning:" in line.lower() or "deprecated" in line.lower():
            data["warnings"].append({
                "line": i + 1,
                "message": line.strip()
            })

        # Dependency issues
        if any(kw in line for kw in ["Could not resolve", "not found", "401", "403", "timeout"]):
            if "dependency" in line.lower() or "artifact" in line.lower() or "maven" in line.lower():
                data["depIssues"].append({
                    "line": i + 1,
                    "message": line.strip()
                })

    # Sort tasks by duration
    if task_times:
        sorted_tasks = sorted(task_times.items(), key=lambda x: x[1], reverse=True)
        data["slowTasks"] = [
            {"task": task, "duration": f"{time:.2f}s"}
            for task, time in sorted_tasks[:10]
        ]

    # Add detailed test failures
    if test_failures:
        for module_info in data["tests"]["modules"]:
            module_failures = [f for f in test_failures if f["module"] == module_info["module"]]
            if module_failures:
                module_info["failures"] = module_failures[:5]  # Top 5 failures per module

    # Generate actions
    if data["status"] == "FAILED":
        data["actions"].append("Review failed tasks and test failures")
        if data["tests"]["failed"] > 0:
            data["actions"].append(f"Fix {data['tests']['failed']} failing test(s)")

    if data["warnings"]:
        data["actions"].append(f"Address {len(data['warnings'])} warning(s)")

    if data["depIssues"]:
        data["actions"].append("Resolve dependency issues")

    return data

def generate_markdown_summary(data, output_path):
    """Generate human-readable markdown summary."""

    lines = []
    lines.append("# Gradle Build Summary")
    lines.append("")
    lines.append(f"**Generated:** {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    lines.append("")

    # Overall Status
    lines.append("## Build Status")
    lines.append("")
    status_icon = "✓" if data["status"] == "SUCCESS" else "✗" if data["status"] == "FAILED" else "?"
    lines.append(f"**Status:** {status_icon} {data['status']}")
    if data.get("totalTime"):
        lines.append(f"**Total Time:** {data['totalTime']}")
    lines.append("")

    # Failed Tasks
    if data["failedTasks"]:
        lines.append("## Failed Tasks")
        lines.append("")
        for task_info in data["failedTasks"]:
            lines.append(f"- `{task_info['task']}` (line {task_info['line']})")
        lines.append("")

    # Test Results
    if data["tests"]["total"] > 0:
        lines.append("## Test Results")
        lines.append("")
        t = data["tests"]
        lines.append(f"- **Total:** {t['total']}")
        lines.append(f"- **Passed:** {t['passed']}")
        lines.append(f"- **Failed:** {t['failed']}")
        lines.append(f"- **Skipped:** {t['skipped']}")
        lines.append("")

        if t["modules"]:
            lines.append("### Test Modules")
            lines.append("")
            for mod in t["modules"]:
                status = "PASS" if mod["failed"] == 0 else f"FAIL ({mod['failed']} failed)"
                lines.append(f"**{mod['module']}:** {status}")
                lines.append(f"  - Total: {mod['total']}, Passed: {mod['passed']}, Failed: {mod['failed']}, Skipped: {mod['skipped']}")

                if mod.get("failures"):
                    lines.append("  - **Top Failures:**")
                    for failure in mod["failures"]:
                        lines.append(f"    - `{failure['class']}.{failure['method']}` (line {failure['line']})")
                lines.append("")

    # Slow Tasks
    if data["slowTasks"]:
        lines.append("## Slowest Tasks")
        lines.append("")
        for task_info in data["slowTasks"]:
            lines.append(f"- `{task_info['task']}`: {task_info['duration']}")
        lines.append("")

    # Warnings
    if data["warnings"]:
        lines.append(f"## Warnings ({len(data['warnings'])})")
        lines.append("")
        # Show first 10 unique warnings
        unique_warnings = []
        seen = set()
        for w in data["warnings"]:
            msg = w["message"][:100]  # Truncate long warnings
            if msg not in seen:
                seen.add(msg)
                unique_warnings.append((w["line"], msg))
                if len(unique_warnings) >= 10:
                    break

        for line_num, msg in unique_warnings:
            lines.append(f"- Line {line_num}: `{msg}`")

        if len(data["warnings"]) > 10:
            lines.append(f"- ... and {len(data['warnings']) - 10} more warnings")
        lines.append("")

    # Dependency Issues
    if data["depIssues"]:
        lines.append("## Dependency Issues")
        lines.append("")
        for issue in data["depIssues"][:5]:
            lines.append(f"- Line {issue['line']}: {issue['message'][:100]}")
        if len(data["depIssues"]) > 5:
            lines.append(f"- ... and {len(data['depIssues']) - 5} more issues")
        lines.append("")

    # Recommended Actions
    if data["actions"]:
        lines.append("## Recommended Actions")
        lines.append("")
        for action in data["actions"]:
            lines.append(f"- {action}")
        lines.append("")

    # Error handling
    if "error" in data:
        lines = [
            "# Gradle Build Summary",
            "",
            "## Error",
            "",
            f"Failed to parse log file: {data['error']}",
            ""
        ]

    # Write output
    output_path = Path(output_path)
    output_path.parent.mkdir(parents=True, exist_ok=True)
    with open(output_path, 'w') as f:
        f.write('\n'.join(lines))

    return len(lines)

def generate_json_report(data, output_path):
    """Generate structured JSON report."""

    output_path = Path(output_path)
    output_path.parent.mkdir(parents=True, exist_ok=True)

    with open(output_path, 'w') as f:
        json.dump(data, f, indent=2)

def main():
    if len(sys.argv) < 2:
        print("Usage: parse_gradle_log_analyst.py <log-file-path>")
        sys.exit(1)

    log_path = sys.argv[1]

    # Parse log
    print(f"Parsing log file: {log_path}")
    data = parse_gradle_log(log_path)

    # Generate reports
    md_path = "build/reports/claude/gradle-summary.md"
    json_path = "build/reports/claude/gradle-summary.json"

    if "error" in data:
        print(f"ERROR: {data['error']}")
        generate_markdown_summary(data, md_path)
        generate_json_report(data, json_path)
        sys.exit(1)

    # Write reports
    line_count = generate_markdown_summary(data, md_path)
    generate_json_report(data, json_path)

    # Status output
    print(f"\nBuild Status: {data['status']}")
    if data.get("totalTime"):
        print(f"Total Time: {data['totalTime']}")
    if data["tests"]["total"] > 0:
        print(f"Tests: {data['tests']['passed']}/{data['tests']['total']} passed, {data['tests']['failed']} failed, {data['tests']['skipped']} skipped")

    print(f"\nReports generated:")
    print(f"  - {md_path} ({line_count} lines)")
    print(f"  - {json_path}")

if __name__ == "__main__":
    main()
