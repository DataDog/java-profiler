---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-12 11:23:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 258 |
| Sample Rate | 4.30/sec |
| Health Score | 269% |
| Threads | 11 |
| Allocations | 150 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 14 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (2 unique values: 34-44 cores)</summary>

```
1786547925 44
1786547930 44
1786547935 44
1786547940 44
1786547945 44
1786547950 44
1786547955 44
1786547960 44
1786547965 44
1786547970 44
1786547975 44
1786547980 44
1786547985 44
1786547990 44
1786547995 44
1786548000 44
1786548005 44
1786548010 44
1786548015 44
1786548020 34
```
</details>

---

