---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 11:01:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 890 |
| Sample Rate | 14.83/sec |
| Health Score | 927% |
| Threads | 10 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (5 unique values: 49-88 cores)</summary>

```
1789743365 49
1789743370 56
1789743375 56
1789743380 56
1789743385 56
1789743391 56
1789743396 56
1789743401 56
1789743406 56
1789743411 56
1789743416 56
1789743421 56
1789743426 56
1789743431 56
1789743436 56
1789743441 84
1789743446 84
1789743451 84
1789743456 84
1789743461 84
```
</details>

---

