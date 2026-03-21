#!/usr/bin/env python3
"""Parse Gradle log and generate summary reports."""

import json
import re
import sys
from collections import defaultdict
from datetime import datetime

def parse_log(log_path):
    """Parse Gradle log file and extract key information."""

    data = {
        'status': 'UNKNOWN',
        'totalTime': '',
        'failedTasks': [],
        'warnings': [],
        'tests': {
            'total': 0,
            'failed': 0,
            'skipped': 0,
            'passed': 0,
            'modules': []
        },
        'slowTasks': [],
        'depIssues': [],
        'actions': [],
        'gtestResults': []
    }

    current_task = None
    task_times = {}
    gtest_output = []
    in_gtest = False
    current_gtest_suite = None

    try:
        with open(log_path, 'r', encoding='utf-8', errors='ignore') as f:
            for line in f:
                line = line.rstrip()

                # Build status
                if 'BUILD SUCCESSFUL' in line:
                    data['status'] = 'SUCCESS'
                    match = re.search(r'in (\d+m \d+s|\d+s)', line)
                    if match:
                        data['totalTime'] = match.group(1)
                elif 'BUILD FAILED' in line:
                    data['status'] = 'FAILED'
                    match = re.search(r'in (\d+m \d+s|\d+s)', line)
                    if match:
                        data['totalTime'] = match.group(1)

                # Task execution
                if line.startswith('> Task :'):
                    match = re.match(r'> Task (:\S+)(?:\s+(UP-TO-DATE|FAILED|FROM-CACHE|NO-SOURCE|SKIPPED))?', line)
                    if match:
                        current_task = match.group(1)
                        status = match.group(2) or 'EXECUTED'
                        if status == 'FAILED':
                            data['failedTasks'].append({
                                'task': current_task,
                                'error': 'Task failed'
                            })

                # GTest output detection
                if 'gtestRelease_' in line or '[==========]' in line or '[ RUN      ]' in line:
                    in_gtest = True
                    gtest_output.append(line)

                    # Parse gtest summary
                    if '[==========]' in line and 'test' in line.lower():
                        match = re.search(r'\[==========\] (\d+) tests? from (\d+) test suites? ran', line)
                        if match:
                            current_gtest_suite = {
                                'total': int(match.group(1)),
                                'suites': int(match.group(2)),
                                'passed': 0,
                                'failed': 0
                            }

                    # Parse gtest pass/fail counts
                    if '[  PASSED  ]' in line:
                        match = re.search(r'\[  PASSED  \] (\d+) tests?', line)
                        if match and current_gtest_suite:
                            current_gtest_suite['passed'] = int(match.group(1))

                    if '[  FAILED  ]' in line:
                        match = re.search(r'\[  FAILED  \] (\d+) tests?', line)
                        if match and current_gtest_suite:
                            current_gtest_suite['failed'] = int(match.group(1))
                            if current_gtest_suite not in data['gtestResults']:
                                data['gtestResults'].append(current_gtest_suite)

                # Warnings
                if 'warning:' in line.lower() or 'deprecated' in line.lower():
                    if len(line) < 500:  # Skip very long lines
                        data['warnings'].append(line.strip())

                # Dependency issues
                if any(x in line for x in ['Could not resolve', '401', '403', 'timeout', 'Connection refused']):
                    if len(line) < 500:
                        data['depIssues'].append(line.strip())

                # Test results from Java tests
                if 'Task has failed previously' in line:
                    data['actions'].append('Some tests failed in previous run')

                # Parse task failure details
                if 'Successful:' in line and 'Failed:' in line:
                    match = re.search(r'Successful:\s*(\d+),\s*Failed:\s*(\d+)', line)
                    if match:
                        passed = int(match.group(1))
                        failed = int(match.group(2))
                        data['tests']['passed'] += passed
                        data['tests']['failed'] += failed
                        data['tests']['total'] += passed + failed

        # Aggregate gtest results
        for gtest in data['gtestResults']:
            data['tests']['total'] += gtest.get('total', 0)
            data['tests']['passed'] += gtest.get('passed', 0)
            data['tests']['failed'] += gtest.get('failed', 0)

    except Exception as e:
        data['status'] = 'ERROR'
        data['actions'].append(f'Error parsing log: {str(e)}')

    return data

def generate_markdown(data, output_path):
    """Generate markdown summary."""

    md = []
    md.append('# Gradle Build Summary\n')
    md.append(f'**Status:** {data["status"]}  ')
    md.append(f'**Duration:** {data["totalTime"]}\n')

    # Overview
    md.append('## Overview\n')
    if data['status'] == 'SUCCESS':
        md.append('Build completed successfully.\n')
    elif data['status'] == 'FAILED':
        md.append('Build failed. See details below.\n')

    # Tests
    md.append('## Test Results\n')
    md.append(f'- **Total:** {data["tests"]["total"]}')
    md.append(f'- **Passed:** {data["tests"]["passed"]}')
    md.append(f'- **Failed:** {data["tests"]["failed"]}')
    md.append(f'- **Skipped:** {data["tests"]["skipped"]}\n')

    if data['gtestResults']:
        md.append('### C++ Unit Tests (gtest)\n')
        for idx, gtest in enumerate(data['gtestResults'], 1):
            md.append(f'- Suite {idx}: {gtest.get("passed", 0)}/{gtest.get("total", 0)} passed')
            if gtest.get('failed', 0) > 0:
                md.append(f'  - {gtest["failed"]} FAILED')
        md.append('')

    # Failed tasks
    if data['failedTasks']:
        md.append('## Failed Tasks\n')
        for task in data['failedTasks']:
            md.append(f'- `{task["task"]}`: {task.get("error", "Unknown error")}')
        md.append('')

    # Warnings
    if data['warnings']:
        md.append('## Warnings\n')
        # Limit to first 20 warnings
        for warning in data['warnings'][:20]:
            if len(warning) < 200:
                md.append(f'- {warning}')
        if len(data['warnings']) > 20:
            md.append(f'\n... and {len(data["warnings"]) - 20} more warnings')
        md.append('')

    # Dependency issues
    if data['depIssues']:
        md.append('## Dependency Issues\n')
        for issue in data['depIssues'][:10]:
            md.append(f'- {issue}')
        md.append('')

    # Actions
    if data['actions']:
        md.append('## Actions Required\n')
        for action in data['actions']:
            md.append(f'- {action}')
        md.append('')

    # Summary
    md.append('## Summary\n')
    if data['status'] == 'SUCCESS':
        md.append('All tasks completed successfully.')
        if data['tests']['failed'] > 0:
            md.append(f'\nNote: {data["tests"]["failed"]} tests failed.')
    else:
        md.append('Build encountered issues. Review the failed tasks and errors above.')

    with open(output_path, 'w') as f:
        f.write('\n'.join(md))

def generate_json(data, output_path):
    """Generate JSON summary."""

    with open(output_path, 'w') as f:
        json.dump(data, f, indent=2)

def main():
    if len(sys.argv) < 2:
        print("Usage: parse_gradle_log.py <log_file>")
        sys.exit(1)

    log_path = sys.argv[1]

    # Parse log
    data = parse_log(log_path)

    # Generate reports
    md_path = 'build/reports/claude/gradle-summary.md'
    json_path = 'build/reports/claude/gradle-summary.json'

    generate_markdown(data, md_path)
    generate_json(data, json_path)

    print(f'Generated reports:')
    print(f'  - {md_path}')
    print(f'  - {json_path}')
    print(f'\nStatus: {data["status"]}')
    print(f'Duration: {data["totalTime"]}')
    print(f'Tests: {data["tests"]["passed"]}/{data["tests"]["total"]} passed')

if __name__ == '__main__':
    main()
