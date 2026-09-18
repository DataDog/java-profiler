---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 03:38:52 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 9.90/sec |
| Health Score | 619% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 10 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (4 unique values: 77-80 cores)</summary>

```
1789716429 80
1789716434 80
1789716439 80
1789716444 80
1789716449 80
1789716454 80
1789716459 80
1789716464 78
1789716469 78
1789716474 78
1789716479 78
1789716484 79
1789716489 79
1789716494 79
1789716499 77
1789716504 77
1789716509 77
1789716514 77
1789716519 79
1789716524 79
```
</details>

---

