#!/usr/bin/env python3
"""
Gradle Log Analyst - Parse Gradle logs and generate summary reports
"""
import re
import json
import sys
from pathlib import Path

def parse_gradle_log(log_path):
    """Parse a Gradle log file and extract key information."""
    with open(log_path, 'r', encoding='utf-8', errors='ignore') as f:
        content = f.read()

    # Extract build status and time
    status_match = re.search(r'BUILD (SUCCESSFUL|FAILED)', content)
    status = status_match.group(1) if status_match else 'UNKNOWN'

    time_match = re.search(r'BUILD \w+ in (.+)$', content, re.MULTILINE)
    total_time = time_match.group(1) if time_match else 'unknown'

    # Extract all tasks
    tasks = []
    task_pattern = re.compile(r'^> Task ([:\w-]+)( (UP-TO-DATE|NO-SOURCE|FAILED))?$', re.MULTILINE)
    for match in task_pattern.finditer(content):
        task_name = match.group(1)
        task_status = match.group(3) if match.group(3) else 'EXECUTED'
        tasks.append({'name': task_name, 'status': task_status})

    # Extract failed tasks
    failed_tasks = [t for t in tasks if t['status'] == 'FAILED']

    # Count gtest results
    gtest_tests = []
    gtest_pattern = re.compile(r'(✅|❌) Test (.+) - (PASSED|FAILED)', content)
    for match in gtest_pattern.finditer(content):
        gtest_tests.append({
            'name': match.group(2),
            'status': match.group(3)
        })

    gtest_passed = sum(1 for t in gtest_tests if t['status'] == 'PASSED')
    gtest_failed = sum(1 for t in gtest_tests if t['status'] == 'FAILED')

    # Count Java test results
    java_test_pattern = re.compile(r'(\w+Test) > (.+) > \[(\d+)\] (PASSED|FAILED|SKIPPED)', re.MULTILINE)
    java_tests = []
    for match in java_test_pattern.finditer(content):
        java_tests.append({
            'class': match.group(1),
            'method': match.group(2),
            'status': match.group(4)
        })

    java_passed = sum(1 for t in java_tests if t['status'] == 'PASSED')
    java_failed = sum(1 for t in java_tests if t['status'] == 'FAILED')
    java_skipped = sum(1 for t in java_tests if t['status'] == 'SKIPPED')

    # Extract warnings
    warnings = []
    if re.search(r'Deprecated Gradle features were used', content):
        warnings.append({
            'type': 'deprecation',
            'message': 'Deprecated Gradle features were used in this build, making it incompatible with Gradle 9.0'
        })

    # Count executed tasks by type
    executed_tasks = [t for t in tasks if t['status'] == 'EXECUTED']
    up_to_date_tasks = [t for t in tasks if t['status'] == 'UP-TO-DATE']
    no_source_tasks = [t for t in tasks if t['status'] == 'NO-SOURCE']

    return {
        'status': status,
        'totalTime': total_time,
        'tasks': {
            'total': len(tasks),
            'executed': len(executed_tasks),
            'upToDate': len(up_to_date_tasks),
            'noSource': len(no_source_tasks),
            'failed': len(failed_tasks)
        },
        'failedTasks': failed_tasks,
        'warnings': warnings,
        'tests': {
            'gtest': {
                'total': len(gtest_tests),
                'passed': gtest_passed,
                'failed': gtest_failed,
                'details': gtest_tests[:10]  # Top 10 for summary
            },
            'java': {
                'total': len(java_tests),
                'passed': java_passed,
                'failed': java_failed,
                'skipped': java_skipped,
                'details': java_tests[:10]  # Top 10 for summary
            }
        },
        'depIssues': [],
        'actions': [] if status == 'SUCCESSFUL' and not failed_tasks else ['Review build output']
    }

def generate_markdown_summary(data, log_path):
    """Generate a human-readable markdown summary."""
    md = []
    md.append("# Gradle Build Summary")
    md.append("")
    md.append(f"**Status:** {data['status']}")
    md.append(f"**Total Time:** {data['totalTime']}")
    md.append(f"**Log File:** {log_path}")
    md.append("")

    # Task Summary
    md.append("## Task Summary")
    md.append("")
    md.append(f"- Total tasks: {data['tasks']['total']}")
    md.append(f"- Executed: {data['tasks']['executed']}")
    md.append(f"- Up-to-date: {data['tasks']['upToDate']}")
    md.append(f"- No source: {data['tasks']['noSource']}")
    md.append(f"- Failed: {data['tasks']['failed']}")
    md.append("")

    # Failed Tasks
    if data['failedTasks']:
        md.append("## Failed Tasks")
        md.append("")
        for task in data['failedTasks']:
            md.append(f"- {task['name']}")
        md.append("")

    # Test Results
    md.append("## Test Results")
    md.append("")

    # GTest
    gtest_data = data['tests']['gtest']
    md.append(f"### C++ Tests (GTest)")
    md.append(f"- Total: {gtest_data['total']}")
    md.append(f"- Passed: {gtest_data['passed']}")
    md.append(f"- Failed: {gtest_data['failed']}")
    md.append("")

    if gtest_data['details']:
        md.append("#### Sample Tests")
        for test in gtest_data['details']:
            icon = "✅" if test['status'] == 'PASSED' else "❌"
            md.append(f"- {icon} {test['name']}")
        md.append("")

    # Java Tests
    java_data = data['tests']['java']
    md.append(f"### Java Tests")
    md.append(f"- Total: {java_data['total']}")
    md.append(f"- Passed: {java_data['passed']}")
    md.append(f"- Failed: {java_data['failed']}")
    md.append(f"- Skipped: {java_data['skipped']}")
    md.append("")

    if java_data['details']:
        md.append("#### Sample Tests")
        for test in java_data['details']:
            icon = "✅" if test['status'] == 'PASSED' else ("❌" if test['status'] == 'FAILED' else "⏭️")
            md.append(f"- {icon} {test['class']}.{test['method']}")
        md.append("")

    # Warnings
    if data['warnings']:
        md.append("## Warnings")
        md.append("")
        for warning in data['warnings']:
            md.append(f"- **{warning['type']}**: {warning['message']}")
        md.append("")

    # Actions
    if data['actions']:
        md.append("## Recommended Actions")
        md.append("")
        for action in data['actions']:
            md.append(f"- {action}")
        md.append("")

    return "\n".join(md)

def main():
    if len(sys.argv) != 2:
        print("Usage: parse_gradle_log_final.py <log_file>")
        sys.exit(1)

    log_path = sys.argv[1]
    if not Path(log_path).exists():
        print(f"Error: Log file not found: {log_path}")
        sys.exit(1)

    # Parse the log
    data = parse_gradle_log(log_path)

    # Add log path to data
    data['logFile'] = log_path

    # Create output directory
    output_dir = Path('build/reports/claude')
    output_dir.mkdir(parents=True, exist_ok=True)

    # Write JSON summary
    json_path = output_dir / 'gradle-summary.json'
    with open(json_path, 'w') as f:
        json.dump(data, f, indent=2)
    print(f"Generated: {json_path}")

    # Write Markdown summary
    md_path = output_dir / 'gradle-summary.md'
    md_content = generate_markdown_summary(data, log_path)
    with open(md_path, 'w') as f:
        f.write(md_content)
    print(f"Generated: {md_path}")

    # Print summary
    print(f"\nBuild Status: {data['status']}")
    print(f"Total Time: {data['totalTime']}")
    print(f"Tasks: {data['tasks']['executed']} executed, {data['tasks']['upToDate']} up-to-date")
    print(f"GTest: {data['tests']['gtest']['passed']}/{data['tests']['gtest']['total']} passed")
    print(f"Java Tests: {data['tests']['java']['passed']}/{data['tests']['java']['total']} passed, {data['tests']['java']['skipped']} skipped")

if __name__ == '__main__':
    main()
