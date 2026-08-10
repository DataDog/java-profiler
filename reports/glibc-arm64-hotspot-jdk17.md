---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-10 06:10:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 7 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (2 unique values: 39-51 cores)</summary>

```
1786356305 39
1786356310 39
1786356315 51
1786356320 51
1786356325 51
1786356330 51
1786356335 51
1786356340 51
1786356345 51
1786356350 51
1786356355 51
1786356360 51
1786356365 51
1786356370 51
1786356375 51
1786356380 51
1786356385 51
1786356390 51
1786356395 51
1786356400 51
```
</details>

---

