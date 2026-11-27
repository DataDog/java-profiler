// Copyright 2026, Datadog, Inc.
import type { ExtensionAPI } from "@earendil-works/pi-coding-agent";
import { spawnSync } from "node:child_process";

// Pi adapter for the permissions floor of .claude/settings.json: a bash call with a segment
// that starts with a denied `Bash(<cmd>:*)` command is blocked, as Claude Code does.
// A hygiene floor, not a sandbox: allowed tools (python3 -c, sed -i) can still delete.
const TRUSTED_REF = "refs/remotes/origin/main"; // qualified: a tag named origin/main must not win
const DENY_RULE = /^Bash\((.+):\*\)$/;
// Launchers that exec their arguments keep the denied command as the payload; one
// option cluster after the launcher is stripped. Not an argv parser: value-taking
// launchers (e.g. `timeout 5 rm y`) still pass — the floor is a hygiene measure,
// not a sandbox.
const LAUNCHER = /^(?:env|exec|export|nohup|command|stdbuf|time|xargs|nice|setsid|strace|watch)\s+(?:-\S+\s+)?/;
// Control-flow keywords that introduce a command without ending the previous one
// (`if true; then rm y; fi`).
const KEYWORD = /^(?:then|do|else|elif)\s+/;
// NAME=<shell word>, where the value may be quoted (containing spaces) or use
// backslash escapes; bash concatenates adjacent quoted/bare parts into one value.
const ASSIGN = /^\w+=(?:"(?:[^"\\]|\\.)*"|'[^']*'|(?:\\.|[^ \t"'\\]))*(?:\s+|$)/;
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
// boundaries. Shell text that never executes is not a segment: single-quoted content,
// double-quoted text outside a command substitution, `#` comments at a word start, and
// heredoc/herestring bodies are kept out; a command substitution boundary executes even
// inside double quotes, so it still splits. A backslash-newline is a line continuation
// outside single quotes (bash removes the pair inside double quotes too); inside
// single quotes both characters are literal. `(...)` nesting inside a command
// substitution is tracked, so a subshell's closing parenthesis does not end the
// substitution early. Heredocs are recognized only outside quotes and substitutions,
// one line of `<<` operators at a time.
export function splitSegments(command: string): string[] {
  const segments: string[] = [];
  let seg = "";
  const stack: Ctx[] = [];
  let parenDepth = 0; // (...) nesting inside the innermost command substitution
  let pendingHeredocs: { delim: string; dash: boolean }[] = [];
  const top = () => (stack.length ? stack[stack.length - 1]! : "");

  // shell word at from (quote-aware, backslash escapes), for herestring data
  const skipWord = (from: number): number => {
    let j = from;
    while (j < command.length && /[ \t]/.test(command[j]!)) j++;
    if (command[j] === "'" || command[j] === '"') {
      const q = command[j]!;
      j++;
      while (j < command.length && command[j] !== q) j += command[j] === "\\" ? 2 : 1;
      return j < command.length ? j + 1 : j;
    }
    while (j < command.length && !/[\s;&|()<>\n]/.test(command[j]!)) j += command[j] === "\\" ? 2 : 1;
    return j;
  };

  // consume heredoc bodies for every pending delimiter; returns the index after the
  // last body. A body is data, never commands, so it enters no segment.
  const consumeHeredocs = (from: number): number => {
    let i = from;
    for (const { delim, dash } of pendingHeredocs) {
      while (i < command.length) {
        let eol = command.indexOf("\n", i);
        if (eol === -1) eol = command.length;
        const line = dash ? command.slice(i, eol).replace(/^\t+/, "") : command.slice(i, eol);
        i = eol + 1;
        if (line === delim) break;
      }
    }
    pendingHeredocs = [];
    return i;
  };

  for (let i = 0; i < command.length; i++) {
    const ch = command[i]!;
    const ctx = top();
    if (ctx === "'") {
      seg += ch;
      if (ch === "'") stack.pop();
      continue;
    }
    if ((ctx === "`" && ch === "`") || (ctx === "$(" && ch === ")" && parenDepth === 0)) {
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
    if (ctx === "$(" || ctx === "`") {
      if (ch === "(") { parenDepth++; segments.push(seg); seg = ""; continue; }
      if (ch === ")" && parenDepth > 0) { parenDepth--; segments.push(seg); seg = ""; continue; }
    }
    const wordStart = seg === "" || /[ \t]$/.test(seg);
    if (ch === "#" && (ctx === "" || ctx === "$(") && wordStart) {
      // comment: through the end of the line; nothing in it executes or quotes
      while (i < command.length && command[i] !== "\n") i++;
      i--;
      continue;
    }
    if (ctx === "" && ch === "<" && command[i + 1] === "<") {
      if (command[i + 2] === "<") { // herestring: the next word is data, never a command
        segments.push(seg + "<<<");
        seg = "";
        i = skipWord(i + 3) - 1;
        continue;
      }
      let j = i + 2;
      const dash = command[j] === "-";
      if (dash) j++;
      while (j < command.length && /[ \t]/.test(command[j]!)) j++;
      let delim = "";
      if (command[j] === "'" || command[j] === '"') {
        const q = command[j]!;
        j++;
        while (j < command.length && command[j] !== q) { delim += command[j]!; j++; }
        j++; // closing quote
      } else {
        while (j < command.length && /\S/.test(command[j]!) && !/[;&|()<>`]/.test(command[j]!)) {
          delim += command[j]!; j++;
        }
      }
      if (delim) {
        pendingHeredocs.push({ delim, dash });
        seg += command.slice(i, j);
        i = j - 1;
        continue;
      }
    }
    if (ch === "'" || ch === '"') {
      stack.push(ch);
      seg += ch;
      continue;
    }
    if (/[\n;&|()]/.test(ch)) {
      segments.push(seg);
      seg = "";
      if (ch === "\n" && pendingHeredocs.length && stack.length === 0) {
        i = consumeHeredocs(i + 1) - 1;
      }
      continue;
    }
    seg += ch;
  }
  segments.push(seg);
  return segments;
}

// Strip exactly one leading token: an assignment (quote-aware value), a launcher, or
// a control-flow keyword. The caller re-matches after each strip, so a deny rule for
// an intermediate form (e.g. Bash(env:*) on `env rm y`) is not skipped.
function stripOne(words: string): string {
  const assign = ASSIGN.exec(words);
  if (assign) return words.slice(assign[0].length).replace(/^[ \t]+/, "");
  return words.replace(LAUNCHER, "").replace(KEYWORD, "").replace(/^[ \t]+/, "");
}

export default function (pi: ExtensionAPI) {
  pi.on("tool_call", async (event, ctx) => {
    if (event.toolName !== "bash") return undefined;
    const denied = deniedCommands(ctx.cwd);
    for (const segment of splitSegments(String(event.input.command ?? ""))) {
      // Match the segment as written and after each assignment/launcher/keyword strip,
      // so a deny rule for the bare command and for an intermediate form both hit.
      let words = segment.trim().replace(/\s+/g, " ");
      for (;;) {
        const hit = denied.find((c) => words === c || words.startsWith(c + " "));
        if (hit) {
          return {
            block: true,
            reason: `Blocked \`${segment.trim()}\`: .claude/settings.json denies Bash(${hit}:*) in agent sessions.`,
          };
        }
        const stripped = stripOne(words);
        if (stripped === words) break;
        words = stripped;
      }
    }
    return undefined;
  });
}
