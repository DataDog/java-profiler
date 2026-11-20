---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 05:14:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 9.83/sec |
| Health Score | 614% |
| Threads | 10 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (4 unique values: 53-76 cores)</summary>

```
1795169315 53
1795169320 53
1795169325 53
1795169330 53
1795169335 53
1795169340 53
1795169345 53
1795169350 53
1795169355 65
1795169360 65
1795169365 65
1795169370 65
1795169375 76
1795169380 76
1795169385 76
1795169390 56
1795169395 56
1795169400 56
1795169405 56
1795169410 56
```
</details>

---

