#!/usr/bin/env python3
"""
Gradle Log Analyst - Parses Gradle build logs and generates summary reports.
"""

import json
import re
import sys
from datetime import datetime
from pathlib import Path
from typing import Dict, List, Optional, Tuple


class GradleLogParser:
    def __init__(self, log_path: str):
        self.log_path = Path(log_path)
        self.status = "UNKNOWN"
        self.total_time = "N/A"
        self.failed_tasks = []
        self.warnings = []
        self.tests = {
            "total": 0,
            "passed": 0,
            "failed": 0,
            "skipped": 0,
            "modules": []
        }
        self.slow_tasks = []
        self.dep_issues = []
        self.actions = []
        self.task_executions = []
        self.errors = []

    def parse(self):
        """Parse the Gradle log file."""
        if not self.log_path.exists():
            return False

        if self.log_path.stat().st_size == 0:
            self.status = "EMPTY_LOG"
            return False

        try:
            with open(self.log_path, 'r', encoding='utf-8', errors='replace') as f:
                lines = f.readlines()
        except Exception as e:
            self.status = f"READ_ERROR: {e}"
            return False

        # Parse the log
        self._parse_lines(lines)
        return True

    def _parse_lines(self, lines: List[str]):
        """Parse all lines from the log."""
        in_test_summary = False
        in_failure_block = False
        current_failure = None
        test_task = None

        for i, line in enumerate(lines):
            line = line.rstrip()

            # Build outcome
            if "BUILD SUCCESSFUL" in line:
                self.status = "SUCCESS"
            elif "BUILD FAILED" in line:
                self.status = "FAILED"

            # Total time
            match = re.search(r'BUILD (SUCCESSFUL|FAILED) in ([\dhms ]+)', line)
            if match:
                self.total_time = match.group(2).strip()

            # Task execution with timing
            task_match = re.match(r'> Task (:[^\s]+)\s*(.*)?$', line)
            if task_match:
                task_name = task_match.group(1)
                task_detail = task_match.group(2) if task_match.group(2) else ""

                # Look ahead for timing if available
                timing = None
                if i + 1 < len(lines):
                    next_line = lines[i + 1].rstrip()
                    time_match = re.search(r'(\d+\.?\d*)\s*(ms|s|m)', next_line)
                    if time_match:
                        timing = time_match.group(0)

                self.task_executions.append({
                    "task": task_name,
                    "detail": task_detail,
                    "timing": timing
                })

            # Failed tasks
            if re.match(r'> Task :[^\s]+ FAILED', line):
                task = line.split()[2]
                self.failed_tasks.append({"task": task, "reason": "Task failed"})

            # Warnings and deprecations
            if "warning:" in line.lower() or "deprecated" in line.lower():
                self.warnings.append(line.strip())

            # Test results - summary line
            test_summary_match = re.search(r'(\d+) tests? completed?, (\d+) failed?, (\d+) skipped?', line)
            if test_summary_match:
                completed = int(test_summary_match.group(1))
                failed = int(test_summary_match.group(2))
                skipped = int(test_summary_match.group(3))
                passed = completed - failed - skipped

                self.tests["total"] += completed
                self.tests["passed"] += passed
                self.tests["failed"] += failed
                self.tests["skipped"] += skipped

                # Track which task this belongs to
                if test_task:
                    self.tests["modules"].append({
                        "task": test_task,
                        "total": completed,
                        "passed": passed,
                        "failed": failed,
                        "skipped": skipped
                    })

            # Test task detection
            if "> Task :ddprof-test:test" in line:
                test_task = ":ddprof-test:test"

            # Failure details
            if "FAILURE:" in line or "What went wrong:" in line:
                in_failure_block = True
                current_failure = []

            if in_failure_block:
                current_failure.append(line)
                if line.strip() == "" or (line and not line.startswith(" ") and ">" in line):
                    in_failure_block = False
                    self.errors.append("\n".join(current_failure))
                    current_failure = None

            # Dependency issues
            if any(keyword in line for keyword in ["Could not resolve", "timeout", "401", "403", "artifact not found"]):
                self.dep_issues.append(line.strip())

            # Task timing extraction for slow tasks
            timing_match = re.search(r'Task timing: (:[^\s]+) took ([\d.]+)(ms|s|m)', line)
            if timing_match:
                task = timing_match.group(1)
                duration = float(timing_match.group(2))
                unit = timing_match.group(3)

                # Normalize to milliseconds
                if unit == 's':
                    duration *= 1000
                elif unit == 'm':
                    duration *= 60000

                self.slow_tasks.append({
                    "task": task,
                    "duration_ms": duration,
                    "formatted": f"{timing_match.group(2)}{unit}"
                })

        # Sort slow tasks by duration
        self.slow_tasks.sort(key=lambda x: x["duration_ms"], reverse=True)
        self.slow_tasks = self.slow_tasks[:10]  # Top 10

        # If we didn't find explicit status, infer from failures
        if self.status == "UNKNOWN":
            self.status = "FAILED" if self.failed_tasks or self.tests["failed"] > 0 else "SUCCESS"

    def generate_markdown(self) -> str:
        """Generate human-readable markdown summary."""
        lines = [
            "# Gradle Build Summary",
            "",
            f"**Log File:** `{self.log_path.name}`",
            f"**Generated:** {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}",
            "",
            "## Build Outcome",
            "",
            f"- **Status:** {self.status}",
            f"- **Total Time:** {self.total_time}",
            "",
        ]

        # Failed tasks
        if self.failed_tasks:
            lines.extend([
                "## Failed Tasks",
                "",
            ])
            for failure in self.failed_tasks:
                lines.append(f"- `{failure['task']}`: {failure['reason']}")
            lines.append("")

        # Test results
        if self.tests["total"] > 0:
            lines.extend([
                "## Test Results",
                "",
                f"- **Total Tests:** {self.tests['total']}",
                f"- **Passed:** {self.tests['passed']}",
                f"- **Failed:** {self.tests['failed']}",
                f"- **Skipped:** {self.tests['skipped']}",
                "",
            ])

            if self.tests["modules"]:
                lines.append("### Test Modules")
                lines.append("")
                for module in self.tests["modules"]:
                    lines.append(f"- `{module['task']}`: {module['passed']}/{module['total']} passed")
                lines.append("")

        # Errors
        if self.errors:
            lines.extend([
                "## Errors",
                "",
            ])
            for i, error in enumerate(self.errors[:5], 1):  # Limit to 5
                lines.append(f"### Error {i}")
                lines.append("```")
                lines.append(error.strip())
                lines.append("```")
                lines.append("")

        # Warnings
        if self.warnings:
            lines.extend([
                "## Warnings",
                "",
            ])
            for warning in self.warnings[:10]:  # Limit to 10
                lines.append(f"- {warning}")
            if len(self.warnings) > 10:
                lines.append(f"- ... and {len(self.warnings) - 10} more warnings")
            lines.append("")

        # Slow tasks
        if self.slow_tasks:
            lines.extend([
                "## Slowest Tasks",
                "",
            ])
            for task in self.slow_tasks:
                lines.append(f"- `{task['task']}`: {task['formatted']}")
            lines.append("")

        # Dependency issues
        if self.dep_issues:
            lines.extend([
                "## Dependency Issues",
                "",
            ])
            for issue in self.dep_issues[:10]:  # Limit to 10
                lines.append(f"- {issue}")
            lines.append("")

        # Task executions summary
        if self.task_executions:
            lines.extend([
                "## Task Executions",
                "",
                f"Total tasks executed: {len(self.task_executions)}",
                "",
            ])

        # Actions/recommendations
        if self.status == "FAILED":
            lines.extend([
                "## Recommended Actions",
                "",
            ])
            if self.tests["failed"] > 0:
                lines.append("- Review failed tests and fix issues")
            if self.failed_tasks:
                lines.append("- Check failed task logs for details")
            if self.dep_issues:
                lines.append("- Resolve dependency issues")
            lines.append("")

        return "\n".join(lines)

    def generate_json(self) -> Dict:
        """Generate structured JSON report."""
        return {
            "log_file": str(self.log_path),
            "generated_at": datetime.now().isoformat(),
            "status": self.status,
            "totalTime": self.total_time,
            "failedTasks": self.failed_tasks,
            "warnings": self.warnings[:20],  # Limit warnings
            "tests": self.tests,
            "slowTasks": self.slow_tasks,
            "depIssues": self.dep_issues[:20],  # Limit issues
            "actions": self._generate_actions(),
            "taskExecutions": len(self.task_executions),
            "errors": self.errors[:5]  # Limit errors
        }

    def _generate_actions(self) -> List[str]:
        """Generate recommended actions based on analysis."""
        actions = []

        if self.status == "FAILED":
            if self.tests["failed"] > 0:
                actions.append(f"Fix {self.tests['failed']} failing test(s)")
            if self.failed_tasks:
                actions.append(f"Investigate {len(self.failed_tasks)} failed task(s)")
            if self.dep_issues:
                actions.append("Resolve dependency issues")

        if len(self.warnings) > 10:
            actions.append(f"Address {len(self.warnings)} warnings")

        if not actions:
            actions.append("No critical actions required")

        return actions


def main():
    if len(sys.argv) < 2:
        print("Usage: parse_gradle_log_agent.py <log_file_path>", file=sys.stderr)
        sys.exit(1)

    log_path = sys.argv[1]
    output_dir = Path("/home/bits/go/src/github.com/DataDog/java-profiler/build/reports/claude")

    parser = GradleLogParser(log_path)

    if not parser.parse():
        # Handle malformed or empty logs
        error_msg = f"Failed to parse log: {parser.status}"

        # Write minimal reports
        with open(output_dir / "gradle-summary.md", 'w') as f:
            f.write(f"# Gradle Build Summary\n\n**Error:** {error_msg}\n")

        with open(output_dir / "gradle-summary.json", 'w') as f:
            json.dump({"status": "ERROR", "message": error_msg}, f, indent=2)

        print(f"Error: {error_msg}", file=sys.stderr)
        sys.exit(0)  # Exit successfully even on parse failure

    # Generate and write markdown
    markdown = parser.generate_markdown()
    md_path = output_dir / "gradle-summary.md"
    with open(md_path, 'w') as f:
        f.write(markdown)

    # Generate and write JSON
    json_data = parser.generate_json()
    json_path = output_dir / "gradle-summary.json"
    with open(json_path, 'w') as f:
        json.dump(json_data, f, indent=2)

    print(f"Reports generated successfully:")
    print(f"  - {md_path}")
    print(f"  - {json_path}")


if __name__ == "__main__":
    main()
