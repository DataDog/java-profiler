// Copyright 2026, Datadog, Inc.
// Pi adapter for .claude/hooks/babysit-pr.py: the hook JSON payload is built from the
// bash tool_result; exit 2 appends the hook's trigger message to the result the model
// reads. Pi has no block-after-success, so the appended text is the same instruction
// Claude Code receives from the hook's stderr. A loose TS pre-filter (gh + pr
// create|new, applied to the backslash-joined command) skips the spawn for commands
// that cannot match; the hook's PR_CMD stays authoritative.
import type { ExtensionAPI } from "@earendil-works/pi-coding-agent";
import { spawn } from "node:child_process";
import { existsSync } from "node:fs";
import { join } from "node:path";

export default function (pi: ExtensionAPI) {
  pi.on("tool_result", async (event, ctx) => {
    if (event.toolName !== "bash") return undefined;
    if (event.isError) return undefined; // a failed command (e.g. "a pull request
    // for branch ... already exists") is not this run's creation — never a trigger
    const content = Array.isArray(event.content) ? event.content : [];
    const command = String(event.input?.command ?? "");
    if (!content.length && !command) return undefined;
    // Cheap TS pre-filter so the python3 spawn only happens for plausible trigger
    // commands; babysit-pr.py's PR_CMD remains authoritative. Loose on purpose:
    // it only skips when the command cannot match. Backslash-joined like the hook,
    // so a line-continued `gh pr \<newline> create` still passes.
    const joined = command.replace(/\\\n/g, " ");
    if (!/\bgh\b/.test(joined) || !/\bpr\s+(create|new)\b/.test(joined)) return undefined;
    const hook = join(ctx.cwd, ".claude", "hooks", "babysit-pr.py");
    if (!existsSync(hook)) return undefined; // a checkout from before the trigger
    const response = content.map(c => (c.type === "text" ? c.text : "")).join("\n");
    const payload = JSON.stringify({
      cwd: ctx.cwd,
      tool_input: { command },
      tool_response: { stdout: response },
    });
    const res = await new Promise<{ status: number | null; stderr: string }>((resolve) => {
      const child = spawn("python3", [hook], {
        env: { ...process.env, CLAUDE_PROJECT_DIR: ctx.cwd },
        timeout: 60_000,
      });
      let stderr = "";
      child.stderr?.on("data", (d: Buffer) => { stderr += d.toString("utf8"); });
      // python3 may exit before reading all of stdin: swallow the EPIPE error
      child.stdin?.on("error", () => {});
      // Fail open on spawn errors (e.g. python3 missing): never reject — a rejection
      // would crash the extension host instead of silently skipping the trigger.
      child.on("error", () => resolve({ status: null, stderr: "" }));
      // close gives code null on kill/timeout: status null != 2 → fail open, same as
      // the old spawnSync timeout behavior. Resolve is idempotent if error and close
      // both fire (node emits close after a failed spawn).
      child.on("close", (code) => resolve({ status: code, stderr }));
      child.stdin?.end(payload);
    });
    if (res.status !== 2) return undefined;
    const reason = res.stderr.trim();
    if (!reason) return undefined;
    return { content: [...content, { type: "text", text: "\n" + reason }] };
  });
}
