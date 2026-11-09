---
id: deadend-sonatype-snapshot-route
title: Resolving the test-order Gradle plugin from any published source
kind: dead-end
tags: [build, test-order, tooling]
applies_to: []
source: writing-any-code-thoroughly/deadend-sonatype-snapshot-route
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# Resolving the test-order Gradle plugin from any published source

All published-source routes are dead as of 2026-10-30: the Gradle Plugin
Portal has no `me.bechberger.test-order.gradle.plugin` marker (404 at 0.0.1,
0.1.0, 0.1.1); Maven Central has the Maven-plugin and library artifacts but no
Gradle plugin jar and no marker; central.sonatype.com snapshots repo returns
200-HTML for every browse path (SPA catch-all) but 404 on
`maven-metadata.xml` — nothing was ever published there. The README's Gradle
instructions (`version 0.1.1` from the portal; snapshot repo for
`0.0.1-SNAPSHOT`) are both wrong for the released state. Do not retry these
routes; the only working path is build-from-source into mavenLocal
(find-test-order-plugin-unpublished).
