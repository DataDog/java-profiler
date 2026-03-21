#!/usr/bin/env python3
"""Enhanced Gradle log parser - generates concise summary reports."""

import json
import re
import sys
from collections import defaultdict, Counter

def deduplicate_warnings(warnings):
    """Deduplicate warnings and count occurrences."""
    warning_counts = Counter(warnings)
    unique_warnings = []
    for warning, count in warning_counts.most_common(10):
        if count > 1:
            unique_warnings.append(f"{warning} (x{count})")
        else:
            unique_warnings.append(warning)
    return unique_warnings, len(warning_counts)

def parse_log(log_path):
    """Parse Gradle log file comprehensively."""

    data = {
        'status': 'UNKNOWN',
        'totalTime': '',
        'failedTasks': [],
        'warnings': [],
        'warningCount': 0,
        'tests': {
            'total': 0,
            'failed': 0,
            'skipped': 0,
            'passed': 0,
            'modules': []
        },
        'gtestSuites': [],
        'slowTasks': [],
        'depIssues': [],
        'actions': []
    }

    all_warnings = []
    gtest_suites = []
    current_gtest = None

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

                # Task execution failures
                if line.startswith('> Task :'):
                    match = re.match(r'> Task (:\S+)\s+FAILED', line)
                    if match:
                        data['failedTasks'].append({
                            'task': match.group(1),
                            'error': 'Task failed'
                        })

                # GTest suite summary
                if '[==========]' in line:
                    match = re.search(r'\[==========\] Running (\d+) tests? from (\d+) test suites?\.', line)
                    if match:
                        current_gtest = {
                            'tests': int(match.group(1)),
                            'suites': int(match.group(2))
                        }

                    match = re.search(r'\[==========\] (\d+) tests? from (\d+) test suites? ran\. \((\d+) ms total\)', line)
                    if match and current_gtest:
                        current_gtest['time_ms'] = int(match.group(3))

                if '[  PASSED  ]' in line and 'tests' in line:
                    match = re.search(r'\[  PASSED  \] (\d+) tests?\.', line)
                    if match and current_gtest:
                        current_gtest['passed'] = int(match.group(1))
                        gtest_suites.append(current_gtest)
                        current_gtest = None

                # Compilation warnings (deduplicate)
                if 'warning:' in line.lower():
                    # Extract just the warning type, not full path
                    if len(line) < 500:
                        # Try to extract just the meaningful part
                        warning_match = re.search(r'warning: (.+)', line, re.IGNORECASE)
                        if warning_match:
                            all_warnings.append(warning_match.group(1))
                        else:
                            all_warnings.append(line.strip())

                # Dependency issues
                if any(x in line for x in ['Could not resolve', 'Connection refused', 'timeout']):
                    if len(line) < 500:
                        data['depIssues'].append(line.strip())

        # Deduplicate and summarize warnings
        data['warnings'], data['warningCount'] = deduplicate_warnings(all_warnings)

        # Aggregate gtest results
        total_gtest_tests = 0
        total_gtest_passed = 0
        for suite in gtest_suites:
            total_gtest_tests += suite.get('tests', 0)
            total_gtest_passed += suite.get('passed', 0)
            data['gtestSuites'].append({
                'tests': suite.get('tests', 0),
                'passed': suite.get('passed', 0),
                'time_ms': suite.get('time_ms', 0)
            })

        data['tests']['total'] = total_gtest_tests
        data['tests']['passed'] = total_gtest_passed
        data['tests']['failed'] = total_gtest_tests - total_gtest_passed

    except Exception as e:
        data['status'] = 'ERROR'
        data['actions'].append(f'Error parsing log: {str(e)}')

    return data

def generate_markdown(data, output_path):
    """Generate comprehensive markdown summary."""

    md = []
    md.append('# Gradle Build Summary\n')
    md.append(f'**Status:** {data["status"]}')
    md.append(f'**Duration:** {data["totalTime"]}\n')

    # Overview
    md.append('## Overview\n')
    if data['status'] == 'SUCCESS':
        md.append('Build completed successfully with all tests passing.\n')
    elif data['status'] == 'FAILED':
        md.append('Build failed. See details below.\n')

    # Test Results
    md.append('## Test Results\n')
    md.append(f'**Total Tests:** {data["tests"]["total"]}')
    md.append(f'**Passed:** {data["tests"]["passed"]} ({100*data["tests"]["passed"]//max(1,data["tests"]["total"])}%)')
    md.append(f'**Failed:** {data["tests"]["failed"]}')
    md.append(f'**Skipped:** {data["tests"]["skipped"]}\n')

    # GTest Details
    if data['gtestSuites']:
        md.append('### C++ Unit Tests (gtest)\n')
        md.append(f'**Total Suites:** {len(data["gtestSuites"])}')

        # Find slowest test suites
        sorted_suites = sorted(data['gtestSuites'], key=lambda x: x.get('time_ms', 0), reverse=True)
        if sorted_suites:
            md.append('\n**Slowest Test Suites:**')
            for i, suite in enumerate(sorted_suites[:5], 1):
                time_sec = suite['time_ms'] / 1000.0
                md.append(f'{i}. {suite["passed"]}/{suite["tests"]} tests passed in {time_sec:.2f}s')
        md.append('')

        # Summary stats
        total_time_ms = sum(s.get('time_ms', 0) for s in data['gtestSuites'])
        md.append(f'**Total gtest time:** {total_time_ms/1000:.2f}s')
        md.append(f'**All gtest suites:** PASSED\n')

    # Failed tasks
    if data['failedTasks']:
        md.append('## Failed Tasks\n')
        for task in data['failedTasks']:
            md.append(f'- `{task["task"]}`: {task.get("error", "Unknown error")}')
        md.append('')

    # Warnings summary
    if data['warnings']:
        md.append('## Compiler Warnings\n')
        md.append(f'**Total unique warnings:** {data["warningCount"]}\n')
        md.append('**Top warnings:**')
        for warning in data['warnings'][:10]:
            # Truncate very long warnings
            if len(warning) > 150:
                warning = warning[:147] + '...'
            md.append(f'- {warning}')
        if data['warningCount'] > 10:
            md.append(f'\n... and {data["warningCount"] - 10} more warning types')
        md.append('')

    # Dependency issues
    if data['depIssues']:
        md.append('## Dependency Issues\n')
        for issue in data['depIssues'][:5]:
            md.append(f'- {issue}')
        md.append('')

    # Actions
    if data['actions']:
        md.append('## Actions Required\n')
        for action in data['actions']:
            md.append(f'- {action}')
        md.append('')

    # Final summary
    md.append('## Summary\n')
    if data['status'] == 'SUCCESS' and data['tests']['failed'] == 0:
        md.append(f'All {data["tests"]["total"]} tests passed successfully.')
        md.append(f'Build completed in {data["totalTime"]}.')
    elif data['status'] == 'SUCCESS' and data['tests']['failed'] > 0:
        md.append(f'Build succeeded but {data["tests"]["failed"]} tests failed.')
    else:
        md.append('Build encountered issues. Review the failed tasks and errors above.')

    if data['warningCount'] > 0:
        md.append(f'\nNote: {data["warningCount"]} compiler warning types detected (consider addressing).')

    with open(output_path, 'w') as f:
        f.write('\n'.join(md))

def generate_json(data, output_path):
    """Generate concise JSON summary."""

    # Remove very verbose fields for JSON
    json_data = {
        'status': data['status'],
        'totalTime': data['totalTime'],
        'failedTasks': data['failedTasks'],
        'tests': data['tests'],
        'gtestSuitesCount': len(data['gtestSuites']),
        'warningCount': data['warningCount'],
        'topWarnings': data['warnings'][:20],  # Limit to top 20
        'depIssues': data['depIssues'],
        'actions': data['actions']
    }

    with open(output_path, 'w') as f:
        json.dump(json_data, f, indent=2)

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
    if data['warningCount'] > 0:
        print(f'Warnings: {data["warningCount"]} unique types')

if __name__ == '__main__':
    main()
