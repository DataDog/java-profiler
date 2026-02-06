---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-06 09:39:27 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 715 |
| Sample Rate | 11.92/sec |
| Health Score | 745% |
| Threads | 9 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (2 unique values: 29-32 cores)</summary>

```
1770388456 32
1770388461 32
1770388466 32
1770388471 32
1770388476 32
1770388481 32
1770388486 29
1770388491 29
1770388496 29
1770388501 29
1770388506 29
1770388511 29
1770388516 29
1770388521 29
1770388526 29
1770388531 29
1770388536 29
1770388541 29
1770388546 29
1770388551 29
```
</details>

---

