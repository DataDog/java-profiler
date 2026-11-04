// Copyright 2026, Datadog, Inc.
import type { ExtensionAPI } from "@earendil-works/pi-coding-agent";
import { spawnSync } from "node:child_process";
import { existsSync } from "node:fs";
import { join } from "node:path";

// Pi adapter for .claude/hooks/require-gradle-wrapper.py: same JSON payload, and the
// hook's exit 2 blocks the bash call. Any other outcome allows it, as in Claude Code.
export default function (pi: ExtensionAPI) {
  pi.on("tool_call", async (event, ctx) => {
    if (event.toolName !== "bash") return undefined;
    const hook = join(ctx.cwd, ".claude", "hooks", "require-gradle-wrapper.py");
    if (!existsSync(hook)) return undefined; // a checkout from before the hook
    const payload = JSON.stringify({ cwd: ctx.cwd, tool_input: { command: String(event.input.command ?? "") } });
    const res = spawnSync("python3", [hook], {
      input: payload,
      encoding: "utf8",
      env: { ...process.env, CLAUDE_PROJECT_DIR: ctx.cwd },
      timeout: 60_000,
    });
    return res.status === 2 ? { block: true, reason: res.stderr.trim() } : undefined;
  });
}
