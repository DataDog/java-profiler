// Copyright 2026, Datadog, Inc.
import type { ExtensionAPI } from "@earendil-works/pi-coding-agent";
import { spawnSync } from "node:child_process";
import { readFileSync, realpathSync } from "node:fs";
import { basename, dirname, isAbsolute, join, relative, resolve } from "node:path";

// In-loop floor for the doc-reference constraint that utils/check-doc-links.py enforces
// repo-wide: markdown an agent writes may not introduce a link to a path the repository
// does not have. The pi adapter runs the checker itself on the document the call would
// produce (--check-file), so the two can never disagree; the Claude Code adapter lives
// in .claude/hooks/doc-links-guard.py. A floor, not a sandbox: other write paths (bash
// sed -i) bypass it, and exit 2 (environment error) must not wedge the agent.
export default function (pi: ExtensionAPI) {
  // cwd → repository root. The checker lives at the root's utils/, so a session whose
  // cwd is a subdirectory resolves the root once and reuses it.
  const rootCache = new Map<string, string>(); // failures are never stored
  function repoRoot(cwd: string): string | null {
    const cached = rootCache.get(cwd);
    if (cached !== undefined) return cached;
    const res = spawnSync("git", ["rev-parse", "--show-toplevel"], {
      cwd, encoding: "utf8", timeout: 10_000,
    });
    // git reports the symlink-resolved root (macOS /var → /private/var); the tool's
    // cwd may be the symlinked form, so both sides go through realpathSync before the
    // containment comparison. A failed lookup is never cached: a transient git error
    // must disable the guard for one call, not for the session.
    if (res.status !== 0) return null; // a failed lookup is never cached
    const root = realpathSync(String(res.stdout).trim());
    rootCache.set(cwd, root);
    return root;
  }

  pi.on("tool_call", async (event, ctx) => {
    const tool = String(event.toolName);
    if (tool !== "write" && tool !== "edit") return undefined;
    const input = event.input as Record<string, unknown>;
    // Pi's file tools accept `@path` mentions; the guard must see the same path.
    const p = String(input.path ?? input.file_path ?? "").replace(/^@/, "");
    if (!/\.(md|markdown)$/i.test(p)) return undefined;
    // Check the document the call would produce, never just the introduced fragment:
    // a fragment's code fences balance against the surrounding file, so fragment-only
    // checking false-blocks valid edits and misses breaks formed by the combination.
    let cwd: string;
    try {
      cwd = realpathSync(ctx.cwd);
    } catch {
      return undefined; // vanished cwd: allow, the tool call itself will fail
    }
    const root = repoRoot(cwd);
    if (!root) return undefined; // not a checkout: nothing to check against
    let abs = isAbsolute(p) ? p : resolve(cwd, p);
    try {
      abs = realpathSync(abs); // pi may pass the symlinked path (macOS /var)
    } catch {
      try {
        abs = join(realpathSync(dirname(abs)), basename(abs)); // new file: real parent
      } catch {
        return undefined; // parent not resolvable: allow, the write call will fail
      }
    }
    const rel = relative(root, abs);
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
      "python3", [join(root, "utils/check-doc-links.py"), "--check-file", rel],
      { cwd: root, input: doc, encoding: "utf8", timeout: 15_000 },
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
