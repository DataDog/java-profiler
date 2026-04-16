---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-16 06:02:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 976 |
| Sample Rate | 16.27/sec |
| Health Score | 1017% |
| Threads | 10 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776333329 64
1776333334 64
1776333339 64
1776333344 64
1776333349 64
1776333354 64
1776333359 64
1776333364 64
1776333369 64
1776333374 64
1776333379 64
1776333384 64
1776333389 64
1776333394 64
1776333399 64
1776333404 64
1776333409 64
1776333414 64
1776333419 64
1776333424 64
```
</details>

---

