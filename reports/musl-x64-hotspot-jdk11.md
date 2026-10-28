---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-28 07:43:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 9.83/sec |
| Health Score | 614% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 9 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (3 unique values: 48-53 cores)</summary>

```
1793187387 48
1793187392 51
1793187397 51
1793187402 53
1793187407 53
1793187412 53
1793187417 53
1793187422 53
1793187427 53
1793187432 53
1793187437 53
1793187442 53
1793187447 53
1793187452 53
1793187457 53
1793187462 53
1793187467 53
1793187472 53
1793187477 53
1793187482 53
```
</details>

---

