---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-05 05:22:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 8 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 8 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (2 unique values: 10-18 cores)</summary>

```
1791191798 18
1791191803 18
1791191808 18
1791191813 18
1791191818 10
1791191823 10
1791191828 10
1791191833 10
1791191838 10
1791191843 10
1791191848 10
1791191853 10
1791191858 10
1791191863 10
1791191868 10
1791191873 10
1791191878 10
1791191883 10
1791191888 10
1791191893 10
```
</details>

---

