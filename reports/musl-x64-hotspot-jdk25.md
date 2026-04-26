---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-26 16:34:20 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 401 |
| Sample Rate | 6.68/sec |
| Health Score | 418% |
| Threads | 9 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 9.90/sec |
| Health Score | 619% |
| Threads | 10 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (4 unique values: 54-62 cores)</summary>

```
1777235399 62
1777235404 62
1777235409 62
1777235414 60
1777235419 60
1777235424 60
1777235429 60
1777235434 60
1777235439 60
1777235444 60
1777235449 62
1777235454 62
1777235459 62
1777235464 62
1777235469 57
1777235474 57
1777235479 54
1777235484 54
1777235489 54
1777235494 54
```
</details>

---

