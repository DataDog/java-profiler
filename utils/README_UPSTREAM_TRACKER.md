# Upstream Async-Profiler Change Tracker

This directory contains scripts to track changes in the upstream async-profiler repository.

## Scripts

All scripts support `-h` or `--help` for detailed usage information.

### check_upstream_changes.sh
Convenient wrapper to check upstream changes locally.

**Usage:**
```bash
# Show help
./utils/check_upstream_changes.sh --help

# Compare against v4.2.1 (current baseline)
./utils/check_upstream_changes.sh

# Compare against specific commit
./utils/check_upstream_changes.sh abc1234

# Compare against 10 commits ago
./utils/check_upstream_changes.sh HEAD~10
```

**Output:**
- Markdown report: `build/upstream-reports/upstream_changes_YYYYMMDD_HHMMSS.md`
- JSON report: `build/upstream-reports/upstream_changes_YYYYMMDD_HHMMSS.json`
- Tracked files list: `build/upstream-reports/tracked_files.txt`

### generate_tracked_files.sh
Identifies which local files should be tracked against upstream.

**Usage:**
```bash
# Show help
./utils/generate_tracked_files.sh --help

# Standard usage
./utils/generate_tracked_files.sh <local_cpp_dir> <upstream_src_dir>
```

**Tracking criteria:**
- File contains async-profiler copyright header
- File exists in upstream repository

### track_upstream_changes.sh
Core logic for change detection and report generation.

**Usage:**
```bash
# Show help
./utils/track_upstream_changes.sh --help

# Standard usage
./utils/track_upstream_changes.sh \
  <upstream_repo_path> \
  <last_commit_sha> \
  <current_commit_sha> \
  <tracked_files_list> \
  <output_md_path> \
  <output_json_path>
```

## Automated CI Workflow

A GitHub Actions workflow runs daily at 3 AM UTC (see `.github/workflows/upstream-tracker.yml`):

- Compares against async-profiler master branch HEAD
- Creates GitHub issues with labels: `upstream-tracking`, `needs-review`
- Tracks state using GitHub repository variable: `UPSTREAM_LAST_COMMIT`

No additional configuration required - the workflow works out of the box.

**Manual trigger:**
```bash
# Normal run (no report if no changes)
gh workflow run upstream-tracker.yml

# Force report generation (for testing)
gh workflow run upstream-tracker.yml -f force_report=true
```

## Report Format

### Markdown Report
- Summary of changes
- List of changed files sorted by commit count
- Recent commits (up to 20)
- Referenced pull requests
- Direct links to GitHub compare views

### JSON Report
- Machine-readable format for automation
- Contains file list, commit counts, date ranges

## Example Output

Based on the latest run (v4.2.1 to a071e8a):
- **27 files changed**
- **71 commits** in range
- Most impacted: profiler.cpp (14 commits), profiler.h (4 commits), stackWalker.cpp (3 commits)

## Compatibility

All scripts are POSIX-compliant and work on:
- macOS (bash 3.2+)
- Linux (bash 3.2+)
- GitHub Actions (Ubuntu)

No bash 4+ features required (no associative arrays or mapfile).
