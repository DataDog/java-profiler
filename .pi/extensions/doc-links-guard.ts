// Copyright 2026, Datadog, Inc.
import type { ExtensionAPI } from "@earendil-works/pi-coding-agent";
import { spawnSync } from "node:child_process";
import { readFileSync } from "node:fs";
import { isAbsolute, relative, resolve } from "node:path";

// In-loop floor for the doc-reference constraint that utils/check-doc-links.py enforces
// repo-wide: markdown an agent writes may not introduce a link to a path the repository
// does not have. The pi adapter runs the checker itself on the document the call would
// produce (--check-file), so the two can never disagree; the Claude Code adapter lives
// in .claude/hooks/doc-links-guard.py. A floor, not a sandbox: other write paths (bash
// sed -i) bypass it, and exit 2 (environment error) must not wedge the agent.
export default function (pi: ExtensionAPI) {
  pi.on("tool_call", async (event, ctx) => {
    const tool = String(event.toolName);
    if (tool !== "write" && tool !== "edit") return undefined;
    const input = event.input as Record<string, unknown>;
    const p = String(input.path ?? input.file_path ?? "");
    if (!/\.(md|markdown)$/i.test(p)) return undefined;
    // Check the document the call would produce, never just the introduced fragment:
    // a fragment's code fences balance against the surrounding file, so fragment-only
    // checking false-blocks valid edits and misses breaks formed by the combination.
    const abs = isAbsolute(p) ? p : resolve(ctx.cwd, p);
    const rel = relative(ctx.cwd, abs);
    if (rel.startsWith("..") || isAbsolute(rel) || rel === "") return undefined; // outside the checkout
    let doc: string | null = null;
    if (tool === "write") {
      if (typeof input.content === "string") doc = input.content;
    } else {
      try {
        doc = readFileSync(abs, "utf8");
      } catch {
        return undefined; // unreadable target: allow, the edit call itself will fail
      }
      // pi's edit tool carries {edits: [{oldText, newText}]}; other harnesses use a
      // single old/new pair. oldText matches at most once (pi's unique-match contract);
      // a function replacement keeps `$` sequences in newText literal.
      const edits = Array.isArray(input.edits)
        ? (input.edits as Record<string, unknown>[])
        : [{ oldText: input.oldText ?? input.old_string, newText: input.newText ?? input.new_string }];
      for (const e of edits) {
        const oldText = typeof e?.oldText === "string" ? e.oldText : null;
        if (oldText === null || !doc.includes(oldText)) {
          doc = null; // cannot reconstruct the result: allow, the edit call will fail
          break;
        }
        const newText = typeof e?.newText === "string" ? e.newText : "";
        doc = doc.replace(oldText, () => newText);
      }
    }
    if (doc === null) return undefined;
    const res = spawnSync(
      "python3", ["utils/check-doc-links.py", "--check-file", rel],
      { cwd: ctx.cwd, input: doc, encoding: "utf8", timeout: 15_000 },
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
