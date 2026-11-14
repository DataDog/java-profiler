---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-14 13:57:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 182 |
| Sample Rate | 3.03/sec |
| Health Score | 189% |
| Threads | 9 |
| Allocations | 122 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 13 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1794682423 38
1794682428 38
1794682433 38
1794682438 38
1794682443 38
1794682448 38
1794682453 38
1794682458 43
1794682463 43
1794682468 43
1794682473 43
1794682478 48
1794682483 48
1794682488 48
1794682493 48
1794682498 48
1794682503 48
1794682508 48
1794682513 48
1794682518 48
```
</details>

---

