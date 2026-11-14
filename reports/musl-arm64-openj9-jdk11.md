---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-14 13:57:45 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 11 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 11 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (5 unique values: 14-34 cores)</summary>

```
1794682383 34
1794682388 34
1794682393 34
1794682398 34
1794682403 34
1794682408 29
1794682413 29
1794682418 29
1794682423 29
1794682428 24
1794682433 24
1794682438 14
1794682443 14
1794682448 14
1794682453 14
1794682458 14
1794682463 14
1794682468 14
1794682473 14
1794682478 14
```
</details>

---

