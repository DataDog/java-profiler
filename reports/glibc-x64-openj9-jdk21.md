---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-02 11:43:31 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 506 |
| Sample Rate | 8.43/sec |
| Health Score | 527% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 11 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (2 unique values: 54-56 cores)</summary>

```
1788363450 56
1788363455 56
1788363460 56
1788363465 56
1788363470 56
1788363475 56
1788363480 56
1788363485 56
1788363490 56
1788363495 56
1788363500 54
1788363505 54
1788363510 54
1788363515 54
1788363520 54
1788363525 54
1788363530 54
1788363535 54
1788363540 54
1788363545 54
```
</details>

---

