---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-14 13:09:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 677 |
| Sample Rate | 11.28/sec |
| Health Score | 705% |
| Threads | 10 |
| Allocations | 436 |

<details>
<summary>CPU Timeline (3 unique values: 33-51 cores)</summary>

```
1794679404 51
1794679409 51
1794679414 51
1794679419 51
1794679424 51
1794679429 51
1794679434 42
1794679439 42
1794679444 42
1794679449 42
1794679454 33
1794679459 33
1794679464 33
1794679469 33
1794679474 33
1794679479 33
1794679484 33
1794679489 33
1794679494 33
1794679499 33
```
</details>

---

