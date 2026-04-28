---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-28 11:22:31 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 11 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (5 unique values: 43-84 cores)</summary>

```
1777389450 44
1777389455 44
1777389460 44
1777389465 44
1777389470 44
1777389475 44
1777389480 44
1777389485 44
1777389490 43
1777389495 43
1777389500 77
1777389505 77
1777389510 77
1777389515 77
1777389520 77
1777389525 77
1777389530 77
1777389535 77
1777389540 80
1777389545 80
```
</details>

---

