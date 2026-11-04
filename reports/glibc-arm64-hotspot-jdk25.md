---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 05:47:32 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 14 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793789001 48
1793789006 48
1793789011 48
1793789016 48
1793789021 48
1793789026 48
1793789031 48
1793789036 48
1793789041 48
1793789046 48
1793789051 48
1793789056 48
1793789061 48
1793789066 48
1793789071 48
1793789076 48
1793789081 48
1793789086 48
1793789091 48
1793789096 48
```
</details>

---

