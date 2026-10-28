---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-28 07:48:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 11 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (3 unique values: 76-81 cores)</summary>

```
1793187882 76
1793187887 78
1793187892 78
1793187897 78
1793187902 78
1793187907 78
1793187912 78
1793187917 78
1793187922 78
1793187927 78
1793187932 78
1793187937 78
1793187942 81
1793187947 81
1793187952 81
1793187957 81
1793187962 81
1793187967 81
1793187972 81
1793187977 81
```
</details>

---

