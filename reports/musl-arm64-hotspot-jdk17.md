---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-22 11:34:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 286 |
| Sample Rate | 4.77/sec |
| Health Score | 298% |
| Threads | 12 |
| Allocations | 148 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 7 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 34-36 cores)</summary>

```
1790090906 36
1790090911 34
1790090916 34
1790090921 34
1790090926 34
1790090931 34
1790090936 34
1790090941 34
1790090946 34
1790090951 34
1790090956 34
1790090961 36
1790090966 36
1790090971 36
1790090976 36
1790090981 36
1790090986 36
1790090991 36
1790090996 36
1790091001 36
```
</details>

---

