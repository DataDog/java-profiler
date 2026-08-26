---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-26 06:37:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 11 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (2 unique values: 44-46 cores)</summary>

```
1787740372 44
1787740377 44
1787740382 44
1787740387 46
1787740392 46
1787740397 46
1787740402 46
1787740407 46
1787740412 46
1787740417 46
1787740422 46
1787740427 46
1787740432 46
1787740437 46
1787740442 46
1787740447 46
1787740452 46
1787740457 46
1787740462 46
1787740467 46
```
</details>

---

