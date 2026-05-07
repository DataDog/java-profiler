---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-07 17:10:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 9 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 124 |
| Sample Rate | 2.07/sec |
| Health Score | 129% |
| Threads | 10 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1778187907 59
1778187912 59
1778187917 59
1778187922 59
1778187927 59
1778187932 59
1778187937 59
1778187942 59
1778187947 59
1778187952 59
1778187957 59
1778187962 59
1778187967 59
1778187972 64
1778187977 64
1778187982 64
1778187987 64
1778187992 64
1778187997 64
1778188002 64
```
</details>

---

