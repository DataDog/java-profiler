---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-28 05:04:12 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 204 |
| Sample Rate | 3.40/sec |
| Health Score | 212% |
| Threads | 9 |
| Allocations | 180 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 12 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (3 unique values: 46-48 cores)</summary>

```
1793177993 48
1793177998 48
1793178003 48
1793178008 48
1793178014 48
1793178019 47
1793178024 47
1793178029 47
1793178034 47
1793178039 47
1793178044 47
1793178049 47
1793178054 47
1793178059 46
1793178064 46
1793178069 47
1793178074 47
1793178079 47
1793178084 46
1793178089 46
```
</details>

---

