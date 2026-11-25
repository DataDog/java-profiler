// Copyright 2026, Datadog, Inc.
import type { ExtensionAPI } from "@earendil-works/pi-coding-agent";
import { spawnSync } from "node:child_process";
import { isAbsolute, relative, resolve } from "node:path";

// In-loop floor for the doc-reference constraint that utils/check-doc-links.py enforces
// repo-wide: markdown an agent writes may not introduce a link to a path the repository
// does not have. The pi adapter runs the checker itself on the incoming content
// (--check-file), so the two can never disagree; the Claude Code adapter lives in
// .claude/hooks/doc-links-guard.py. A floor, not a sandbox: other write paths (bash
// sed -i) bypass it, and exit 2 (environment error) must not wedge the agent.
export default function (pi: ExtensionAPI) {
  pi.on("tool_call", async (event, ctx) => {
    const tool = String(event.toolName);
    if (tool !== "write" && tool !== "edit") return undefined;
    const input = event.input as Record<string, unknown>;
    const p = String(input.path ?? input.file_path ?? "");
    if (!p.toLowerCase().endsWith(".md")) return undefined;
    // pi's edit tool carries {edits: [{oldText, newText}]}; other harnesses use a single
    // new_string/newText or a whole-file content. Concatenate every new-text fragment the
    // call would introduce; a call with none of them is not a content change to check.
    const edits = Array.isArray(input.edits) ? input.edits : null;
    const fragments = [
      input.content,
      input.new_string,
      ...(edits ? edits.map((e) => (e as Record<string, unknown>)?.newText ??
          (e as Record<string, unknown>)?.new_string) : [input.newText]),
    ];
    const content = fragments
      .filter((f) => typeof f === "string" && f)
      .join("\n");
    if (!content) return undefined;
    const abs = isAbsolute(p) ? p : resolve(ctx.cwd, p);
    const rel = relative(ctx.cwd, abs);
    if (rel.startsWith("..") || isAbsolute(rel) || rel === "") return undefined; // outside the checkout
    const res = spawnSync(
      "python3", ["utils/check-doc-links.py", "--check-file", rel],
      { cwd: ctx.cwd, input: content, encoding: "utf8", timeout: 15_000 },
    );
    if (res.status === 1) {
      return {
        block: true,
        reason: `Blocked: the write would introduce broken doc links.\n${String(res.stdout).trim()}`,
      };
    }
    return undefined;
  });
}
