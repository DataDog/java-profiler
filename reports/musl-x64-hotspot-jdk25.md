---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-23 09:09:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 783 |
| Sample Rate | 13.05/sec |
| Health Score | 816% |
| Threads | 12 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (5 unique values: 32-40 cores)</summary>

```
1790168640 40
1790168645 35
1790168650 35
1790168655 36
1790168660 36
1790168665 36
1790168670 36
1790168675 36
1790168680 32
1790168685 32
1790168690 32
1790168695 32
1790168700 32
1790168705 32
1790168710 39
1790168715 39
1790168720 39
1790168725 39
1790168730 39
1790168735 39
```
</details>

---

