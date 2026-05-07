---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-07 17:10:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 386 |
| Sample Rate | 6.43/sec |
| Health Score | 402% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 11 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (3 unique values: 55-77 cores)</summary>

```
1778187895 55
1778187900 55
1778187905 55
1778187911 55
1778187916 55
1778187921 77
1778187926 77
1778187931 62
1778187936 62
1778187941 62
1778187946 62
1778187951 62
1778187956 62
1778187961 62
1778187966 62
1778187971 62
1778187976 62
1778187981 62
1778187986 62
1778187991 62
```
</details>

---

