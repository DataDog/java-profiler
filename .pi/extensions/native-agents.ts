// Copyright 2026, Datadog, Inc.
import type { ExtensionAPI } from "@earendil-works/pi-coding-agent";
import { spawnSync } from "node:child_process";
import { readFileSync } from "node:fs";
import { homedir } from "node:os";
import { join, relative, resolve, sep } from "node:path";

// Pi counterpart of the native-code CLAUDE.md stubs: appends the native instructions to
// the first read, edit or write result below a directory listed in .pi/native-agents.json.
// Once per session, and again after a compaction drops them from the context.
export default function (pi: ExtensionAPI) {
  let injected = false;
  pi.on("session_start", async () => {
    injected = false;
  });
  pi.on("session_compact", async () => {
    injected = false;
  });
  pi.on("tool_result", async (event, ctx) => {
    if (injected) return undefined;
    if (event.toolName !== "read" && event.toolName !== "edit" && event.toolName !== "write") return undefined;
    let path = String(event.input.path ?? "").replace(/^@/, "");
    if (path.startsWith("~/")) path = join(homedir(), path.slice(1));
    // Pi may run in a subdirectory: the list and its paths are relative to the checkout's top level.
    const top = spawnSync("git", ["rev-parse", "--show-toplevel"], { cwd: ctx.cwd, encoding: "utf8" });
    const root = top.status === 0 ? top.stdout.trim() : ctx.cwd;
    const rel = relative(root, resolve(ctx.cwd, path)).split(sep).join("/");
    let list: { instructions: string; dirs: string[] };
    let text: string;
    try {
      list = JSON.parse(readFileSync(join(root, ".pi", "native-agents.json"), "utf8"));
      if (!list.dirs.some((dir) => rel.startsWith(dir + "/"))) return undefined;
      text = readFileSync(join(root, list.instructions), "utf8");
    } catch {
      return undefined; // a checkout without the list or the instructions file
    }
    injected = true;
    const note = `Instructions from ${list.instructions}, which apply to the file above:\n\n${text}`;
    return {
      content: [...event.content, { type: "text", text: note }],
      structuredContent: event.structuredContent,
    };
  });
}
