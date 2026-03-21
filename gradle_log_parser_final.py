#!/usr/bin/env python3
"""
Gradle Log Analyst - Comprehensive parser for Gradle logs with gtest support
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
        "gtests": {
            "total": 0,
            "failed": 0,
            "passed": 0,
            "suites": []
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
    gtest_suites = defaultdict(lambda: {"passed": 0, "failed": 0, "tests": []})
    current_gtest_suite = None
    java_test_modules = defaultdict(lambda: {"passed": 0, "failed": 0, "skipped": 0, "failedTests": []})
    warnings_set = set()  # Deduplicate warnings
    dep_issues_set = set()

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
                match = re.search(r'BUILD SUCCESSFUL in\s+(.+)', line)
                if match:
                    result["totalTime"] = match.group(1)
                match = re.search(r'BUILD FAILED in\s+(.+)', line)
                if match:
                    result["totalTime"] = match.group(1)

                # Task execution times (from task output lines)
                match = re.search(r'> Task (:[^\s]+)(?:\s+(\w+(?:-\w+)?))?$', line)
                if match:
                    task_name = match.group(1)
                    # We'll try to get timing from elsewhere

                # Failed tasks
                if "> Task" in line and "FAILED" in line:
                    match = re.search(r'> Task (:[^\s]+)', line)
                    if match:
                        task_name = match.group(1)
                        if not any(t["task"] == task_name for t in result["failedTasks"]):
                            result["failedTasks"].append({
                                "task": task_name,
                                "reason": "Task execution failed"
                            })

                # GTest output patterns
                # Suite start: [----------] N tests from SuiteName
                match = re.search(r'^\[----------\]\s+(\d+)\s+tests? from\s+(.+)', line)
                if match:
                    count = int(match.group(1))
                    suite_name = match.group(2)
                    current_gtest_suite = suite_name
                    gtest_suites[suite_name]  # Initialize

                # Test run: [ RUN      ] SuiteName.TestName
                match = re.search(r'^\[\s*RUN\s*\]\s+(.+)\.(.+)', line)
                if match:
                    suite = match.group(1)
                    test = match.group(2)
                    if suite not in gtest_suites:
                        gtest_suites[suite]
                    current_gtest_suite = suite

                # Test result: [       OK ] SuiteName.TestName (X ms)
                match = re.search(r'^\[\s*(OK|FAILED)\s*\]\s+(.+?)\.(.+?)\s+\((\d+)\s*ms\)', line)
                if match:
                    status = match.group(1)
                    suite = match.group(2)
                    test = match.group(3)
                    duration = match.group(4)

                    if suite not in gtest_suites:
                        gtest_suites[suite]

                    gtest_suites[suite]["tests"].append({
                        "name": test,
                        "status": status,
                        "duration": f"{duration}ms"
                    })

                    if status == "OK":
                        gtest_suites[suite]["passed"] += 1
                        result["gtests"]["passed"] += 1
                    else:
                        gtest_suites[suite]["failed"] += 1
                        result["gtests"]["failed"] += 1

                    result["gtests"]["total"] += 1

                # Summary: [  PASSED  ] N tests.
                match = re.search(r'^\[\s*PASSED\s*\]\s+(\d+)\s+tests?\.', line)
                if match:
                    # This is a suite summary, already counted above
                    pass

                # Java test results (Gradle format - less common in this log with -i)
                match = re.search(r'^([A-Z]\w+Test(?:IT)?)\s+>\s+(.+?)\s+(PASSED|FAILED|SKIPPED)', line)
                if match:
                    test_class = match.group(1)
                    test_method = match.group(2)
                    test_result = match.group(3)

                    module = java_test_modules[test_class]
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

                # Warnings - deduplicate and limit
                if "warning:" in line.lower() or ("deprecated" in line.lower() and "gradle" in line.lower()):
                    clean_warning = line.strip()
                    if len(clean_warning) > 0 and len(warnings_set) < 30:
                        warnings_set.add(clean_warning)

                # Dependency issues
                if any(x in line.lower() for x in ["could not resolve", "pkix path", "timed out", "timeout"]):
                    if any(x in line for x in ["401", "403", "404"]) or "Could not" in line:
                        clean_issue = line.strip()
                        if len(clean_issue) > 0:
                            dep_issues_set.add(clean_issue)

                # Configuration cache
                if "Configuration cache" in line and "reused" not in line.lower():
                    if len(result["actions"]) < 10:
                        result["actions"].append(line.strip())

    except Exception as e:
        result["status"] = "ERROR"
        result["actions"].append(f"Error parsing log: {str(e)}")
        return result

    # Finalize gtest suites
    for suite_name, suite_data in gtest_suites.items():
        result["gtests"]["suites"].append({
            "name": suite_name,
            "passed": suite_data["passed"],
            "failed": suite_data["failed"],
            "tests": suite_data["tests"]
        })

    # Finalize Java test modules
    for module_name, module_data in java_test_modules.items():
        result["tests"]["modules"].append({
            "name": module_name,
            "passed": module_data["passed"],
            "failed": module_data["failed"],
            "skipped": module_data["skipped"],
            "failedTests": module_data["failedTests"]
        })

    # Convert sets to lists
    result["warnings"] = sorted(list(warnings_set))
    result["depIssues"] = sorted(list(dep_issues_set))

    # Calculate task execution times from the detailed log
    # This is harder to extract from -i output, so we'll skip for now

    # Add actions based on results
    if result["status"] == "FAILED":
        result["actions"].insert(0, "Build failed. Review failed tasks and test failures.")

    total_test_failures = result["tests"]["failed"] + result["gtests"]["failed"]
    if total_test_failures > 0:
        result["actions"].insert(0, f"{total_test_failures} test(s) failed (Java: {result['tests']['failed']}, C++: {result['gtests']['failed']})")

    if result["depIssues"]:
        result["actions"].append("Dependency issues detected. Check network and repository configuration.")

    # Add summary action
    if result["status"] == "SUCCESS":
        total_tests = result["tests"]["total"] + result["gtests"]["total"]
        result["actions"].insert(0, f"Build succeeded. {total_tests} tests passed (Java: {result['tests']['total']}, C++: {result['gtests']['total']})")

    return result


def generate_markdown_summary(result, output_path):
    """Generate human-readable markdown summary"""

    lines = []
    lines.append("# Gradle Build Summary")
    lines.append("")
    lines.append(f"**Status:** {result['status']}")
    lines.append(f"**Total Time:** {result.get('totalTime', 'N/A')}")
    lines.append(f"**Parsed:** {result['metadata']['parsedAt']}")
    lines.append(f"**Log File:** `{Path(result['metadata']['logFile']).name}`")
    lines.append("")

    # Overall summary
    total_tests = result["tests"]["total"] + result["gtests"]["total"]
    total_passed = result["tests"]["passed"] + result["gtests"]["passed"]
    total_failed = result["tests"]["failed"] + result["gtests"]["failed"]

    lines.append("## Summary")
    lines.append("")
    lines.append(f"- **Total Tests:** {total_tests}")
    lines.append(f"- **Passed:** {total_passed}")
    lines.append(f"- **Failed:** {total_failed}")
    lines.append(f"- **Skipped:** {result['tests']['skipped']}")
    lines.append("")

    # GTest Results (C++ tests)
    if result["gtests"]["total"] > 0:
        lines.append("## C++ Tests (gtest)")
        lines.append("")
        lines.append(f"- **Total:** {result['gtests']['total']}")
        lines.append(f"- **Passed:** {result['gtests']['passed']}")
        lines.append(f"- **Failed:** {result['gtests']['failed']}")
        lines.append("")

        if result["gtests"]["suites"]:
            lines.append("### Test Suites")
            lines.append("")
            for suite in result["gtests"]["suites"]:
                lines.append(f"#### {suite['name']}")
                lines.append(f"- Passed: {suite['passed']}, Failed: {suite['failed']}")

                # Show failed tests
                failed_tests = [t for t in suite["tests"] if t["status"] == "FAILED"]
                if failed_tests:
                    lines.append("- **Failed Tests:**")
                    for test in failed_tests:
                        lines.append(f"  - `{test['name']}` ({test['duration']})")
                lines.append("")

    # Java Test Results
    if result["tests"]["total"] > 0:
        lines.append("## Java Tests")
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

    # Warnings
    if result["warnings"]:
        lines.append("## Warnings")
        lines.append("")
        for warning in result["warnings"][:15]:  # Limit display
            # Truncate very long warnings
            if len(warning) > 120:
                warning = warning[:117] + "..."
            lines.append(f"- {warning}")
        if len(result["warnings"]) > 15:
            lines.append(f"- ... and {len(result['warnings']) - 15} more warnings")
        lines.append("")

    # Dependency Issues
    if result["depIssues"]:
        lines.append("## Dependency Issues")
        lines.append("")
        for issue in result["depIssues"][:10]:
            if len(issue) > 120:
                issue = issue[:117] + "..."
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
        print("Usage: gradle_log_parser_final.py <log_file_path>")
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

    # Print summary to console
    print(f"Status: {result['status']}")
    print(f"Build time: {result['totalTime']}")
    print(f"Java tests: {result['tests']['total']} total, {result['tests']['passed']} passed, {result['tests']['failed']} failed")
    print(f"C++ tests: {result['gtests']['total']} total, {result['gtests']['passed']} passed, {result['gtests']['failed']} failed")
    print(f"")
    print(f"Generated summary: {md_output}")
    print(f"Generated JSON: {json_output}")


if __name__ == "__main__":
    main()
