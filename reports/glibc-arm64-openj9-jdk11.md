---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-07 17:10:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 9 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778187916 64
1778187921 64
1778187926 64
1778187931 64
1778187936 64
1778187941 64
1778187946 64
1778187951 64
1778187956 64
1778187961 64
1778187966 64
1778187971 64
1778187976 64
1778187981 64
1778187986 64
1778187991 64
1778187996 64
1778188001 64
1778188006 64
1778188011 64
```
</details>

---

