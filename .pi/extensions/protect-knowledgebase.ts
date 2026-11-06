// Copyright 2026, Datadog, Inc.
import type { ExtensionAPI } from "@earendil-works/pi-coding-agent";
import { spawnSync } from "node:child_process";
import { existsSync } from "node:fs";
import { join } from "node:path";

// Pi adapter for .claude/hooks/protect-knowledgebase.py. Pi's edit and write tools take
// `path`, drop a leading `@` and expand `~` (the hook expands `~`); Pi has no notebook tool.
export default function (pi: ExtensionAPI) {
  pi.on("tool_call", async (event, ctx) => {
    if (event.toolName !== "edit" && event.toolName !== "write") return undefined;
    const path = String(event.input.path ?? "").replace(/^@/, "");
    if (!path) return undefined;
    // Pi may run in a subdirectory: the hook lives at the checkout's top level.
    const top = spawnSync("git", ["rev-parse", "--show-toplevel"], { cwd: ctx.cwd, encoding: "utf8" });
    const root = top.status === 0 ? top.stdout.trim() : ctx.cwd;
    const hook = join(root, ".claude", "hooks", "protect-knowledgebase.py");
    if (!existsSync(hook)) return undefined; // a checkout from before the hook
    const payload = JSON.stringify({ cwd: ctx.cwd, tool_input: { file_path: path } });
    const res = spawnSync("python3", [hook], {
      input: payload,
      encoding: "utf8",
      env: { ...process.env, CLAUDE_PROJECT_DIR: root },
      timeout: 60_000,
    });
    return res.status === 2 ? { block: true, reason: res.stderr.trim() } : undefined;
  });
}
