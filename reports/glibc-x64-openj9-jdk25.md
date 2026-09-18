---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 03:31:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 10 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 10 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (5 unique values: 86-96 cores)</summary>

```
1789716399 86
1789716404 86
1789716409 95
1789716414 95
1789716419 95
1789716424 95
1789716429 95
1789716434 95
1789716439 95
1789716444 95
1789716449 95
1789716454 95
1789716459 95
1789716464 95
1789716469 95
1789716474 95
1789716479 95
1789716484 96
1789716489 96
1789716494 96
```
</details>

---

