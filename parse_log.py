#!/usr/bin/env python3
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
            "modules": []
        },
        "slowTasks": [],
        "depIssues": [],
        "actions": [],
        "buildInfo": {},
        "tasks": []
    }

    try:
        with open(log_path, 'r', encoding='utf-8', errors='ignore') as f:
            lines = f.readlines()
    except Exception as e:
        result["status"] = "ERROR"
        result["actions"].append(f"Failed to read log file: {e}")
        return result

    # Track current context
    current_task = None
    test_summary_started = False
    failed_tests = []
    task_timings = {}

    for i, line in enumerate(lines):
        stripped = line.strip()

        # Build outcome
        if "BUILD SUCCESSFUL" in stripped:
            result["status"] = "SUCCESS"
        elif "BUILD FAILED" in stripped:
            result["status"] = "FAILED"

        # Total time
        if match := re.search(r'Total time:\s*(\d+(?:\.\d+)?)\s*(\w+)', stripped):
            result["totalTime"] = f"{match.group(1)} {match.group(2)}"

        # Task execution with timing
        if match := re.match(r'^> Task\s+(:\S+)\s*$', stripped):
            current_task = match.group(1)

        # Task timing
        if match := re.search(r'> Task\s+(:\S+).*?(\d+(?:\.\d+)?s)', stripped):
            task_name = match.group(1)
            timing = match.group(2)
            task_timings[task_name] = timing
            result["tasks"].append({
                "name": task_name,
                "duration": timing
            })

        # Failed task detection
        if "FAILED" in stripped and current_task:
            if match := re.match(r'^> Task\s+(:\S+)\s+FAILED', stripped):
                failed_task = match.group(1)
                result["failedTasks"].append({
                    "task": failed_task,
                    "exception": ""
                })

        # Test results summary
        if match := re.search(r'(\d+)\s+tests?\s+completed,\s+(\d+)\s+failed,\s+(\d+)\s+skipped', stripped, re.IGNORECASE):
            total = int(match.group(1))
            failed = int(match.group(2))
            skipped = int(match.group(3))
            passed = total - failed - skipped

            result["tests"]["total"] += total
            result["tests"]["failed"] += failed
            result["tests"]["skipped"] += skipped
            result["tests"]["passed"] += passed

            if current_task:
                result["tests"]["modules"].append({
                    "task": current_task,
                    "total": total,
                    "passed": passed,
                    "failed": failed,
                    "skipped": skipped
                })

        # Failed test detection
        if match := re.match(r'^(.+?)\s+>\s+(.+?)\s+FAILED', stripped):
            test_class = match.group(1).strip()
            test_method = match.group(2).strip()
            failed_tests.append({
                "class": test_class,
                "method": test_method,
                "exception": "",
                "message": ""
            })

        # Exception messages
        if failed_tests and any(keyword in stripped for keyword in ['Exception:', 'Error:', 'Caused by:']):
            if failed_tests[-1]["exception"] == "":
                failed_tests[-1]["exception"] = stripped
            else:
                failed_tests[-1]["message"] = stripped

        # Warnings
        if re.search(r'warning:|deprecated|deprecation', stripped, re.IGNORECASE):
            if "w:" not in stripped.lower() and len(stripped) > 20:
                result["warnings"].append(stripped[:200])

        # Configuration cache
        if "Configuration cache" in stripped:
            result["buildInfo"]["configCache"] = stripped

        # Dependency issues
        if any(keyword in stripped for keyword in ['Could not resolve', 'not found', '401', '403', 'timeout']):
            result["depIssues"].append(stripped[:200])

        # Build info
        if "Gradle" in stripped and "version" in stripped.lower():
            result["buildInfo"]["gradleVersion"] = stripped
        if "JVM:" in stripped:
            result["buildInfo"]["jvm"] = stripped

    # Extract top 10 slowest tasks
    if task_timings:
        def parse_duration(duration_str):
            if duration_str.endswith('ms'):
                return float(duration_str[:-2]) / 1000
            elif duration_str.endswith('s'):
                return float(duration_str[:-1])
            elif duration_str.endswith('m'):
                return float(duration_str[:-1]) * 60
            return 0.0

        sorted_tasks = sorted(
            task_timings.items(),
            key=lambda x: parse_duration(x[1]),
            reverse=True
        )[:10]

        result["slowTasks"] = [
            {"task": task, "duration": duration}
            for task, duration in sorted_tasks
        ]

    # Add failed tests to result
    if failed_tests:
        result["tests"]["failedTests"] = failed_tests[:20]  # Limit to top 20

    # Add action items
    if result["status"] == "FAILED":
        result["actions"].append("Fix failing tests and tasks")
    if result["warnings"]:
        result["actions"].append("Address deprecation warnings")
    if result["depIssues"]:
        result["actions"].append("Resolve dependency issues")

    return result

def generate_markdown(data, output_path):
    """Generate human-readable markdown summary."""

    lines = []
    lines.append("# Gradle Build Summary")
    lines.append("")
    lines.append(f"**Status:** {data['status']}")
    lines.append(f"**Total Time:** {data['totalTime']}")
    lines.append("")

    # Build info
    if data["buildInfo"]:
        lines.append("## Build Environment")
        for key, value in data["buildInfo"].items():
            lines.append(f"- {key}: {value}")
        lines.append("")

    # Failed tasks
    if data["failedTasks"]:
        lines.append("## Failed Tasks")
        for task in data["failedTasks"]:
            lines.append(f"- **{task['task']}**")
            if task.get("exception"):
                lines.append(f"  - Exception: {task['exception']}")
        lines.append("")

    # Test summary
    tests = data["tests"]
    lines.append("## Test Results")
    lines.append(f"- **Total:** {tests['total']}")
    lines.append(f"- **Passed:** {tests['passed']}")
    lines.append(f"- **Failed:** {tests['failed']}")
    lines.append(f"- **Skipped:** {tests['skipped']}")
    lines.append("")

    # Failed tests
    if tests.get("failedTests"):
        lines.append("### Failed Tests")
        for test in tests["failedTests"][:10]:
            lines.append(f"- **{test['class']}.{test['method']}**")
            if test.get("exception"):
                lines.append(f"  - {test['exception'][:150]}")
        if len(tests["failedTests"]) > 10:
            lines.append(f"- _(and {len(tests['failedTests']) - 10} more)_")
        lines.append("")

    # Test modules
    if tests["modules"]:
        lines.append("### Test Results by Module")
        for module in tests["modules"]:
            lines.append(f"- **{module['task']}**: {module['passed']}/{module['total']} passed")
        lines.append("")

    # Slowest tasks
    if data["slowTasks"]:
        lines.append("## Slowest Tasks (Top 10)")
        for task in data["slowTasks"]:
            lines.append(f"- {task['task']}: {task['duration']}")
        lines.append("")

    # Warnings
    if data["warnings"]:
        lines.append("## Warnings")
        for warning in data["warnings"][:15]:
            lines.append(f"- {warning}")
        if len(data["warnings"]) > 15:
            lines.append(f"- _(and {len(data['warnings']) - 15} more warnings)_")
        lines.append("")

    # Dependency issues
    if data["depIssues"]:
        lines.append("## Dependency Issues")
        for issue in data["depIssues"][:10]:
            lines.append(f"- {issue}")
        lines.append("")

    # Action items
    if data["actions"]:
        lines.append("## Recommended Actions")
        for action in data["actions"]:
            lines.append(f"- {action}")
        lines.append("")

    # Footer
    lines.append("---")
    lines.append(f"*Generated on {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}*")

    with open(output_path, 'w') as f:
        f.write('\n'.join(lines))

def main():
    if len(sys.argv) < 2:
        print("Usage: parse_log.py <log_file_path>")
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

    print(f"Summary generated successfully:")
    print(f"  - Markdown: {md_path}")
    print(f"  - JSON: {json_path}")
    print(f"\nBuild Status: {data['status']}")
    print(f"Total Time: {data['totalTime']}")
    print(f"Tests: {data['tests']['passed']}/{data['tests']['total']} passed")

if __name__ == "__main__":
    main()
