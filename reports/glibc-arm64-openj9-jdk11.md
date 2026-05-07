---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-07 17:34:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 9 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 332 |
| Sample Rate | 5.53/sec |
| Health Score | 346% |
| Threads | 11 |
| Allocations | 173 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1778189425 59
1778189430 59
1778189435 59
1778189440 59
1778189445 59
1778189450 64
1778189455 64
1778189460 64
1778189465 64
1778189470 64
1778189475 64
1778189480 64
1778189485 64
1778189490 64
1778189495 64
1778189500 64
1778189505 64
1778189510 64
1778189515 64
1778189520 64
```
</details>

---

