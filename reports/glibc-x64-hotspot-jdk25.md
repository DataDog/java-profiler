---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 08:34:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 413 |
| Sample Rate | 6.88/sec |
| Health Score | 430% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 10 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1795613388 94
1795613393 94
1795613398 94
1795613403 94
1795613408 94
1795613413 94
1795613418 94
1795613423 94
1795613428 94
1795613433 94
1795613438 94
1795613443 94
1795613448 94
1795613453 94
1795613458 94
1795613463 94
1795613468 94
1795613473 96
1795613478 96
1795613483 96
```
</details>

---

