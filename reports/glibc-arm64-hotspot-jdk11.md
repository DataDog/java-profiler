---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-06 08:27:23 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 13 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1786018994 31
1786018999 31
1786019004 36
1786019009 36
1786019014 31
1786019019 31
1786019024 31
1786019029 31
1786019034 31
1786019039 31
1786019044 31
1786019049 31
1786019054 31
1786019059 31
1786019064 31
1786019069 31
1786019074 36
1786019079 36
1786019084 36
1786019089 36
```
</details>

---

