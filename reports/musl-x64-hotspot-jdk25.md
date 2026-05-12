---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-12 06:43:00 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 10 |
| Allocations | 429 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 11 |
| Allocations | 562 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1778582315 61
1778582320 61
1778582325 61
1778582330 61
1778582335 61
1778582340 61
1778582345 61
1778582350 61
1778582355 61
1778582360 61
1778582365 61
1778582370 61
1778582375 61
1778582380 61
1778582385 59
1778582390 59
1778582395 59
1778582400 59
1778582405 59
1778582410 59
```
</details>

---

