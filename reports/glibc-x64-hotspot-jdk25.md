---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-18 05:19:52 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 453 |
| Sample Rate | 7.55/sec |
| Health Score | 472% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 11 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (3 unique values: 78-96 cores)</summary>

```
1787044355 96
1787044360 96
1787044365 96
1787044370 96
1787044375 96
1787044380 96
1787044385 96
1787044390 96
1787044395 80
1787044400 80
1787044405 80
1787044411 80
1787044416 78
1787044421 78
1787044426 78
1787044431 78
1787044436 78
1787044441 78
1787044446 78
1787044451 78
```
</details>

---

