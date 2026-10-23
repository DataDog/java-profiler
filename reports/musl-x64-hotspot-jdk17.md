---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-23 10:56:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 10 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (3 unique values: 49-59 cores)</summary>

```
1792767094 59
1792767099 59
1792767104 51
1792767109 51
1792767114 51
1792767120 51
1792767125 51
1792767130 51
1792767135 51
1792767140 51
1792767145 51
1792767150 51
1792767155 51
1792767160 51
1792767165 51
1792767170 51
1792767175 51
1792767180 51
1792767185 51
1792767190 51
```
</details>

---

