#!/usr/bin/env python3

import sys
import re
import json
from pathlib import Path
from datetime import datetime

def parse_gradle_log(log_path):
    """Parse Gradle log and extract structured information."""

    with open(log_path, 'r', encoding='utf-8', errors='ignore') as f:
        lines = f.readlines()

    result = {
        'status': 'UNKNOWN',
        'totalTime': '',
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
        'executedTasks': [],
        'upToDateTasks': [],
        'noSourceTasks': [],
        'gradle_version': '',
        'build_time': '',
        'deprecation_warning': False
    }

    # Extract build status and time
    for line in lines[-20:]:
        if 'BUILD SUCCESSFUL' in line:
            result['status'] = 'SUCCESS'
            match = re.search(r'in (\d+[smh\s]+)', line)
            if match:
                result['totalTime'] = match.group(1).strip()
        elif 'BUILD FAILED' in line:
            result['status'] = 'FAILED'
            match = re.search(r'in (\d+[smh\s]+)', line)
            if match:
                result['totalTime'] = match.group(1).strip()

    # Parse tasks
    task_pattern = re.compile(r'^> Task (:\S+)(?:\s+(UP-TO-DATE|NO-SOURCE|FAILED))?')
    for line in lines:
        match = task_pattern.match(line)
        if match:
            task_name = match.group(1)
            task_status = match.group(2) if match.group(2) else 'EXECUTED'

            if task_status == 'EXECUTED':
                result['executedTasks'].append(task_name)
            elif task_status == 'UP-TO-DATE':
                result['upToDateTasks'].append(task_name)
            elif task_status == 'NO-SOURCE':
                result['noSourceTasks'].append(task_name)
            elif task_status == 'FAILED':
                result['failedTasks'].append({
                    'task': task_name,
                    'reason': 'Task execution failed'
                })

    # Extract warnings
    warning_patterns = [
        (r'warning:', 'Compiler warning'),
        (r'deprecated', 'Deprecation'),
        (r'Deprecated Gradle features', 'Gradle deprecation'),
    ]

    for i, line in enumerate(lines):
        # Compiler warnings
        if 'warning:' in line.lower():
            # Get context lines
            context_start = max(0, i - 1)
            context_end = min(len(lines), i + 3)
            context = ''.join(lines[context_start:context_end]).strip()

            # Extract warning type
            warning_type = 'Compiler warning'
            if '-Wattributes' in line:
                warning_type = 'Attribute warning'
            elif '-Wplacement-new' in line:
                warning_type = 'Placement new warning'

            result['warnings'].append({
                'type': warning_type,
                'message': line.strip(),
                'context': context[:200]
            })

        # Deprecation warnings
        if 'Deprecated Gradle features' in line:
            result['deprecation_warning'] = True
            result['warnings'].append({
                'type': 'Gradle deprecation',
                'message': line.strip(),
                'context': ''
            })

    # Extract actionable tasks count
    for line in lines:
        match = re.search(r'(\d+) actionable tasks?: (\d+) executed(?:, (\d+) up-to-date)?', line)
        if match:
            result['actions'].append({
                'total': int(match.group(1)),
                'executed': int(match.group(2)),
                'upToDate': int(match.group(3)) if match.group(3) else 0
            })

    # Deduplicate warnings
    seen_warnings = set()
    unique_warnings = []
    for w in result['warnings']:
        key = (w['type'], w['message'][:100])
        if key not in seen_warnings:
            seen_warnings.add(key)
            unique_warnings.append(w)
    result['warnings'] = unique_warnings

    # Extract Gradle version
    for line in lines[:50]:
        if 'Gradle' in line and 'daemon' in line:
            match = re.search(r'daemon/([0-9.]+)/', line)
            if match:
                result['gradle_version'] = match.group(1)
                break

    return result


def generate_markdown_summary(data, log_path):
    """Generate human-readable markdown summary."""

    md = []
    md.append("# Gradle Build Summary")
    md.append("")
    md.append(f"**Log File:** `{log_path}`")
    md.append(f"**Generated:** {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    md.append("")

    # Build Status
    status_emoji = "✓" if data['status'] == 'SUCCESS' else "✗"
    md.append(f"## Build Status: {status_emoji} {data['status']}")
    md.append("")
    if data['totalTime']:
        md.append(f"**Total Build Time:** {data['totalTime']}")
    if data['gradle_version']:
        md.append(f"**Gradle Version:** {data['gradle_version']}")
    md.append("")

    # Task Summary
    md.append("## Task Summary")
    md.append("")
    total_tasks = len(data['executedTasks']) + len(data['upToDateTasks']) + len(data['noSourceTasks'])
    md.append(f"- **Total Tasks:** {total_tasks}")
    md.append(f"- **Executed:** {len(data['executedTasks'])}")
    md.append(f"- **Up-to-date:** {len(data['upToDateTasks'])}")
    md.append(f"- **No Source:** {len(data['noSourceTasks'])}")
    md.append(f"- **Failed:** {len(data['failedTasks'])}")
    md.append("")

    # Executed Tasks
    if data['executedTasks']:
        md.append("### Executed Tasks")
        md.append("")
        for task in data['executedTasks']:
            md.append(f"- `{task}`")
        md.append("")

    # Up-to-date Tasks
    if data['upToDateTasks']:
        md.append("### Up-to-date Tasks")
        md.append("")
        for task in data['upToDateTasks']:
            md.append(f"- `{task}`")
        md.append("")

    # Failed Tasks
    if data['failedTasks']:
        md.append("## Failed Tasks")
        md.append("")
        for failed in data['failedTasks']:
            md.append(f"### {failed['task']}")
            md.append("")
            md.append(f"**Reason:** {failed['reason']}")
            md.append("")

    # Warnings
    if data['warnings']:
        md.append("## Warnings")
        md.append("")
        md.append(f"**Total Warnings:** {len(data['warnings'])}")
        md.append("")

        # Group warnings by type
        warning_types = {}
        for w in data['warnings']:
            wtype = w['type']
            if wtype not in warning_types:
                warning_types[wtype] = []
            warning_types[wtype].append(w)

        for wtype, warnings in warning_types.items():
            md.append(f"### {wtype} ({len(warnings)})")
            md.append("")
            for w in warnings[:5]:  # Show first 5 of each type
                md.append(f"- {w['message']}")
            if len(warnings) > 5:
                md.append(f"- ... and {len(warnings) - 5} more")
            md.append("")

    # Deprecations
    if data['deprecation_warning']:
        md.append("## Deprecation Notice")
        md.append("")
        md.append("Deprecated Gradle features were used in this build, making it incompatible with Gradle 9.0.")
        md.append("Use `--warning-mode all` to show individual deprecation warnings.")
        md.append("")

    # Test Summary
    if data['tests']['total'] > 0:
        md.append("## Test Summary")
        md.append("")
        md.append(f"- **Total:** {data['tests']['total']}")
        md.append(f"- **Failed:** {data['tests']['failed']}")
        md.append(f"- **Skipped:** {data['tests']['skipped']}")
        md.append("")

    # Recommendations
    md.append("## Recommendations")
    md.append("")
    if data['deprecation_warning']:
        md.append("- Run with `--warning-mode all` to identify deprecation sources")
    if len(data['warnings']) > 10:
        md.append("- Review and address compiler warnings")
    if data['status'] == 'SUCCESS':
        md.append("- Build completed successfully")
    md.append("")

    return '\n'.join(md)


def main():
    if len(sys.argv) < 2:
        print("Usage: python parse_gradle_final_analyst.py <log-file>")
        sys.exit(1)

    log_path = sys.argv[1]

    if not Path(log_path).exists():
        print(f"Error: Log file not found: {log_path}")
        sys.exit(1)

    # Parse log
    data = parse_gradle_log(log_path)

    # Generate outputs
    base_dir = Path(log_path).parent.parent
    output_dir = base_dir / 'reports' / 'claude'

    # Write JSON
    json_path = output_dir / 'gradle-summary.json'
    with open(json_path, 'w') as f:
        json.dump(data, f, indent=2)

    # Write Markdown
    md_path = output_dir / 'gradle-summary.md'
    md_content = generate_markdown_summary(data, log_path)
    with open(md_path, 'w') as f:
        f.write(md_content)

    print(f"✓ Summary generated successfully")
    print(f"  - JSON: {json_path}")
    print(f"  - Markdown: {md_path}")


if __name__ == '__main__':
    main()
