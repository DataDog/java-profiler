---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-01-30 04:28:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 17.00/sec |
| Health Score | 1062% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 749 |
| Sample Rate | 24.97/sec |
| Health Score | 1561% |
| Threads | 9 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1769764945 30
1769764950 30
1769764955 30
1769764960 32
1769764965 32
1769764970 32
1769764976 32
1769764981 30
1769764986 30
1769764991 30
1769764996 30
1769765001 30
1769765006 30
1769765011 30
1769765016 30
1769765021 32
1769765026 32
1769765031 32
1769765036 32
1769765041 32
```
</details>

---

