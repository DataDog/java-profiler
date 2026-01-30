---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-01-30 04:28:20 EST

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 18.83/sec |
| Health Score | 1177% |
| Threads | 10 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 23.17/sec |
| Health Score | 1448% |
| Threads | 11 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (5 unique values: 43-73 cores)</summary>

```
1769764976 57
1769764981 57
1769764986 57
1769764991 57
1769764996 43
1769765001 43
1769765006 43
1769765011 43
1769765016 48
1769765021 48
1769765026 48
1769765031 48
1769765036 48
1769765041 48
1769765046 48
1769765051 48
1769765056 47
1769765061 47
1769765066 47
1769765071 47
```
</details>

---

