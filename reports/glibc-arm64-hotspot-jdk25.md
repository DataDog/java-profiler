---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-05 05:22:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 275 |
| Sample Rate | 4.58/sec |
| Health Score | 286% |
| Threads | 14 |
| Allocations | 138 |

<details>
<summary>CPU Timeline (2 unique values: 23-28 cores)</summary>

```
1791191852 28
1791191857 28
1791191862 28
1791191867 28
1791191872 28
1791191877 28
1791191882 28
1791191887 28
1791191892 23
1791191897 23
1791191902 23
1791191907 23
1791191912 23
1791191917 23
1791191922 23
1791191927 23
1791191932 23
1791191937 23
1791191942 23
1791191947 23
```
</details>

---

