// Copyright 2026, Datadog, Inc.
import type { ExtensionAPI } from "@earendil-works/pi-coding-agent";
import { spawnSync } from "node:child_process";

// Pi adapter for the permissions floor of .claude/settings.json: a bash call with a segment
// that starts with a denied `Bash(<cmd>:*)` command is blocked, as Claude Code does.
// A hygiene floor, not a sandbox: allowed tools (python3 -c, sed -i) can still delete.
const TRUSTED_REF = "refs/remotes/origin/main"; // qualified: a tag named origin/main must not win
const DENY_RULE = /^Bash\((.+):\*\)$/;
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

type Ctx = "'" | '"' | "`" | "$(";

// Split a bash command into segments at the separators the shell treats as command
// boundaries ([\n;&|()] and the command-substitution openers). Never inside single
// quotes (everything is literal); inside double quotes only at a command substitution
// boundary, which executes even quoted — so `echo "a && rm b"` is one segment, while
// `echo "pre`rm y`post"` still yields an `rm y` segment. A backslash-newline is a line
// continuation outside single quotes (bash removes the pair inside double quotes too);
// inside single quotes both characters are literal.
export function splitSegments(command: string): string[] {
  const segments: string[] = [];
  let seg = "";
  const stack: Ctx[] = [];
  const top = () => (stack.length ? stack[stack.length - 1]! : "");
  for (let i = 0; i < command.length; i++) {
    const ch = command[i]!;
    const ctx = top();
    if (ctx === "'") {
      seg += ch;
      if (ch === "'") stack.pop();
      continue;
    }
    if ((ctx === "`" && ch === "`") || (ctx === "$(" && ch === ")")) {
      // The closer is a separator, not part of the substituted command: keeping it
      // would turn a bare `echo $(cmd)` into the segment `cmd)`, which neither equals
      // the denied word nor starts with it plus a space.
      segments.push(seg);
      seg = "";
      stack.pop();
      continue;
    }
    if (ch === "\\") {
      if (command[i + 1] === "\n") { i++; continue; } // line continuation: remove the pair
      seg += ch;
      if (i + 1 < command.length) seg += command[++i]!; // escaped character, verbatim
      continue;
    }
    if (ch === "`" || (ch === "$" && command[i + 1] === "(")) {
      const opener = ch === "`" ? "`" : "$(";
      stack.push(opener as Ctx);
      segments.push(seg + opener);
      seg = "";
      if (opener === "$(") i++;
      continue;
    }
    if (ctx === '"') {
      seg += ch;
      if (ch === '"') stack.pop();
      continue;
    }
    if (ch === "'" || ch === '"') {
      stack.push(ch);
      seg += ch;
      continue;
    }
    if (/[\n;&|()]/.test(ch)) {
      segments.push(seg);
      seg = "";
      continue;
    }
    seg += ch;
  }
  segments.push(seg);
  return segments;
}

export default function (pi: ExtensionAPI) {
  pi.on("tool_call", async (event, ctx) => {
    if (event.toolName !== "bash") return undefined;
    const denied = deniedCommands(ctx.cwd);
    for (const segment of splitSegments(String(event.input.command ?? ""))) {
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
