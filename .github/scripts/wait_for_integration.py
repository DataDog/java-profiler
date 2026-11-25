# Copyright 2026, Datadog, Inc.
"""Wait for the candidate's quarantine-aware GitLab verdict through GitHub only."""

import http.client
import json
import os
import re
import sys
import time
import urllib.error
import urllib.parse
import urllib.request


API_URL = "https://api.github.com"
DATADOG_ORG_ID = 365230
REQUIRED_CONTEXTS = (
    "dd-gitlab/prepare-patched-agent",
    "dd-gitlab/validate-dd-trace-quarantine",
    "dd-gitlab/post-pr-comment",
)
BRIDGE_BOT = re.compile(
    r"(gitsync-ddbuild-stable[0-9]+|dd-ghss-(?:ciux|ciexecution)-[0-9]+)\[bot\]"
)
WAIT_SECONDS = 6 * 60 * 60
POLL_SECONDS = 180
MAX_PAGES = 100


class GateError(Exception):
    """Evidence cannot certify this candidate."""


class RetryRead(Exception):
    """A transient read failure requires a fresh snapshot, not cached success."""


class NoRedirect(urllib.request.HTTPRedirectHandler):
    """Refuse redirects so the GitHub token cannot be forwarded to another URL."""

    def redirect_request(self, req, fp, code, msg, headers, newurl):
        return None


OPENER = urllib.request.build_opener(NoRedirect)


class GitHub:
    """Read GitHub evidence under one deadline, including pagination and identity reads."""

    def __init__(self, repo, token, deadline):
        self.repo = repo
        self.token = token
        self.deadline = deadline
        self.trusted_bots = set()

    def get(self, path):
        """Read one JSON response; only transport, invalid JSON and transient HTTP errors retry."""
        remaining = self.deadline - time.monotonic()
        if remaining <= 0:
            raise GateError("Timed out waiting for GitHub integration evidence")
        request = urllib.request.Request(API_URL + path, headers={
            "Accept": "application/vnd.github+json",
            "Authorization": "Bearer " + self.token,
            "X-GitHub-Api-Version": "2022-11-28",
            "User-Agent": "java-profiler-certification",
        })
        try:
            with OPENER.open(request, timeout=min(30, remaining)) as response:
                return json.load(response)
        except urllib.error.HTTPError as error:
            error.close()
            if (error.code >= 500 or error.code == 429
                    or (error.code == 403 and error.headers.get("X-RateLimit-Remaining") == "0")):
                raise RetryRead("GitHub HTTP " + str(error.code)) from error
            raise GateError("GitHub HTTP " + str(error.code) + " reading " + path) from error
        except (OSError, ValueError, http.client.HTTPException) as error:
            raise RetryRead("GitHub transport or JSON read failed") from error

    def statuses(self, sha):
        """Read the full newest-first history; a failed later page invalidates the snapshot."""
        records = []
        for page in range(1, MAX_PAGES + 1):
            batch = self.get(f"/repos/{self.repo}/commits/{sha}/statuses?per_page=100&page={page}")
            if not isinstance(batch, list):
                raise GateError("GitHub statuses response is not an array")
            records.extend(batch)
            if len(batch) < 100:
                return records
        raise GateError("GitHub status history exceeds the pagination limit")

    def verify_publisher(self, status):
        """Match a rotating bridge bot to its current account and Datadog-owned app."""
        creator = status.get("creator")
        if not isinstance(creator, dict):
            raise GateError("Integration status has no publisher")
        login = creator.get("login")
        bot_id = creator.get("id")
        match = BRIDGE_BOT.fullmatch(login) if isinstance(login, str) else None
        if (creator.get("type") != "Bot" or match is None
                or type(bot_id) is not int or bot_id <= 0):
            raise GateError("Integration status has an untrusted publisher")
        identity = (login, bot_id)
        if identity in self.trusted_bots:
            return
        slug = match.group(1)
        app = self.get("/apps/" + slug)
        bot = self.get("/users/" + urllib.parse.quote(login, safe=""))
        if (not isinstance(app, dict) or app.get("slug") != slug
                or not isinstance(app.get("owner"), dict)
                or app["owner"].get("id") != DATADOG_ORG_ID
                or app["owner"].get("type") != "Organization"
                or not isinstance(bot, dict) or type(bot.get("id")) is not int
                or bot.get("id") != bot_id
                or bot.get("login") != login or bot.get("type") != "Bot"):
            raise GateError("Integration publisher is not a Datadog bridge app")
        self.trusted_bots.add(identity)


def latest_statuses(records):
    """Select before checking trust: a newer untrusted update must not expose an older success."""
    latest = {}
    for record in records:
        if not isinstance(record, dict) or not isinstance(record.get("context"), str):
            raise GateError("Malformed GitHub status record")
        context = record["context"].lower()
        if context in REQUIRED_CONTEXTS and context not in latest:
            latest[context] = record
    return latest


def write_summary(sha, states):
    """Append the last observed snapshot even when the gate fails or times out."""
    summary = "## dd-trace-integration (" + sha + ")\n"
    summary += "".join(f"- {context}: {states[context]}\n" for context in REQUIRED_CONTEXTS)
    print(summary, flush=True)
    path = os.environ.get("GITHUB_STEP_SUMMARY")
    if path:
        with open(path, "a", encoding="utf-8") as handle:
            handle.write(summary)


def wait_for_integration(api, sha):
    """Require all three verified verdicts; retries never reuse a previous successful snapshot."""
    states = dict.fromkeys(REQUIRED_CONTEXTS, "missing")
    try:
        while time.monotonic() < api.deadline:
            states = dict.fromkeys(REQUIRED_CONTEXTS, "missing")
            try:
                latest = latest_statuses(api.statuses(sha))
                for context, status in latest.items():
                    state = status.get("state")
                    if state not in ("success", "pending", "failure", "error"):
                        raise GateError("Invalid integration status state for " + context)
                    states[context] = "unverified"
                    if status.get("url") != f"{API_URL}/repos/{api.repo}/statuses/{sha}":
                        raise GateError("Integration status does not belong to the candidate SHA")
                    api.verify_publisher(status)
                    states[context] = state
                if time.monotonic() >= api.deadline:
                    raise GateError("Timed out waiting for GitHub integration evidence")
                if any(state in ("failure", "error") for state in states.values()):
                    raise GateError("GitLab integration verdict failed")
                if all(state == "success" for state in states.values()):
                    return
                print("Waiting: " + ", ".join(f"{key}={value}" for key, value in states.items()),
                      flush=True)
            except RetryRead as error:
                states = dict.fromkeys(REQUIRED_CONTEXTS, "unavailable")
                print(str(error) + "; retrying the complete snapshot", flush=True)
            remaining = api.deadline - time.monotonic()
            if remaining > 0:
                time.sleep(min(POLL_SECONDS, remaining))
        raise GateError("Timed out waiting for GitHub integration evidence")
    finally:
        write_summary(sha, states)


def main():
    """Use only the workflow's repository, full candidate SHA and built-in read token."""
    repo = os.environ.get("GITHUB_REPOSITORY", "")
    sha = os.environ.get("GITHUB_SHA", "")
    token = os.environ.get("GITHUB_TOKEN", "")
    try:
        if not re.fullmatch(r"[A-Za-z0-9_.-]+/[A-Za-z0-9_.-]+", repo):
            raise GateError("GITHUB_REPOSITORY must identify owner/repository")
        if not re.fullmatch(r"[0-9a-f]{40}", sha):
            raise GateError("GITHUB_SHA must be a full commit SHA")
        if not token:
            raise GateError("GITHUB_TOKEN is not configured")
        wait_for_integration(GitHub(repo, token, time.monotonic() + WAIT_SECONDS), sha)
    except (GateError, OSError) as error:
        print("::error::" + str(error), file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
