// Copyright 2026, Datadog, Inc.
import type { ExtensionAPI } from "@earendil-works/pi-coding-agent";
import { spawnSync } from "node:child_process";
import { readFileSync } from "node:fs";
import { homedir } from "node:os";
import { join, relative, resolve, sep } from "node:path";

// Pi may run in a subdirectory: the list and its paths are relative to the checkout's top level.
function checkoutRoot(cwd: string): string {
  const top = spawnSync("git", ["rev-parse", "--show-toplevel"], { cwd, encoding: "utf8" });
  return top.status === 0 ? top.stdout.trim() : cwd;
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

// Pi counterpart of the native-code CLAUDE.md stubs: appends the native instructions to
// the first read, edit or write result below a directory listed in .pi/native-agents.json.
// Once per session, and again after a compaction drops them from the context.
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
    let path = String(event.input.path ?? "").replace(/^@/, "");
    if (path.startsWith("~/")) path = join(homedir(), path.slice(1));
    let root = roots.get(ctx.cwd);
    if (root === undefined) roots.set(ctx.cwd, (root = checkoutRoot(ctx.cwd)));
    const rel = relative(root, resolve(ctx.cwd, path)).split(sep).join("/");
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
