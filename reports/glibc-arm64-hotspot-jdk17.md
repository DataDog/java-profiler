---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-22 07:06:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 195 |
| Sample Rate | 3.25/sec |
| Health Score | 203% |
| Threads | 10 |
| Allocations | 155 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 10 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (2 unique values: 16-32 cores)</summary>

```
1790074864 16
1790074869 16
1790074874 16
1790074879 16
1790074884 16
1790074889 16
1790074894 16
1790074899 16
1790074904 16
1790074909 16
1790074914 16
1790074919 16
1790074924 16
1790074929 16
1790074934 16
1790074939 16
1790074944 32
1790074949 32
1790074954 32
1790074959 32
```
</details>

---

