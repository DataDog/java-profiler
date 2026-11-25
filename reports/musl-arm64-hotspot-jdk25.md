---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 16:21:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 9 |
| Allocations | 37 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 11 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (2 unique values: 17-18 cores)</summary>

```
1795641295 18
1795641300 18
1795641305 17
1795641310 17
1795641315 17
1795641320 17
1795641325 17
1795641330 17
1795641335 17
1795641340 17
1795641345 17
1795641350 17
1795641355 18
1795641360 18
1795641365 18
1795641370 18
1795641375 18
1795641380 18
1795641385 18
1795641390 18
```
</details>

---

