---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-17 06:25:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1794914425 30
1794914430 30
1794914435 28
1794914440 28
1794914445 28
1794914450 28
1794914455 28
1794914460 28
1794914465 28
1794914470 28
1794914475 28
1794914480 28
1794914485 28
1794914490 30
1794914495 30
1794914500 32
1794914505 32
1794914510 32
1794914515 32
1794914520 32
```
</details>

---

