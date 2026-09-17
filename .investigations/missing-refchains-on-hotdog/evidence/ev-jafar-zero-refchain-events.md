---
id: ev-jafar-zero-refchain-events
type: evidence
status: confirmed
depends_on: [ev-post-resync-deployment-verified]
supersedes: []
related: [find-marker-tag-slot-index-mismatch]
tags: [jfr, jafar, zero-events, post-resync]
created: 2026-08-24
updated: 2026-08-24
---

# Phase 2: event types registered, event count still 0

## Source
jafar MCP `jfr_open` + `jfr_list_types` on the freshest uploaded profile
after the resync.

## Raw excerpts

```json
{"id":19,"alias":"jb-fresh",
 "path":"/tmp/hotdog-jb-fresh3/prof-analyzer-hotdog-2026-08-24_14-46-42.156Z-ip-10-128-190-53.ec2.internal-stripe.jfr",
 "availableTypes":229,"chunkCount":2,"message":"Recording opened successfully"}
```

```json
{"sessionId":19,"totalTypes":2,"totalEvents":0,"scanned":true,
 "eventTypes":[{"name":"datadog.ReferenceChain","count":0},
               {"name":"datadog.ReferenceChainAbandoned","count":0}],
 "filter":"chain"}
```

So: the types are registered by the new binary (proving the feature is
compiled in and the JFR writer is wired), but **zero** events of either
type were emitted in the recording window.
