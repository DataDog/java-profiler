---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-27 07:00:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 188 |
| Sample Rate | 3.13/sec |
| Health Score | 196% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 51-56 cores)</summary>

```
1793098429 51
1793098434 56
1793098439 56
1793098444 56
1793098449 56
1793098454 56
1793098459 56
1793098464 56
1793098469 56
1793098474 56
1793098479 56
1793098484 56
1793098489 56
1793098494 56
1793098499 56
1793098504 56
1793098509 56
1793098514 56
1793098519 56
1793098524 56
```
</details>

---

