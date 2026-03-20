# Utility Scripts

This directory contains utility scripts for managing the java-profiler project.

## Release Script

### `release.sh`

Triggers the Validated Release workflow using GitHub CLI to create a new release.

**Prerequisites:**
- [GitHub CLI](https://cli.github.com/) installed and authenticated
- Git repository is up to date
- You are on the correct branch for the release type

**Usage:**
```bash
./utils/release.sh <release_type> [options]
```

**Arguments:**
- `release_type`: Type of release (`major`, `minor`, or `patch`)

**Options:**
- `--no-dry-run`: Actually perform the release (default is dry-run)
- `--skip-tests`: Skip pre-release tests (emergency releases only)
- `--branch <name>`: Specify branch to release from (default: current branch)
- `--commit <sha>`: Specify commit SHA to release (default: interactive selection)
- `--help`: Show help message

**Examples:**

1. **Interactive commit selection** (recommended first step):
   ```bash
   ./utils/release.sh minor
   ```
   This will show a nice arrow-key navigable menu of the last 10 commits.

2. **Perform an actual minor release** from main branch:
   ```bash
   ./utils/release.sh minor --no-dry-run
   ```

3. **Release a specific commit**:
   ```bash
   ./utils/release.sh patch --commit abc123def456 --no-dry-run
   ```

4. **Perform a patch release** from a release branch:
   ```bash
   # Ensure you're on a release/X.Y._ branch
   git checkout release/1.35._
   ./utils/release.sh patch --no-dry-run
   ```

5. **Emergency patch** without tests (use with caution):
   ```bash
   ./utils/release.sh patch --no-dry-run --skip-tests
   ```

**Branch Rules:**
- **Major/Minor releases**: Must be run from the `main` branch
- **Patch releases**: Must be run from a `release/X.Y._` branch

**Interactive Features:**
- **Commit Selection**: If no `--commit` is specified, the script shows an interactive menu of the last 10 commits
- Use ↑/↓ arrow keys to navigate
- Press Enter to select a commit
- Press 'q' to quit
- **Comprehensive Summary**: After execution, displays a detailed summary of all actions performed, including any errors or warnings

**Release Flow:**
1. Script validates inputs and branch rules
2. Interactive commit selection (or use specified commit)
3. Triggers GitHub Actions "Validated Release" workflow on selected commit
4. Workflow runs pre-release tests (testDebug + testAsan)
5. Workflow creates annotated git tag
6. Tag push triggers GitLab build pipeline
7. GitLab builds multi-platform artifacts
8. GitLab publishes to Maven Central
9. GitHub workflows create release with assets
10. Script displays comprehensive execution summary

**Monitoring:**

After triggering the release, monitor progress:

```bash
# Watch the workflow run in real-time
gh run watch

# List recent workflow runs
gh run list --workflow=release-validated.yml --limit 5

# View in browser
gh workflow view release-validated.yml --web
```

**Troubleshooting:**

If the release fails:

1. **Tests fail**: Fix the issues and re-run
2. **Tag already exists**: Delete the tag and retry:
   ```bash
   git tag -d v_X.Y.Z
   git push origin :v_X.Y.Z
   ```
3. **GitLab build fails**: Check GitLab pipeline and retry
4. **Authentication issues**: Run `gh auth login`

## Backport Script

### `backport-pr.sh`

Cherry-picks a merged PR onto a release branch, pushes the backport branch, and opens a PR.

**Prerequisites:**
- [GitHub CLI](https://cli.github.com/) installed and authenticated
- [jq](https://jqlang.github.io/jq/) installed
- Clean working tree (no uncommitted changes)

**Usage:**
```bash
./utils/backport-pr.sh [--dry-run] [<release-name>] <pr-number-or-url>
```

**Arguments:**
- `<release-name>`: Target release branch suffix, e.g. `1.9._` (maps to `release/1.9._`). If omitted, the script presents an interactive picker of the 10 most recent release branches.
- `<pr-number-or-url>`: PR number (`420`) or full GitHub URL (`https://github.com/DataDog/java-profiler/pull/420`).
- `--dry-run`: Show what would happen without making any changes.

**Examples:**
```bash
# Backport PR #420 to release/1.9._
./utils/backport-pr.sh 1.9._ 420

# Same, using a URL
./utils/backport-pr.sh 1.9._ https://github.com/DataDog/java-profiler/pull/420

# Interactive branch selection
./utils/backport-pr.sh 420

# Preview without making changes
./utils/backport-pr.sh --dry-run 1.9._ 420
```

**Features:**
- Interactive release branch picker when no branch is specified
- Accepts both PR numbers and full GitHub URLs
- Single GitHub API call for all PR metadata
- Warns if the PR is not merged and asks for confirmation
- Handles squashed/garbage-collected commits by falling back to the merge commit
- Detects and cleans up existing backport branches from previous attempts
- Guided recovery on cherry-pick conflicts (does not leave you stranded)
- Comments on the original PR with a link to the backport for traceability
- Colored terminal output (degrades gracefully in non-TTY contexts)
- Restores the original branch on completion or failure

## Patch dd-java-agent Script

### `patch-dd-java-agent.sh`

Patches a `dd-java-agent.jar` with locally-built ddprof library contents for quick local testing without a full dd-trace-java rebuild.

**Usage:**
```bash
DD_AGENT_JAR=path/to/dd-java-agent.jar DDPROF_JAR=path/to/ddprof.jar ./utils/patch-dd-java-agent.sh
```

## Cherry-Pick Scripts

### `cherry.sh`

Helper script for cherry-picking commits from upstream async-profiler.

### `init_cherypick_repo.sh`

Initializes the repository for cherry-picking from upstream.

---

For more information about the release process, see `.github/workflows/release-validated.yml`.
