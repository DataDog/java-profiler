---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-05 15:03:46 EST

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 10 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 883 |
| Sample Rate | 14.72/sec |
| Health Score | 920% |
| Threads | 12 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (5 unique values: 63-72 cores)</summary>

```
1770321503 66
1770321508 66
1770321513 66
1770321518 66
1770321523 66
1770321528 66
1770321533 63
1770321538 63
1770321543 63
1770321548 63
1770321553 63
1770321558 67
1770321563 67
1770321568 67
1770321573 72
1770321578 72
1770321583 72
1770321588 72
1770321593 72
1770321598 72
```
</details>

---

