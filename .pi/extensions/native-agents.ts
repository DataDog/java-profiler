// Copyright 2026, Datadog, Inc.
import type { ExtensionAPI } from "@earendil-works/pi-coding-agent";
import { spawnSync } from "node:child_process";
import { readFileSync, realpathSync } from "node:fs";
import { homedir } from "node:os";
import { basename, dirname, join, relative, resolve, sep } from "node:path";
import { fileURLToPath } from "node:url";

// Pi may run in a subdirectory: the list and its paths are relative to the checkout's top level.
function checkoutRoot(cwd: string): string {
  const top = spawnSync("git", ["rev-parse", "--show-toplevel"], { cwd, encoding: "utf8" });
  return top.status === 0 ? top.stdout.trim() : cwd;
}

// p with symlinks resolved, like git's root, so both sides of relative() agree. A write may
// name a file and directories that do not exist yet: those keep their names below the deepest
// existing ancestor.
function realize(p: string): string {
  try {
    return realpathSync(p);
  } catch {
    const parent = dirname(p);
    return parent === p ? p : join(realize(parent), basename(p));
  }
}

// The absolute path that Pi's file tools use for input, or null for a file URL that Pi rejects.
// Mirrors Pi's resolveToCwd, which the package does not export, without its Windows branch.
function resolveToolPath(input: string, cwd: string): string | null {
  let p = input.replace(/[\u00A0\u2000-\u200A\u202F\u205F\u3000]/g, " ").replace(/^@/, "");
  if (p === "~") p = homedir();
  else if (p.startsWith("~/")) p = join(homedir(), p.slice(2));
  else if (p.startsWith("file://")) {
    try {
      p = fileURLToPath(p);
    } catch {
      return null; // a host or an encoded "/", which the tool call itself fails on
    }
  }
  return resolve(cwd, p);
}

// The instructions for rel, a path relative to root, if it is below a directory listed in
// root's .pi/native-agents.json; null for any other path or a missing or malformed file.
function instructionsFor(root: string, rel: string): { path: string; text: string } | null {
  try {
    const list = JSON.parse(readFileSync(join(root, ".pi", "native-agents.json"), "utf8"));
    if (!list.dirs.some((dir: string) => rel.startsWith(dir + "/"))) return null;
    return { path: list.instructions, text: readFileSync(join(root, list.instructions), "utf8") };
  } catch {
    return null; // a missing list or instructions file, or a list of the wrong shape
  }
}

// Pi counterpart of the native-code CLAUDE.md stubs: appends the native instructions to the
// first read, edit or write result that reaches the model for a path below a directory listed
// in .pi/native-agents.json. Once per session, and again after a compaction drops them.
export default function (pi: ExtensionAPI) {
  let injected = false;
  // checkoutRoot per cwd, kept for the session, so that file tool calls before the first
  // injection do not each spawn git. The list is re-read on each call: it is one small file.
  let roots = new Map<string, string>();
  pi.on("session_start", async () => {
    injected = false;
    roots = new Map();
  });
  pi.on("session_compact", async () => {
    injected = false;
  });
  pi.on("tool_result", async (event, ctx) => {
    if (injected) return undefined;
    // A call made by another tool (codemode) returns its result to that tool, not to the model.
    if (event.parentToolCallId !== undefined) return undefined;
    if (event.toolName !== "read" && event.toolName !== "edit" && event.toolName !== "write") return undefined;
    const path = resolveToolPath(String(event.input.path ?? ""), ctx.cwd);
    if (path === null) return undefined;
    let root = roots.get(ctx.cwd);
    if (root === undefined) roots.set(ctx.cwd, (root = realize(checkoutRoot(ctx.cwd))));
    const rel = relative(root, realize(path)).split(sep).join("/");
    const found = instructionsFor(root, rel);
    if (!found) return undefined;
    injected = true;
    const note = `Instructions from ${found.path}, which apply to the file above:\n\n${found.text}`;
    return {
      content: [...event.content, { type: "text", text: note }],
      structuredContent: event.structuredContent,
    };
  });
}
