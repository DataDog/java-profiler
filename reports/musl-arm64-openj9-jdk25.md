---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-15 16:13:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 10 |
| Allocations | 39 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 11 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (3 unique values: 14-18 cores)</summary>

```
1794776907 14
1794776912 14
1794776917 14
1794776922 14
1794776927 14
1794776932 14
1794776937 14
1794776942 14
1794776947 14
1794776952 14
1794776957 14
1794776962 14
1794776967 16
1794776972 16
1794776977 18
1794776982 18
1794776987 18
1794776992 18
1794776997 18
1794777002 18
```
</details>

---

