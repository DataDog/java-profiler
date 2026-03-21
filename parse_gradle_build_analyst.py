#!/usr/bin/env python3
"""
Gradle Log Analyst - Parses Gradle build logs and generates summary artifacts.
Outputs:
  1. build/reports/claude/gradle-summary.md (human-readable summary)
  2. build/reports/claude/gradle-summary.json (structured JSON data)
"""

import json
import re
import sys
from pathlib import Path
from datetime import datetime
from collections import defaultdict


def parse_gradle_log(log_path):
    """Parse Gradle build log and extract key information."""

    with open(log_path, 'r', encoding='utf-8', errors='ignore') as f:
        lines = f.readlines()

    # Initialize data structure
    data = {
        'status': 'UNKNOWN',
        'totalTime': None,
        'failedTasks': [],
        'warnings': [],
        'tests': {
            'total': 0,
            'failed': 0,
            'skipped': 0,
            'modules': []
        },
        'slowTasks': [],
        'depIssues': [],
        'actions': [],
        'tasks': [],
        'upToDateCount': 0,
        'noSourceCount': 0,
        'executedCount': 0,
        'deprecationWarnings': []
    }

    # Track tasks with their status and timing
    task_pattern = re.compile(r'^> Task (:\S+)\s*(.*)$')
    build_result_pattern = re.compile(r'^BUILD (SUCCESSFUL|FAILED) in (.+)$')
    deprecation_pattern = re.compile(r'Deprecated Gradle features')
    warning_pattern = re.compile(r'(warning|deprecated|cache|file system)', re.IGNORECASE)

    current_task = None
    task_details = {}

    for line_num, line in enumerate(lines, 1):
        line = line.strip()

        # Extract task execution
        task_match = task_pattern.match(line)
        if task_match:
            task_name = task_match.group(1)
            task_status = task_match.group(2).strip()

            task_info = {
                'name': task_name,
                'status': task_status if task_status else 'EXECUTED',
                'line': line_num
            }

            data['tasks'].append(task_info)
            task_details[task_name] = task_info

            # Count task types
            if 'UP-TO-DATE' in task_status:
                data['upToDateCount'] += 1
            elif 'NO-SOURCE' in task_status:
                data['noSourceCount'] += 1
            else:
                data['executedCount'] += 1

            current_task = task_name

        # Extract build result
        result_match = build_result_pattern.match(line)
        if result_match:
            data['status'] = result_match.group(1)
            data['totalTime'] = result_match.group(2)

        # Extract deprecation warnings
        if deprecation_pattern.search(line):
            data['deprecationWarnings'].append({
                'line': line_num,
                'message': line
            })

        # Extract general warnings
        if warning_pattern.search(line) and not line.startswith('>'):
            if 'Build cache is disabled' not in line:  # Exclude noise
                data['warnings'].append({
                    'line': line_num,
                    'message': line
                })

        # Extract failed tasks (FAILED status)
        if 'FAILED' in line and current_task:
            if current_task not in [t['name'] for t in data['failedTasks']]:
                data['failedTasks'].append({
                    'name': current_task,
                    'line': line_num,
                    'error': line
                })

        # Extract dependency issues
        if any(keyword in line.lower() for keyword in ['could not resolve', 'not found', 'timeout', '401', '403']):
            data['depIssues'].append({
                'line': line_num,
                'message': line
            })

    # Calculate actionable tasks from final summary
    for line in lines:
        if 'actionable tasks:' in line.lower():
            match = re.search(r'(\d+)\s+actionable tasks?', line, re.IGNORECASE)
            if match:
                data['actions'].append({
                    'total': int(match.group(1)),
                    'details': line.strip()
                })

    # Sort tasks by execution order
    data['tasks'].sort(key=lambda x: x['line'])

    return data


def generate_markdown_summary(data, log_path):
    """Generate human-readable markdown summary."""

    md = []
    md.append("# Gradle Build Summary\n")
    md.append(f"**Generated**: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n")
    md.append(f"**Log File**: `{log_path}`\n")
    md.append("")

    # Build Status
    md.append("## Build Status\n")
    status_emoji = "✓" if data['status'] == 'SUCCESSFUL' else "✗"
    md.append(f"- **Status**: {status_emoji} {data['status']}")
    if data['totalTime']:
        md.append(f"- **Total Time**: {data['totalTime']}")
    md.append("")

    # Task Summary
    md.append("## Task Execution Summary\n")
    total_tasks = len(data['tasks'])
    md.append(f"- **Total Tasks**: {total_tasks}")
    md.append(f"- **Up-to-Date**: {data['upToDateCount']}")
    md.append(f"- **No-Source**: {data['noSourceCount']}")
    md.append(f"- **Executed**: {data['executedCount']}")

    if data['actions']:
        for action in data['actions']:
            md.append(f"- {action['details']}")
    md.append("")

    # Task Details
    md.append("## Task Details\n")
    md.append("| Task | Status |")
    md.append("|------|--------|")
    for task in data['tasks']:
        status = task['status'] if task['status'] else 'EXECUTED'
        md.append(f"| `{task['name']}` | {status} |")
    md.append("")

    # Failed Tasks
    if data['failedTasks']:
        md.append("## Failed Tasks\n")
        for failed in data['failedTasks']:
            md.append(f"### {failed['name']}\n")
            md.append(f"- **Line**: {failed['line']}")
            md.append(f"- **Error**: `{failed['error']}`")
            md.append("")

    # Warnings
    if data['warnings'] or data['deprecationWarnings']:
        md.append("## Warnings\n")

        if data['deprecationWarnings']:
            md.append("### Deprecation Warnings\n")
            for warn in data['deprecationWarnings']:
                md.append(f"- Line {warn['line']}: {warn['message']}")
            md.append("")

        if data['warnings']:
            unique_warnings = {}
            for warn in data['warnings']:
                msg = warn['message']
                if msg not in unique_warnings:
                    unique_warnings[msg] = warn['line']

            md.append("### Build Warnings\n")
            for msg, line in sorted(unique_warnings.items(), key=lambda x: x[1]):
                md.append(f"- Line {line}: {msg}")
            md.append("")

    # Dependency Issues
    if data['depIssues']:
        md.append("## Dependency Issues\n")
        for issue in data['depIssues']:
            md.append(f"- Line {issue['line']}: {issue['message']}")
        md.append("")

    # Test Summary
    if data['tests']['total'] > 0:
        md.append("## Test Summary\n")
        md.append(f"- **Total Tests**: {data['tests']['total']}")
        md.append(f"- **Failed**: {data['tests']['failed']}")
        md.append(f"- **Skipped**: {data['tests']['skipped']}")
        md.append("")

    # Key Metrics
    md.append("## Key Metrics\n")
    md.append(f"- **Build Result**: {data['status']}")
    md.append(f"- **Duration**: {data['totalTime'] or 'N/A'}")
    md.append(f"- **Tasks Analyzed**: {total_tasks}")
    md.append(f"- **Cache Efficiency**: {data['upToDateCount']}/{total_tasks} up-to-date ({100*data['upToDateCount']//total_tasks if total_tasks > 0 else 0}%)")
    md.append("")

    return "\n".join(md)


def main():
    if len(sys.argv) < 2:
        print("Usage: parse_gradle_build_analyst.py <log_file_path>")
        sys.exit(1)

    log_path = Path(sys.argv[1])

    if not log_path.exists():
        print(f"Error: Log file not found: {log_path}")
        sys.exit(1)

    # Determine project root and output directory
    project_root = Path("/home/bits/go/src/github.com/DataDog/java-profiler")
    output_dir = project_root / "build" / "reports" / "claude"
    output_dir.mkdir(parents=True, exist_ok=True)

    # Parse log
    print(f"Parsing log file: {log_path}")
    data = parse_gradle_log(log_path)

    # Generate markdown summary
    md_content = generate_markdown_summary(data, str(log_path))
    md_path = output_dir / "gradle-summary.md"
    md_path.write_text(md_content)
    print(f"Generated: {md_path}")

    # Generate JSON summary
    json_path = output_dir / "gradle-summary.json"
    with open(json_path, 'w') as f:
        json.dump(data, f, indent=2)
    print(f"Generated: {json_path}")

    print(f"\nBuild Status: {data['status']}")
    print(f"Total Time: {data['totalTime']}")
    print(f"Tasks: {len(data['tasks'])} total, {data['upToDateCount']} up-to-date")


if __name__ == '__main__':
    main()
