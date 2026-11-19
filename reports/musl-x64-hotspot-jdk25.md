---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 06:06:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 440 |
| Sample Rate | 7.33/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 11 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (4 unique values: 68-83 cores)</summary>

```
1795085927 83
1795085932 83
1795085937 83
1795085942 83
1795085947 83
1795085952 83
1795085957 83
1795085962 83
1795085967 83
1795085972 73
1795085977 73
1795085982 73
1795085987 73
1795085992 73
1795085997 73
1795086002 68
1795086007 68
1795086012 68
1795086017 68
1795086022 68
```
</details>

---

