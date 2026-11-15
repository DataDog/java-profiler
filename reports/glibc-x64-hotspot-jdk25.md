---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-15 16:13:24 EST

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
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 436 |
| Sample Rate | 7.27/sec |
| Health Score | 454% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 646 |
| Sample Rate | 10.77/sec |
| Health Score | 673% |
| Threads | 11 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1794776917 96
1794776922 96
1794776927 96
1794776932 96
1794776937 96
1794776942 96
1794776947 96
1794776952 96
1794776957 96
1794776962 96
1794776967 96
1794776972 96
1794776977 96
1794776982 96
1794776987 96
1794776992 96
1794776997 96
1794777002 96
1794777007 96
1794777012 96
```
</details>

---

