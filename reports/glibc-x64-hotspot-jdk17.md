---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-25 07:37:32 EDT

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 331 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 11 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (2 unique values: 86-88 cores)</summary>

```
1790335984 88
1790335989 86
1790335994 86
1790335999 86
1790336004 86
1790336009 86
1790336014 86
1790336019 86
1790336024 86
1790336029 86
1790336034 88
1790336039 88
1790336044 86
1790336049 86
1790336054 86
1790336059 86
1790336064 86
1790336069 86
1790336074 86
1790336079 86
```
</details>

---

