---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-09 05:57:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 5 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 16-64 cores)</summary>

```
1794221660 16
1794221665 16
1794221670 16
1794221675 28
1794221680 28
1794221685 28
1794221690 28
1794221695 28
1794221700 28
1794221705 28
1794221710 28
1794221715 28
1794221720 28
1794221725 64
1794221730 64
1794221735 64
1794221740 64
1794221745 64
1794221750 64
1794221755 64
```
</details>

---

