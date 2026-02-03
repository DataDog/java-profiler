---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-03 04:52:44 EST

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 10 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 753 |
| Sample Rate | 12.55/sec |
| Health Score | 784% |
| Threads | 13 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (3 unique values: 86-91 cores)</summary>

```
1770111894 86
1770111899 86
1770111904 86
1770111909 86
1770111914 86
1770111919 86
1770111924 86
1770111929 86
1770111935 86
1770111940 86
1770111945 91
1770111950 91
1770111955 91
1770111960 91
1770111965 91
1770111970 91
1770111975 91
1770111980 91
1770111985 91
1770111990 91
```
</details>

---

