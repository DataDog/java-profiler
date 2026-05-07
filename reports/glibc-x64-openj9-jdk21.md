---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-07 09:00:15 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 460 |
| Sample Rate | 7.67/sec |
| Health Score | 479% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 777 |
| Sample Rate | 12.95/sec |
| Health Score | 809% |
| Threads | 11 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (6 unique values: 38-64 cores)</summary>

```
1778158388 38
1778158393 38
1778158398 44
1778158403 44
1778158408 44
1778158413 44
1778158418 42
1778158423 42
1778158428 62
1778158433 62
1778158438 62
1778158443 62
1778158448 62
1778158453 62
1778158458 62
1778158463 62
1778158468 62
1778158473 62
1778158478 62
1778158483 64
```
</details>

---

