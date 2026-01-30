---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-01-30 04:28:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 19.43/sec |
| Health Score | 1214% |
| Threads | 9 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 766 |
| Sample Rate | 25.53/sec |
| Health Score | 1596% |
| Threads | 11 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (2 unique values: 88-96 cores)</summary>

```
1769764955 96
1769764960 96
1769764965 96
1769764971 96
1769764976 96
1769764981 96
1769764986 96
1769764991 96
1769764996 96
1769765001 96
1769765006 96
1769765011 96
1769765016 96
1769765021 96
1769765026 96
1769765031 96
1769765036 88
1769765041 88
1769765046 88
1769765051 88
```
</details>

---

