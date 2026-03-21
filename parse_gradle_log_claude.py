#!/usr/bin/env python3
"""
Gradle Log Analyst - Parse Gradle logs and generate summary artifacts
"""

import re
import json
import sys
from datetime import datetime
from pathlib import Path
from collections import defaultdict

def parse_gradle_log(log_path):
    """Parse Gradle log file and extract key information"""

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
        "actions": [],
        "metadata": {
            "logFile": str(log_path),
            "parsedAt": datetime.now().isoformat(),
            "logSize": log_path.stat().st_size if log_path.exists() else 0
        }
    }

    if not log_path.exists():
        result["status"] = "ERROR"
        result["actions"].append(f"Log file not found: {log_path}")
        return result

    # Tracking variables
    task_times = {}
    current_test_class = None
    test_modules = defaultdict(lambda: {"passed": 0, "failed": 0, "skipped": 0, "failedTests": []})
    in_failure_section = False
    current_failure = []
    failed_test_name = None

    try:
        with open(log_path, 'r', encoding='utf-8', errors='ignore') as f:
            for line in f:
                line = line.rstrip()

                # Build outcome
                if "BUILD SUCCESSFUL" in line:
                    result["status"] = "SUCCESS"
                elif "BUILD FAILED" in line:
                    result["status"] = "FAILED"

                # Total build time
                match = re.search(r'Total time:\s+(.+)', line)
                if match:
                    result["totalTime"] = match.group(1)

                # Task execution times
                match = re.search(r'> Task (:[^\s]+)\s+.*?(\d+(?:\.\d+)?)\s*m?s', line)
                if match:
                    task_name = match.group(1)
                    time_str = match.group(2)
                    try:
                        time_val = float(time_str)
                        task_times[task_name] = time_val
                    except ValueError:
                        pass

                # Failed tasks
                if "> Task" in line and "FAILED" in line:
                    match = re.search(r'> Task (:[^\s]+)', line)
                    if match:
                        task_name = match.group(1)
                        result["failedTasks"].append({
                            "task": task_name,
                            "reason": "Task execution failed"
                        })

                # Test execution
                if re.match(r'^[A-Z]\w+Test(?:IT)?\s*>', line):
                    match = re.match(r'^([A-Z]\w+Test(?:IT)?)\s*>', line)
                    if match:
                        current_test_class = match.group(1)

                # Test results per class
                match = re.search(r'^([A-Z]\w+Test(?:IT)?)\s+>\s+(.+?)\s+(PASSED|FAILED|SKIPPED)', line)
                if match:
                    test_class = match.group(1)
                    test_method = match.group(2)
                    test_result = match.group(3)

                    module = test_modules[test_class]
                    if test_result == "PASSED":
                        module["passed"] += 1
                        result["tests"]["passed"] += 1
                    elif test_result == "FAILED":
                        module["failed"] += 1
                        result["tests"]["failed"] += 1
                        module["failedTests"].append(test_method)
                    elif test_result == "SKIPPED":
                        module["skipped"] += 1
                        result["tests"]["skipped"] += 1

                    result["tests"]["total"] += 1

                # Capture failure details
                if re.search(r'^\s*[A-Z]\w+Test(?:IT)?\s+>\s+\w+\s+FAILED', line):
                    match = re.search(r'^\s*([A-Z]\w+Test(?:IT)?)\s+>\s+(\w+)\s+FAILED', line)
                    if match:
                        failed_test_name = f"{match.group(1)}.{match.group(2)}"
                        in_failure_section = True
                        current_failure = []

                if in_failure_section and line.strip():
                    if line.startswith("    at ") or "Exception" in line or "Error" in line or "Expected" in line or "Actual" in line:
                        current_failure.append(line.strip())
                    elif re.match(r'^[A-Z]\w+Test(?:IT)?\s+>', line):
                        # New test started, save previous failure
                        if failed_test_name and current_failure:
                            result["failedTasks"].append({
                                "task": failed_test_name,
                                "reason": "\n".join(current_failure[:10])  # First 10 lines
                            })
                        in_failure_section = False
                        current_failure = []
                        failed_test_name = None

                # Warnings
                if "warning:" in line.lower() or "deprecated" in line.lower():
                    if len(result["warnings"]) < 50:  # Limit warnings
                        result["warnings"].append(line.strip())

                # Dependency issues
                if any(x in line for x in ["Could not resolve", "PKIX path", "401", "403", "timeout", "timed out"]):
                    result["depIssues"].append(line.strip())

                # Configuration cache
                if "Configuration cache" in line:
                    result["actions"].append(line.strip())

    except Exception as e:
        result["status"] = "ERROR"
        result["actions"].append(f"Error parsing log: {str(e)}")
        return result

    # Finalize test modules
    for module_name, module_data in test_modules.items():
        result["tests"]["modules"].append({
            "name": module_name,
            "passed": module_data["passed"],
            "failed": module_data["failed"],
            "skipped": module_data["skipped"],
            "failedTests": module_data["failedTests"]
        })

    # Sort and get slowest tasks
    sorted_tasks = sorted(task_times.items(), key=lambda x: x[1], reverse=True)
    result["slowTasks"] = [
        {"task": task, "duration": f"{time}ms"}
        for task, time in sorted_tasks[:10]
    ]

    # Add actions
    if result["status"] == "FAILED":
        result["actions"].append("Build failed. Review failed tasks and test failures.")
    if result["tests"]["failed"] > 0:
        result["actions"].append(f"{result['tests']['failed']} test(s) failed. Review test output above.")
    if result["depIssues"]:
        result["actions"].append("Dependency issues detected. Check network and repository configuration.")

    return result


def generate_markdown_summary(result, output_path):
    """Generate human-readable markdown summary"""

    lines = []
    lines.append("# Gradle Build Summary")
    lines.append("")
    lines.append(f"**Status:** {result['status']}")
    lines.append(f"**Total Time:** {result.get('totalTime', 'N/A')}")
    lines.append(f"**Parsed:** {result['metadata']['parsedAt']}")
    lines.append(f"**Log File:** {result['metadata']['logFile']}")
    lines.append("")

    # Test Results
    lines.append("## Test Results")
    lines.append("")
    t = result["tests"]
    lines.append(f"- **Total:** {t['total']}")
    lines.append(f"- **Passed:** {t['passed']}")
    lines.append(f"- **Failed:** {t['failed']}")
    lines.append(f"- **Skipped:** {t['skipped']}")
    lines.append("")

    if t["modules"]:
        lines.append("### Test Modules")
        lines.append("")
        for mod in t["modules"]:
            lines.append(f"#### {mod['name']}")
            lines.append(f"- Passed: {mod['passed']}, Failed: {mod['failed']}, Skipped: {mod['skipped']}")
            if mod["failedTests"]:
                lines.append(f"- **Failed Tests:** {', '.join(mod['failedTests'])}")
            lines.append("")

    # Failed Tasks
    if result["failedTasks"]:
        lines.append("## Failed Tasks")
        lines.append("")
        for task in result["failedTasks"]:
            lines.append(f"### {task['task']}")
            lines.append("```")
            lines.append(task['reason'])
            lines.append("```")
            lines.append("")

    # Slow Tasks
    if result["slowTasks"]:
        lines.append("## Slowest Tasks (Top 10)")
        lines.append("")
        for task in result["slowTasks"]:
            lines.append(f"- `{task['task']}`: {task['duration']}")
        lines.append("")

    # Warnings
    if result["warnings"]:
        lines.append("## Warnings")
        lines.append("")
        for warning in result["warnings"][:20]:  # Limit to first 20
            lines.append(f"- {warning}")
        if len(result["warnings"]) > 20:
            lines.append(f"- ... and {len(result['warnings']) - 20} more warnings")
        lines.append("")

    # Dependency Issues
    if result["depIssues"]:
        lines.append("## Dependency Issues")
        lines.append("")
        for issue in result["depIssues"][:10]:
            lines.append(f"- {issue}")
        lines.append("")

    # Actions
    if result["actions"]:
        lines.append("## Recommended Actions")
        lines.append("")
        for action in result["actions"]:
            lines.append(f"- {action}")
        lines.append("")

    # Write to file
    output_path.parent.mkdir(parents=True, exist_ok=True)
    with open(output_path, 'w', encoding='utf-8') as f:
        f.write("\n".join(lines))

    return len(lines)


def main():
    if len(sys.argv) < 2:
        print("Usage: parse_gradle_log_claude.py <log_file_path>")
        sys.exit(1)

    log_path = Path(sys.argv[1])
    base_dir = Path("/home/bits/go/src/github.com/DataDog/java-profiler")

    # Output paths
    md_output = base_dir / "build/reports/claude/gradle-summary.md"
    json_output = base_dir / "build/reports/claude/gradle-summary.json"

    # Parse log
    result = parse_gradle_log(log_path)

    # Generate markdown
    line_count = generate_markdown_summary(result, md_output)

    # Write JSON
    json_output.parent.mkdir(parents=True, exist_ok=True)
    with open(json_output, 'w', encoding='utf-8') as f:
        json.dump(result, f, indent=2)

    # Print summary
    print(f"Parsed log: {log_path}")
    print(f"Status: {result['status']}")
    print(f"Tests: {result['tests']['total']} total, {result['tests']['passed']} passed, {result['tests']['failed']} failed, {result['tests']['skipped']} skipped")
    print(f"Generated {line_count} lines in {md_output}")
    print(f"Wrote structured data to {json_output}")


if __name__ == "__main__":
    main()
