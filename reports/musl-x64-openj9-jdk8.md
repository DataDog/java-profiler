---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-18 03:34:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 233 |
| Sample Rate | 3.88/sec |
| Health Score | 242% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 338 |
| Sample Rate | 5.63/sec |
| Health Score | 352% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 41-61 cores)</summary>

```
1789716444 61
1789716449 61
1789716454 61
1789716459 61
1789716464 61
1789716469 61
1789716474 61
1789716479 61
1789716484 41
1789716489 41
1789716494 41
1789716499 41
1789716504 41
1789716509 41
1789716514 41
1789716519 41
1789716524 41
1789716529 41
1789716534 41
1789716539 41
```
</details>

---

