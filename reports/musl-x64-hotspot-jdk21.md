---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-27 00:56:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 9 |
| Allocations | 325 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 9 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1787806330 79
1787806335 79
1787806340 79
1787806345 79
1787806350 79
1787806355 79
1787806360 79
1787806365 79
1787806370 79
1787806375 79
1787806380 81
1787806385 81
1787806390 81
1787806395 81
1787806400 81
1787806405 81
1787806410 81
1787806415 81
1787806420 81
1787806425 81
```
</details>

---

