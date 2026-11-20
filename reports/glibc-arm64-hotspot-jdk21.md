---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-20 06:42:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 310 |
| Sample Rate | 5.17/sec |
| Health Score | 323% |
| Threads | 9 |
| Allocations | 162 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 10 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795174660 34
1795174665 34
1795174670 34
1795174675 34
1795174680 34
1795174685 34
1795174690 34
1795174695 34
1795174700 29
1795174705 29
1795174710 29
1795174715 29
1795174720 29
1795174725 29
1795174730 29
1795174735 29
1795174740 29
1795174745 29
1795174750 34
1795174755 34
```
</details>

---

