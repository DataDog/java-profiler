---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 08:20:13 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 187 |
| Sample Rate | 3.12/sec |
| Health Score | 195% |
| Threads | 11 |
| Allocations | 131 |

<details>
<summary>CPU Timeline (4 unique values: 45-48 cores)</summary>

```
1794402894 48
1794402899 48
1794402904 48
1794402909 48
1794402914 48
1794402919 48
1794402924 48
1794402929 48
1794402934 46
1794402939 46
1794402944 46
1794402949 46
1794402954 45
1794402959 45
1794402964 45
1794402969 45
1794402974 45
1794402979 45
1794402984 45
1794402989 45
```
</details>

---

