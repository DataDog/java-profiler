---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-29 12:24:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 10 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (4 unique values: 48-53 cores)</summary>

```
1777479449 51
1777479454 51
1777479459 51
1777479464 51
1777479469 51
1777479474 51
1777479479 51
1777479484 51
1777479489 51
1777479494 51
1777479499 50
1777479504 50
1777479509 50
1777479514 50
1777479519 50
1777479524 50
1777479529 50
1777479534 50
1777479539 50
1777479544 50
```
</details>

---

