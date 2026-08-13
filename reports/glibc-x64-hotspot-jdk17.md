---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-13 16:15:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 10 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (4 unique values: 64-72 cores)</summary>

```
1786651873 64
1786651878 64
1786651883 64
1786651888 64
1786651893 64
1786651898 64
1786651903 64
1786651908 64
1786651913 64
1786651918 64
1786651923 66
1786651928 66
1786651933 66
1786651938 70
1786651943 70
1786651948 70
1786651953 70
1786651958 70
1786651963 70
1786651968 70
```
</details>

---

