#!/usr/bin/env python3
"""
Comprehensive Gradle Log Parser
Generates both JSON and Markdown summaries from Gradle build logs.
"""
import re
import json
from collections import defaultdict
from datetime import datetime

LOG_PATH = "/home/bits/go/src/github.com/DataDog/java-profiler/build/logs/20260128-142001-_ddprof-test_testDebug.log"
JSON_OUT = "/home/bits/go/src/github.com/DataDog/java-profiler/build/reports/claude/gradle-summary.json"
MD_OUT = "/home/bits/go/src/github.com/DataDog/java-profiler/build/reports/claude/gradle-summary.md"

def parse_log():
    """Parse the Gradle log and extract all relevant information."""
    data = {
        "status": "UNKNOWN",
        "totalTime": "",
        "failedTasks": [],
        "warnings": [],
        "tests": {
            "total": 0,
            "passed": 0,
            "failed": 0,
            "skipped": 0,
            "modules": []
        },
        "slowTasks": [],
        "depIssues": [],
        "actions": [],
        "tasks": [],
        "configurationCache": None,
        "gtestResults": {
            "total": 0,
            "passed": 0,
            "suites": []
        },
        "javaTestResults": {
            "total": 0,
            "passed": 0,
            "failed": 0,
            "skipped": 0,
            "classes": []
        }
    }

    tasks = {}
    warnings_set = set()
    dep_issues_set = set()
    gtest_suites = []
    current_gtest_suite = None

    with open(LOG_PATH, 'r', encoding='utf-8', errors='ignore') as f:
        lines = f.readlines()

    for i, line in enumerate(lines):
        # Build status
        if "BUILD SUCCESSFUL" in line:
            data["status"] = "SUCCESS"
            match = re.search(r'in (.+)$', line)
            if match:
                data["totalTime"] = match.group(1).strip()
        elif "BUILD FAILED" in line:
            data["status"] = "FAILED"
            match = re.search(r'in (.+)$', line)
            if match:
                data["totalTime"] = match.group(1).strip()

        # Task execution
        task_match = re.match(r'^> Task (:[^\s]+)', line)
        if task_match:
            task_name = task_match.group(1)
            if "FAILED" in line:
                tasks[task_name] = {"name": task_name, "status": "FAILED"}
                data["failedTasks"].append({"task": task_name, "error": "Task failed"})
            elif "UP-TO-DATE" in line:
                tasks[task_name] = {"name": task_name, "status": "UP-TO-DATE"}
            elif "NO-SOURCE" in line:
                tasks[task_name] = {"name": task_name, "status": "NO-SOURCE"}
            else:
                tasks[task_name] = {"name": task_name, "status": "EXECUTED"}

        # GTest results
        gtest_running = re.match(r'^\[==========\] Running (\d+) tests? from (\d+) test suites?\.', line)
        if gtest_running:
            current_gtest_suite = {
                "total_tests": int(gtest_running.group(1)),
                "passed": 0,
                "tests": []
            }

        gtest_passed_line = re.match(r'^\[  PASSED  \] (\d+) tests?\.', line)
        if gtest_passed_line and current_gtest_suite:
            current_gtest_suite["passed"] = int(gtest_passed_line.group(1))
            gtest_suites.append(current_gtest_suite)
            data["gtestResults"]["total"] += current_gtest_suite["total_tests"]
            data["gtestResults"]["passed"] += current_gtest_suite["passed"]
            current_gtest_suite = None

        # Warnings
        if any(w in line.lower() for w in ["warning:", "deprecated"]):
            if len(line.strip()) > 10 and "Deprecated Gradle features" not in line:
                warnings_set.add(line.strip()[:150])

        # Dependency issues
        if any(x in line for x in ["Could not resolve", "timeout", "401", "403", "404"]):
            if any(x in line.lower() for x in ["dependency", "artifact", "http", "repository"]):
                dep_issues_set.add(line.strip()[:150])

        # Configuration cache
        if "Configuration cache entry" in line:
            if "reused" in line:
                data["configurationCache"] = "reused"
            elif "stored" in line:
                data["configurationCache"] = "stored"

    # Process Java test results from XML
    try:
        import xml.etree.ElementTree as ET
        xml_path = "/home/bits/go/src/github.com/DataDog/java-profiler/ddprof-test/build/test-results/testdebug/TEST-com.datadoghq.profiler.ContextSanityTest.xml"
        tree = ET.parse(xml_path)
        root = tree.getroot()

        tests = int(root.get("tests", 0))
        failures = int(root.get("failures", 0))
        errors = int(root.get("errors", 0))
        skipped = int(root.get("skipped", 0))

        data["javaTestResults"]["total"] = tests
        data["javaTestResults"]["failed"] = failures + errors
        data["javaTestResults"]["skipped"] = skipped
        data["javaTestResults"]["passed"] = tests - failures - errors - skipped
        data["javaTestResults"]["classes"].append({
            "name": root.get("name"),
            "tests": tests,
            "passed": tests - failures - errors - skipped,
            "failed": failures + errors,
            "skipped": skipped
        })
    except Exception as e:
        pass

    # Combine test results
    data["tests"]["total"] = data["gtestResults"]["total"] + data["javaTestResults"]["total"]
    data["tests"]["passed"] = data["gtestResults"]["passed"] + data["javaTestResults"]["passed"]
    data["tests"]["failed"] = data["javaTestResults"]["failed"]
    data["tests"]["skipped"] = data["javaTestResults"]["skipped"]

    # Process warnings and issues
    data["warnings"] = sorted(list(warnings_set))[:20]
    data["depIssues"] = sorted(list(dep_issues_set))[:10]

    # Tasks summary
    data["tasks"] = [{"name": name, "status": info.get("status", "EXECUTED")}
                     for name, info in sorted(tasks.items())]

    # Determine actions
    if data["status"] == "FAILED":
        data["actions"].append("Investigate failed tasks and fix errors")
    if data["tests"]["failed"] > 0:
        data["actions"].append(f"Fix {data['tests']['failed']} failing test(s)")
    if data["warnings"]:
        data["actions"].append("Review and address warnings")
    if data["depIssues"]:
        data["actions"].append("Resolve dependency issues")

    # Count executed tasks
    executed_count = sum(1 for t in data["tasks"] if t["status"] == "EXECUTED")
    uptodate_count = sum(1 for t in data["tasks"] if t["status"] == "UP-TO-DATE")

    data["tasksSummary"] = {
        "total": len(data["tasks"]),
        "executed": executed_count,
        "upToDate": uptodate_count,
        "failed": len(data["failedTasks"])
    }

    return data

def generate_markdown(data):
    """Generate a human-readable Markdown summary."""
    lines = [
        "# Gradle Build Summary",
        "",
        f"**Build Status:** {data['status']}",
        f"**Total Time:** {data['totalTime']}",
        f"**Generated:** {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}",
        "",
        "## Overview",
        "",
        f"- Total Tasks: {data['tasksSummary']['total']}",
        f"- Executed: {data['tasksSummary']['executed']}",
        f"- Up-to-date: {data['tasksSummary']['upToDate']}",
        f"- Failed: {data['tasksSummary']['failed']}",
        "",
        "## Test Results",
        "",
        f"**Total Tests:** {data['tests']['total']} ({data['gtestResults']['total']} C++, "
        f"{data['javaTestResults']['total']} Java)",
        "",
        f"- Passed: {data['tests']['passed']}",
        f"- Failed: {data['tests']['failed']}",
        f"- Skipped: {data['tests']['skipped']}",
        ""
    ]

    # C++ Tests
    if data['gtestResults']['total'] > 0:
        lines.extend([
            "### C++ Tests (Google Test)",
            "",
            f"- Total: {data['gtestResults']['total']}",
            f"- Passed: {data['gtestResults']['passed']}",
            ""
        ])

    # Java Tests
    if data['javaTestResults']['total'] > 0:
        lines.extend([
            "### Java Tests",
            "",
            f"- Total: {data['javaTestResults']['total']}",
            f"- Passed: {data['javaTestResults']['passed']}",
            f"- Failed: {data['javaTestResults']['failed']}",
            f"- Skipped: {data['javaTestResults']['skipped']}",
            ""
        ])

        if data['javaTestResults']['classes']:
            lines.append("**Test Classes:**")
            lines.append("")
            for cls in data['javaTestResults']['classes']:
                lines.append(f"- {cls['name']}: {cls['passed']}/{cls['tests']} passed")
            lines.append("")

    # Failed Tasks
    if data['failedTasks']:
        lines.extend([
            "## Failed Tasks",
            ""
        ])
        for task in data['failedTasks']:
            lines.append(f"- {task['task']}: {task['error']}")
        lines.append("")

    # Warnings
    if data['warnings']:
        lines.extend([
            "## Warnings",
            "",
            f"Found {len(data['warnings'])} warning(s) (showing first 10):",
            ""
        ])
        for warning in data['warnings'][:10]:
            lines.append(f"- {warning}")
        lines.append("")

    # Key Tasks
    executed_tasks = [t for t in data['tasks'] if t['status'] == 'EXECUTED']
    if executed_tasks:
        lines.extend([
            "## Key Executed Tasks",
            ""
        ])
        # Show main compilation and test tasks
        key_patterns = [':compile', ':link', ':test', ':gtest', ':assemble', ':build']
        key_tasks = [t for t in executed_tasks
                     if any(p in t['name'].lower() for p in key_patterns)]

        for task in key_tasks[:15]:
            lines.append(f"- {task['name']}")

        if len(executed_tasks) > 15:
            lines.append(f"- ... and {len(executed_tasks) - 15} more")
        lines.append("")

    # Actions
    if data['actions']:
        lines.extend([
            "## Recommended Actions",
            ""
        ])
        for action in data['actions']:
            lines.append(f"- {action}")
        lines.append("")

    # Configuration
    if data['configurationCache']:
        lines.extend([
            "## Build Configuration",
            "",
            f"- Configuration Cache: {data['configurationCache']}",
            ""
        ])

    return "\n".join(lines)

def main():
    """Main execution function."""
    print("Parsing Gradle log...")
    data = parse_log()

    # Write JSON
    print(f"Writing JSON to {JSON_OUT}...")
    with open(JSON_OUT, 'w') as f:
        json.dump(data, f, indent=2)

    # Write Markdown
    print(f"Writing Markdown to {MD_OUT}...")
    markdown = generate_markdown(data)
    with open(MD_OUT, 'w') as f:
        f.write(markdown)

    print("\nSummary:")
    print(f"  Status: {data['status']}")
    print(f"  Time: {data['totalTime']}")
    print(f"  Tests: {data['tests']['passed']}/{data['tests']['total']} passed")
    print(f"  Tasks: {data['tasksSummary']['executed']} executed, "
          f"{data['tasksSummary']['upToDate']} up-to-date")

    if data['warnings']:
        print(f"  Warnings: {len(data['warnings'])}")

    print("\nReports generated successfully.")

if __name__ == "__main__":
    main()
