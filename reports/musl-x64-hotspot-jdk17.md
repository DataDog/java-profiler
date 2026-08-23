---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-23 05:47:33 EDT

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
| CPU Cores (start) | 11 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 844 |
| Sample Rate | 14.07/sec |
| Health Score | 879% |
| Threads | 10 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (4 unique values: 11-51 cores)</summary>

```
1787478181 11
1787478186 11
1787478191 11
1787478196 11
1787478201 11
1787478206 11
1787478211 11
1787478216 31
1787478221 31
1787478226 51
1787478231 51
1787478236 51
1787478241 51
1787478246 51
1787478251 51
1787478256 51
1787478261 51
1787478266 51
1787478271 51
1787478276 51
```
</details>

---

