<!-- Copyright 2026, Datadog, Inc. -->

# Work Tracking

The process reference behind the Work Tracking rules in
[AGENTS.md](../AGENTS.md): what each phase produces, and the verification
infrastructure a change relies on. The invariants — verification first, evidence
states, fix the code not the expectation — live in AGENTS.md and always apply;
this page is the how.

Work runs in four phases — Intent → Design → Build and Test → Deploy — with the
tracker ticket as the system of record: decisions and evidence land there, so
anyone can pick the work up without reconstructing a conversation. Datadog
engineers track work in Jira (`PROF-<n>`); external contributors use GitHub
issues.

## Intent — what and why

Work starts from an open tracker ticket stating the what and the why — expected
observable behavior and impact, never the how. Typical inputs: product
requirements, support requests, customer issues, incidents, perf/cost
opportunities, documentation.

- Agent: gather context, dedupe against existing tickets, fill the ticket
  template, map affected code to owners (`CODEOWNERS`), flag missing information
  or unclear ownership for triage.
- Human: correct misunderstandings, resolve judgment calls, align with other
  owners when needed.
- Design-ready when: named owner, clear problem and outcome, enough supporting
  context, defined scope, and required alignment resolved — recorded on the
  ticket when it moves to Design.

## Design — how

Turn the intent into a proposed solution and a way to verify it.

- Agent: investigate the code and existing platforms, propose the approach with
  trade-offs and rejected alternatives, make constraints explicit — isolation,
  compatibility, rollout, recovery.
- Acceptance criteria are written before code, each tagged with where it is
  verified: `local`, `test-drive`, or `production-check`. Production checks stay
  pending until deployment and name the telemetry and observation window they
  need.
- Human: review trade-offs and assumptions. Engineer steering is mandatory on
  critical areas: public API, security, formal models, shared-library behavior,
  schema migrations, new dependencies, perf-critical code.
- Sizing (S/M/L) drives design depth. Output: the design (markdown in a draft
  PR), the acceptance criteria, and the identified review requirements.
- Build-ready when: approach clear enough to implement, verification plan
  feasible, blocking questions and required alignment resolved.

## Build and Test — do it and prove it

- **Plan mode first.** The plan maps every acceptance criterion to a concrete
  check, must be executable without the planning conversation, and lives as a
  versioned `plan.md` (or ticket-linked equivalent — one declared source of
  truth) linked to the ticket and PR. The engineer challenges material choices,
  accepts the plan, and the agent implements autonomously, keeping the plan in
  sync as reality diverges.
- **Advisory vs deterministic.** `AGENTS.md` and skills guide; hooks, CI, and
  access control decide. The agent fixes failures — it never disables a required
  check, weakens an expectation, or changes a tolerance to pass. CI and access
  controls remain authoritative even when a local hook does not fire.
- **Testing loop.** The agent tests its own work throughout, not just at the
  end, against representative data covering normal, boundary, degraded, and
  failure scenarios. The loop is baseline → implement → checks → test drive →
  telemetry compared against baseline — never expectations alone.
- **Parallel sessions.** One task per workspace/worktree; subagents for bounded
  jobs; checks from separate branches never validate the merged result —
  re-verify it. Parallel sessions never broaden authority: they inherit the
  starter's permissions and stay attributable to that engineer; evidence
  identifies the session, candidate, and configuration that produced it.
- **Evidence.** The PR links the tracker ticket and reports every check as
  `passed` / `failed` / `blocked` / `inconclusive` — never prose summaries;
  observed results are kept separate from their interpretation; missing evidence
  means unverified. Evidence binds to the exact candidate; a changed candidate
  invalidates it. Output: a PR plus a rollout plan.

## Verification substrate

The infrastructure the loop above depends on. A change that cannot be verified
with it must ship with its verification story.

- **Reproducible local execution.** One documented command, isolated copies side
  by side, baseline vs candidate: JMH benchmarks with baselines, the container
  matrix runs, the compare/repro scripts in `utils/`.
- **High-fidelity mocks.** Versioned with the contracts they mimic, limits
  explicit. A mock that drifts from its contract verifies the wrong thing with
  full confidence.
- **On-demand test environments.** Container runs for this project; RAPID test
  drives, backend hotdogs, and devkube for Datadog engineers. Ephemeral by
  design: verify, tear down.
- **Instance-specific telemetry.** Logs, metrics, and traces attributable to the
  exact instance and version under test — not aggregates that mix versions. If
  telemetry cannot be scoped, say so instead of passing the check.
- **Agent-accessible tools and context.** CLIs/APIs/MCP for the tools involved,
  and versioned service context kept in the repo. A verification step only a
  human can drive is a verification gap.

## Deploy — ship and verify in production

- **Review.** Agentic review runs on the PR, the coding agent applies the fixes,
  humans approve.
- **Merge.** Merge-queue automation handles rebase/retry/lint churn (PR Shepherd
  where available).
- **Deploy.** The agent triggers the pipeline, confirms version / config /
  flags, and records the deployment on the ticket.
- **Verify.** Release automation validates the rollout where available; the
  coding agent fills gaps with telemetry checked against the production
  acceptance criteria, recording the deployed revision, environment, affected
  cohort, and observation window.
- **Recover.** Follow the rollout plan's stop/recovery steps; the agent
  investigates, the human reviews the fix.
- **Close.** Clean up flags and dead code, link the production results, close
  the ticket — only now. New findings go back to Intent as new tickets; closed
  tickets are never reopened to absorb post-hoc findings.

Done means production evidence shows the intended effect — not "it merged".
