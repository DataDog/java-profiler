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
    const command = String(event.input.command ?? "");
    if (!command.includes("gradlew")) return undefined; // most commands: skip the python3 spawn
    // Pi may run in a subdirectory: the hook lives at the checkout's top level.
    const top = spawnSync("git", ["rev-parse", "--show-toplevel"], { cwd: ctx.cwd, encoding: "utf8" });
    const root = top.status === 0 ? top.stdout.trim() : ctx.cwd;
    const hook = join(root, ".claude", "hooks", "require-gradle-wrapper.py");
    if (!existsSync(hook)) return undefined; // a checkout from before the hook
    const payload = JSON.stringify({ cwd: ctx.cwd, tool_input: { command } });
    const res = spawnSync("python3", [hook], {
      input: payload,
      encoding: "utf8",
      env: { ...process.env, CLAUDE_PROJECT_DIR: root },
      timeout: 60_000,
    });
    return res.status === 2 ? { block: true, reason: res.stderr.trim() } : undefined;
  });
}
