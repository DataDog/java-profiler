---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-29 06:07:14 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 388 |
| Sample Rate | 6.47/sec |
| Health Score | 404% |
| Threads | 10 |
| Allocations | 188 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 166 |
| Sample Rate | 2.77/sec |
| Health Score | 173% |
| Threads | 11 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (3 unique values: 44-64 cores)</summary>

```
1790675884 44
1790675889 44
1790675894 44
1790675899 44
1790675904 44
1790675909 44
1790675914 44
1790675919 44
1790675924 44
1790675929 44
1790675934 44
1790675939 44
1790675944 44
1790675949 44
1790675954 44
1790675959 64
1790675964 64
1790675969 45
1790675974 45
1790675979 45
```
</details>

---

