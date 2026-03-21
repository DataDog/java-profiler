# octo-sts Policy Configuration Request

## Policy Name
`self.upstream-tracker.manage-variables`

## Scope
`DataDog/java-profiler`

## Purpose
Enable the upstream async-profiler change tracker workflow to persist state between runs by reading and writing GitHub Actions variables.

## Required Permissions

The policy needs to grant the following GitHub REST API permissions:

### Actions Variables - Read
- **Endpoint**: `GET /repos/{owner}/{repo}/actions/variables/{name}`
- **Purpose**: Read the last checked commit SHA to determine what changed since last run

### Actions Variables - Update
- **Endpoint**: `PATCH /repos/{owner}/{repo}/actions/variables/{name}`
- **Purpose**: Update the last checked commit SHA after successful run

### Actions Variables - Create
- **Endpoint**: `POST /repos/{owner}/{repo}/actions/variables`
- **Purpose**: Create the variable on first run if it doesn't exist

### Issues - Write
- **Endpoint**: `POST /repos/{owner}/{repo}/issues`
- **Purpose**: Create issues when upstream changes are detected

## Policy Definition Template

```hcl
# This is a template - adjust syntax based on your octo-sts policy system
policy "self.upstream-tracker.manage-variables" {
  scope = "DataDog/java-profiler"

  permissions = [
    "actions:variables:read",
    "actions:variables:write",
    "issues:write"
  ]

  # Alternative format if using REST API paths
  allow = [
    "GET /repos/DataDog/java-profiler/actions/variables/*",
    "PATCH /repos/DataDog/java-profiler/actions/variables/*",
    "POST /repos/DataDog/java-profiler/actions/variables",
    "POST /repos/DataDog/java-profiler/issues"
  ]
}
```

## Workflow Context

This policy is used by `.github/workflows/upstream-tracker.yml` which:
1. Runs daily to check for upstream async-profiler changes
2. Compares tracked files against the last checked commit
3. Creates GitHub issues when changes are detected
4. Persists the current commit SHA for next run

## Variable Used
- **Name**: `UPSTREAM_LAST_COMMIT`
- **Type**: Actions repository variable
- **Value**: 40-character commit SHA (hex)
- **Scope**: Repository-level (not environment-specific)

## Similar Existing Policies
- `self.approve-trivial.approve-pr` - Used for PR auto-approval
- `self.pr-comment` - Used for PR comment management

## Testing
After policy is created, test with:
```bash
gh workflow run upstream-tracker.yml
```

Then verify in Actions tab that the workflow completes successfully and updates the `UPSTREAM_LAST_COMMIT` variable.
