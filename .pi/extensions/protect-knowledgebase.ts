// Copyright 2026, Datadog, Inc.
import type { ExtensionAPI } from "@earendil-works/pi-coding-agent";
import { spawnSync } from "node:child_process";
import { existsSync } from "node:fs";
import { join } from "node:path";

// Pi adapter for .claude/hooks/protect-knowledgebase.py. Pi's edit and write tools take
// `path`; the hook reads Claude Code's `file_path`. Pi has no notebook tool.
export default function (pi: ExtensionAPI) {
  pi.on("tool_call", async (event, ctx) => {
    if (event.toolName !== "edit" && event.toolName !== "write") return undefined;
    const path = String(event.input.path ?? "");
    const hook = join(ctx.cwd, ".claude", "hooks", "protect-knowledgebase.py");
    if (!path || !existsSync(hook)) return undefined; // a checkout from before the hook
    const payload = JSON.stringify({ cwd: ctx.cwd, tool_input: { file_path: path } });
    const res = spawnSync("python3", [hook], {
      input: payload,
      encoding: "utf8",
      env: { ...process.env, CLAUDE_PROJECT_DIR: ctx.cwd },
      timeout: 60_000,
    });
    return res.status === 2 ? { block: true, reason: res.stderr.trim() } : undefined;
  });
}
