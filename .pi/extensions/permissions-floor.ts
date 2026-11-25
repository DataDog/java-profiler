// Copyright 2026, Datadog, Inc.
import type { ExtensionAPI } from "@earendil-works/pi-coding-agent";
import { spawnSync } from "node:child_process";

// Pi adapter for the permissions floor of .claude/settings.json: a bash call with a segment
// that starts with a denied `Bash(<cmd>:*)` command is blocked, as Claude Code does.
// A hygiene floor, not a sandbox: allowed tools (python3 -c, sed -i) can still delete.
const TRUSTED_REF = "refs/remotes/origin/main"; // qualified: a tag named origin/main must not win
const DENY_RULE = /^Bash\((.+):\*\)$/;
const SEGMENT = /[\n;&|()`]+/;
const ENV_PREFIX = /^(?:\w+=\S*\s+)*/;

function deniedCommands(cwd: string): string[] {
  // origin/main's floor, never the checkout's: the branch may be untrusted (a fork PR).
  const res = spawnSync("git", ["show", `${TRUSTED_REF}:.claude/settings.json`], {
    cwd,
    encoding: "utf8",
    timeout: 10_000,
  });
  if (res.status !== 0) return []; // not a checkout of this repo, or no floor on main yet
  try {
    const deny: unknown[] = JSON.parse(res.stdout)?.permissions?.deny ?? [];
    return deny.map((r) => DENY_RULE.exec(String(r))?.[1]).filter((c): c is string => !!c);
  } catch {
    return [];
  }
}

export default function (pi: ExtensionAPI) {
  pi.on("tool_call", async (event, ctx) => {
    if (event.toolName !== "bash") return undefined;
    const command = String(event.input.command ?? "");
    const denied = deniedCommands(ctx.cwd);
    for (const segment of command.split(SEGMENT)) {
      const words = segment.trim().replace(ENV_PREFIX, "");
      const hit = denied.find((c) => words === c || words.startsWith(c + " "));
      if (hit) {
        return {
          block: true,
          reason: `Blocked \`${segment.trim()}\`: .claude/settings.json denies Bash(${hit}:*) in agent sessions.`,
        };
      }
    }
    return undefined;
  });
}
