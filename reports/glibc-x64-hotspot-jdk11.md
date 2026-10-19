---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-18 21:28:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 702 |
| Sample Rate | 11.70/sec |
| Health Score | 731% |
| Threads | 9 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (3 unique values: 28-51 cores)</summary>

```
1792373039 28
1792373044 28
1792373049 28
1792373054 51
1792373059 51
1792373064 51
1792373069 51
1792373074 51
1792373079 51
1792373084 51
1792373089 51
1792373094 51
1792373099 51
1792373104 51
1792373109 51
1792373114 51
1792373119 51
1792373124 51
1792373129 51
1792373134 51
```
</details>

---

