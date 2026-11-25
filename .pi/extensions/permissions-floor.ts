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
// Launchers that exec their arguments keep the denied command as the payload; one
// option cluster after the launcher is stripped. Not an argv parser: value-taking
// launchers (e.g. `timeout 5 rm y`) still pass — the floor is a hygiene measure,
// not a sandbox.
const LAUNCHER = /^(?:env|exec|nohup|command|stdbuf|time|xargs|nice|setsid|strace|watch)\s+(?:-\S+\s+)?/;
// cwd → origin/main's deny list, read once per cwd. Never keyed on anything else and
// never populated on failure: a transient git error must disable the floor for one
// call, not for the session.
const deniedCommandsCache = new Map<string, string[]>();

function deniedCommands(cwd: string): string[] {
  const cached = deniedCommandsCache.get(cwd);
  if (cached !== undefined) return cached;
  // origin/main's floor, never the checkout's: the branch may be untrusted (a fork PR).
  const res = spawnSync("git", ["show", `${TRUSTED_REF}:.claude/settings.json`], {
    cwd,
    encoding: "utf8",
    timeout: 10_000,
  });
  if (res.status !== 0) {
    console.error(`permissions floor: failed to read ${TRUSTED_REF}:.claude/settings.json; deny rules are inactive`);
    return [];
  }
  try {
    const deny: unknown[] = JSON.parse(res.stdout)?.permissions?.deny ?? [];
    const rules = deny.map((r) => DENY_RULE.exec(String(r))?.[1]).filter((c): c is string => !!c);
    deniedCommandsCache.set(cwd, rules);
    return rules;
  } catch {
    return [];
  }
}

// Backslash-newline is a line continuation outside single quotes (bash removes the
// pair inside double quotes too); inside single quotes both characters are literal,
// so a quoted argument's text must survive for the deny match on the segment.
export function joinContinuations(command: string): string {
  let out = "";
  let quote: "" | "'" | '"' = "";
  for (let i = 0; i < command.length; i++) {
    const ch = command[i]!;
    if (quote === "'") {
      out += ch;
      if (ch === "'") quote = "";
      continue;
    }
    if (ch === "\\") {
      if (command[i + 1] === "\n") { i++; continue; } // line continuation: remove the pair
      out += ch;
      if (i + 1 < command.length) out += command[++i]!; // escaped character, verbatim
      continue;
    }
    if (quote === '"') {
      out += ch;
      if (ch === '"') quote = "";
      continue;
    }
    if (ch === "'" || ch === '"') quote = ch;
    out += ch;
  }
  return out;
}

export default function (pi: ExtensionAPI) {
  pi.on("tool_call", async (event, ctx) => {
    if (event.toolName !== "bash") return undefined;
    const command = joinContinuations(String(event.input.command ?? ""));
    const denied = deniedCommands(ctx.cwd);
    for (const segment of command.split(SEGMENT)) {
      // Match the segment as written and after stripping each launcher/assignment
      // prefix, so neither a deny rule for the bare command nor one for the launcher
      // form is missed.
      let words = segment.trim().replace(ENV_PREFIX, "").replace(/\s+/g, " ");
      for (;;) {
        const hit = denied.find((c) => words === c || words.startsWith(c + " "));
        if (hit) {
          return {
            block: true,
            reason: `Blocked \`${segment.trim()}\`: .claude/settings.json denies Bash(${hit}:*) in agent sessions.`,
          };
        }
        const stripped = words.replace(LAUNCHER, "").replace(ENV_PREFIX, "").replace(/\s+/g, " ");
        if (stripped === words) break;
        words = stripped;
      }
    }
    return undefined;
  });
}
