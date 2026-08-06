---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-06 08:27:25 EDT

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
| CPU Cores (start) | 6 |
| CPU Cores (end) | 7 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 8 |
| Allocations | 429 |

<details>
<summary>CPU Timeline (3 unique values: 6-32 cores)</summary>

```
1786018999 6
1786019004 6
1786019009 32
1786019014 32
1786019019 7
1786019024 7
1786019029 7
1786019034 7
1786019039 7
1786019044 7
1786019049 7
1786019054 7
1786019059 7
1786019064 7
1786019069 7
1786019074 7
1786019079 7
1786019084 7
1786019089 7
1786019094 7
```
</details>

---

