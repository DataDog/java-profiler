---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-14 13:57:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 311 |
| Sample Rate | 5.18/sec |
| Health Score | 324% |
| Threads | 10 |
| Allocations | 167 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 9 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (3 unique values: 41-48 cores)</summary>

```
1794682393 46
1794682398 46
1794682403 46
1794682408 48
1794682413 48
1794682418 48
1794682423 48
1794682428 48
1794682433 48
1794682438 48
1794682443 48
1794682448 48
1794682453 48
1794682458 48
1794682463 48
1794682468 48
1794682473 48
1794682478 48
1794682483 46
1794682488 46
```
</details>

---

