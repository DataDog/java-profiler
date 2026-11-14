---
id: find-test-order-plugin-unpublished
title: test-order Gradle plugin is unpublished; mavenLocal bootstrap required
kind: finding
tags: [build, gradle, test-order, tooling]
applies_to: [settings.gradle.kts]
source: writing-any-code-thoroughly/find-test-order-plugin-unpublished
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# test-order Gradle plugin is unpublished; mavenLocal bootstrap required

The `me.bechberger.test-order` Gradle plugin was never published as of v0.1.1:
only Maven artifacts (`test-order-core/agent/junit/annotations/...`) exist on
Maven Central; the Sonatype snapshots repo 404s on the plugin metadata (verified
via curl, including `me.bechberger.test-order.gradle.plugin` markers at 0.0.1,
0.1.0, 0.1.1 on the Gradle Plugin Portal). The working route: clone
github.com/parttimenerd/test-order at tag `v0.1.1`, apply one patch (wire
`testTask.finalizedBy("testOrderOfflineRestore")` into the online learn
configuration so a failing test run still persists the learned index), and run
`gradle :test-order-gradle-plugin:publishToMavenLocal` from the plugin module.
`settings.gradle.kts` resolves it via `mavenLocal { content {
includeGroupAndSubgroups("me.bechberger") } }` — the marker's group is
`me.bechberger.test-order` (a subgroup), so plain `includeGroup` excludes it.
Without the mavenLocal artifact every `:ddprof-test` configuration fails with
"plugin not found".

## Evidence
- Verified live during the integration (2026-10-30): 404s from
  plugins.gradle.org and central.sonatype.com snapshots; publishToMavenLocal
  succeeded; build configured only after adding the scoped mavenLocal repo.
- Sphinx review round 1 flagged this as HIGH (F-ce713f6fd764); user dismissed
  it as a consciously accepted prototype tradeoff, documented in
  doc/building/TestingGuide.md ("Test ordering and prioritization").

## What this rules out
- Any CI/other-machine use without repeating the bootstrap.

## Open questions
- Vendor the patched plugin into build-logic if the experiment graduates →
  task-vendor-test-order-plugin
