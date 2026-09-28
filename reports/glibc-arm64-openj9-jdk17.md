---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-28 14:12:55 EDT

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
| CPU Cores (start) | 12 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 219 |
| Sample Rate | 3.65/sec |
| Health Score | 228% |
| Threads | 14 |
| Allocations | 120 |

<details>
<summary>CPU Timeline (2 unique values: 12-32 cores)</summary>

```
1790618912 12
1790618917 32
1790618922 32
1790618927 32
1790618932 32
1790618937 12
1790618942 12
1790618947 12
1790618952 12
1790618957 12
1790618962 12
1790618967 12
1790618972 12
1790618977 12
1790618982 12
1790618987 12
1790618992 12
1790618997 12
1790619002 12
1790619007 12
```
</details>

---

