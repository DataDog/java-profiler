---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-23 04:28:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 11 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1776932418 59
1776932423 59
1776932428 59
1776932433 59
1776932438 59
1776932443 59
1776932448 64
1776932453 64
1776932458 64
1776932463 64
1776932468 64
1776932473 64
1776932478 64
1776932483 64
1776932488 64
1776932494 64
1776932499 64
1776932504 64
1776932509 64
1776932514 64
```
</details>

---

