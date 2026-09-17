---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 14:20:05 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 282 |
| Sample Rate | 4.70/sec |
| Health Score | 294% |
| Threads | 14 |
| Allocations | 121 |

<details>
<summary>CPU Timeline (2 unique values: 37-40 cores)</summary>

```
1789668954 40
1789668959 40
1789668964 40
1789668969 40
1789668974 40
1789668979 40
1789668984 40
1789668989 40
1789668994 40
1789668999 40
1789669004 40
1789669009 40
1789669014 40
1789669019 37
1789669024 37
1789669029 37
1789669034 37
1789669039 37
1789669044 37
1789669050 37
```
</details>

---

