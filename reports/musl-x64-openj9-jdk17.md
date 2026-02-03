---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-03 04:52:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 8 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 909 |
| Sample Rate | 15.15/sec |
| Health Score | 947% |
| Threads | 10 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (5 unique values: 38-50 cores)</summary>

```
1770111959 42
1770111964 42
1770111969 40
1770111974 40
1770111979 40
1770111984 40
1770111989 40
1770111994 40
1770111999 40
1770112004 40
1770112009 40
1770112014 40
1770112019 40
1770112024 38
1770112029 38
1770112034 38
1770112039 38
1770112044 40
1770112049 40
1770112054 42
```
</details>

---

