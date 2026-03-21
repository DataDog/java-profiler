#!/usr/bin/env python3
"""Comprehensive Gradle log parser for DataDog Java Profiler builds."""
import re
import json
from datetime import datetime
from pathlib import Path
import sys

def parse_gradle_log(log_path):
    """Parse Gradle log and extract structured information."""

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
            "modules": [],
            "gtest": {
                "suites": [],
                "total": 0,
                "passed": 0
            }
        },
        "slowTasks": [],
        "depIssues": [],
        "actions": [],
        "buildInfo": {},
        "tasks": {
            "total": 0,
            "executed": 0,
            "upToDate": 0,
            "noSource": 0,
            "details": []
        }
    }

    try:
        with open(log_path, 'r', encoding='utf-8', errors='ignore') as f:
            lines = f.readlines()
    except Exception as e:
        result["status"] = "ERROR"
        result["actions"].append(f"Failed to read log file: {e}")
        return result

    current_gtest_suite = None
    gtest_running = False

    for i, line in enumerate(lines):
        stripped = line.strip()

        # Build outcome
        if match := re.search(r'BUILD (SUCCESSFUL|FAILED) in (.+)', stripped):
            result["status"] = match.group(1)
            result["totalTime"] = match.group(2)

        # Task execution summary
        if match := re.search(r'(\d+) actionable tasks?: (\d+) executed, (\d+) up-to-date', stripped):
            result["tasks"]["total"] = int(match.group(1))
            result["tasks"]["executed"] = int(match.group(2))
            result["tasks"]["upToDate"] = int(match.group(3))

        # Individual task execution
        if match := re.match(r'^> Task\s+(:\S+)(?:\s+(UP-TO-DATE|NO-SOURCE|FAILED))?', stripped):
            task_name = match.group(1)
            task_status = match.group(2) if match.group(2) else "EXECUTED"

            result["tasks"]["details"].append({
                "name": task_name,
                "status": task_status
            })

            if task_status == "UP-TO-DATE":
                result["tasks"]["upToDate"] += 1
            elif task_status == "NO-SOURCE":
                result["tasks"]["noSource"] += 1
            elif task_status == "FAILED":
                result["failedTasks"].append({
                    "task": task_name,
                    "exception": ""
                })

        # GTest results
        if "Running main() from ./googletest/src/gtest_main.cc" in stripped:
            gtest_running = True
            current_gtest_suite = {"name": "", "tests": 0, "passed": 0, "time": ""}

        if gtest_running and (match := re.search(r'\[==========\] Running (\d+) tests? from (\d+) test suites?', stripped)):
            if current_gtest_suite:
                current_gtest_suite["tests"] = int(match.group(1))

        if gtest_running and (match := re.search(r'\[==========\] (\d+) tests? from (\d+) test suites? ran\. \((\d+) ms total\)', stripped)):
            if current_gtest_suite:
                current_gtest_suite["tests"] = int(match.group(1))
                current_gtest_suite["time"] = f"{match.group(3)} ms"

        if gtest_running and (match := re.search(r'\[  PASSED  \] (\d+) tests?\.', stripped)):
            if current_gtest_suite:
                current_gtest_suite["passed"] = int(match.group(1))

                # Try to get suite name from context
                for j in range(max(0, i-20), i):
                    if match2 := re.search(r'> Task (:\S+:gtest\S+)', lines[j]):
                        current_gtest_suite["name"] = match2.group(1)
                        break

                result["tests"]["gtest"]["suites"].append(current_gtest_suite)
                result["tests"]["gtest"]["total"] += current_gtest_suite["tests"]
                result["tests"]["gtest"]["passed"] += current_gtest_suite["passed"]

                current_gtest_suite = None
                gtest_running = False

        # Java test results
        if match := re.search(r'(\d+)\s+tests?\s+completed,\s+(\d+)\s+failed,\s+(\d+)\s+skipped', stripped, re.IGNORECASE):
            total = int(match.group(1))
            failed = int(match.group(2))
            skipped = int(match.group(3))
            passed = total - failed - skipped

            result["tests"]["total"] += total
            result["tests"]["failed"] += failed
            result["tests"]["skipped"] += skipped
            result["tests"]["passed"] += passed

        # Warnings
        if "Deprecated Gradle features were used" in stripped:
            result["warnings"].append("Deprecated Gradle features used - incompatible with Gradle 9.0")

        if "Configuration cache" in stripped and "disabled" in stripped:
            result["warnings"].append("Configuration cache is disabled")

        # Build environment
        if match := re.search(r'Gradle (\d+\.\d+)', stripped):
            result["buildInfo"]["gradle"] = match.group(0)

        if "JVM:" in stripped or "java.vm.version:" in stripped:
            result["buildInfo"]["jvm"] = stripped

        if match := re.search(r'Using (\d+) worker leases', stripped):
            result["buildInfo"]["workers"] = match.group(1)

    # Calculate slowest tasks (top 10 executed tasks)
    executed_tasks = [t for t in result["tasks"]["details"] if t["status"] == "EXECUTED" or t["status"] == "FAILED"]
    result["slowTasks"] = executed_tasks[:10] if len(executed_tasks) > 0 else []

    # Generate action items
    if result["status"] == "FAILED":
        result["actions"].append("Fix failing tasks")
    if result["tests"]["failed"] > 0:
        result["actions"].append(f"Fix {result['tests']['failed']} failing test(s)")
    if result["warnings"]:
        result["actions"].append("Address deprecation warnings")

    return result

def generate_markdown(data, output_path):
    """Generate human-readable markdown summary."""

    lines = []
    lines.append("# Gradle Build Summary")
    lines.append("")
    lines.append(f"**Status:** {data['status']}")
    lines.append(f"**Total Time:** {data['totalTime']}")
    lines.append("")

    # Build environment
    if data["buildInfo"]:
        lines.append("## Build Environment")
        for key, value in data["buildInfo"].items():
            lines.append(f"- **{key}**: {value}")
        lines.append("")

    # Task summary
    tasks = data["tasks"]
    lines.append("## Task Execution Summary")
    lines.append(f"- **Total Tasks:** {tasks['total']}")
    lines.append(f"- **Executed:** {tasks['executed']}")
    lines.append(f"- **Up-to-date:** {tasks['upToDate']}")
    lines.append(f"- **No-source:** {tasks['noSource']}")
    lines.append("")

    # Failed tasks
    if data["failedTasks"]:
        lines.append("## Failed Tasks")
        for task in data["failedTasks"]:
            lines.append(f"- {task['task']}")
        lines.append("")

    # Test summary
    tests = data["tests"]
    gtest = tests["gtest"]

    lines.append("## Test Results")
    lines.append("")
    lines.append("### C++ Unit Tests (GTest)")
    lines.append(f"- **Total Test Suites:** {len(gtest['suites'])}")
    lines.append(f"- **Total Tests:** {gtest['total']}")
    lines.append(f"- **Passed:** {gtest['passed']}")

    if gtest["suites"]:
        lines.append("")
        lines.append("#### GTest Suites")
        for suite in gtest["suites"]:
            suite_name = suite.get("name", "Unknown")
            if suite_name:
                # Extract readable name from task path
                readable_name = suite_name.split(":")[-1].replace("gtestDebug_", "")
                lines.append(f"- **{readable_name}**: {suite['passed']}/{suite['tests']} passed ({suite['time']})")

    lines.append("")

    if tests["total"] > 0:
        lines.append("### Java Integration Tests")
        lines.append(f"- **Total:** {tests['total']}")
        lines.append(f"- **Passed:** {tests['passed']}")
        lines.append(f"- **Failed:** {tests['failed']}")
        lines.append(f"- **Skipped:** {tests['skipped']}")
        lines.append("")

    # Executed tasks
    if data["slowTasks"]:
        lines.append("## Executed Tasks")
        for task in data["slowTasks"]:
            lines.append(f"- {task['name']}")
        lines.append("")

    # Warnings
    if data["warnings"]:
        lines.append("## Warnings")
        for warning in data["warnings"]:
            lines.append(f"- {warning}")
        lines.append("")

    # Action items
    if data["actions"]:
        lines.append("## Recommended Actions")
        for action in data["actions"]:
            lines.append(f"- {action}")
        lines.append("")

    # Footer
    lines.append("---")
    lines.append(f"*Report generated on {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}*")

    with open(output_path, 'w') as f:
        f.write('\n'.join(lines))

def main():
    if len(sys.argv) < 2:
        print("Usage: comprehensive_gradle_parser.py <log_file_path>")
        sys.exit(1)

    log_path = sys.argv[1]
    base_dir = Path(log_path).parent.parent
    output_dir = base_dir / "reports" / "claude"
    output_dir.mkdir(parents=True, exist_ok=True)

    md_path = output_dir / "gradle-summary.md"
    json_path = output_dir / "gradle-summary.json"

    # Parse log
    data = parse_gradle_log(log_path)

    # Generate outputs
    generate_markdown(data, md_path)

    with open(json_path, 'w') as f:
        json.dump(data, f, indent=2)

    print(f"Analysis complete: {data['status']} in {data['totalTime']}")
    print(f"GTest: {data['tests']['gtest']['passed']}/{data['tests']['gtest']['total']} tests passed")
    if data['tests']['total'] > 0:
        print(f"Java Tests: {data['tests']['passed']}/{data['tests']['total']} tests passed")
    print(f"\nReports generated:")
    print(f"  {md_path}")
    print(f"  {json_path}")

if __name__ == "__main__":
    main()
