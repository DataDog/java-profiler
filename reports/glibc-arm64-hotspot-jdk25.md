---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-22 11:34:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 276 |
| Sample Rate | 4.60/sec |
| Health Score | 287% |
| Threads | 14 |
| Allocations | 152 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790090955 50
1790090960 50
1790090965 50
1790090970 50
1790090975 50
1790090980 50
1790090985 50
1790090990 50
1790090995 50
1790091000 50
1790091005 50
1790091010 50
1790091015 50
1790091020 50
1790091025 50
1790091030 50
1790091035 50
1790091040 50
1790091045 50
1790091050 50
```
</details>

---

