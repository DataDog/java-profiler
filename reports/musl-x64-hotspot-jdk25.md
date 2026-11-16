---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-16 12:07:00 EST

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
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
| Allocations | 544 |

<details>
<summary>CPU Timeline (3 unique values: 49-60 cores)</summary>

```
1794848449 58
1794848454 58
1794848459 58
1794848464 58
1794848469 58
1794848474 58
1794848479 58
1794848484 60
1794848489 60
1794848494 60
1794848499 60
1794848504 60
1794848509 60
1794848514 60
1794848519 49
1794848524 49
1794848529 49
1794848534 49
1794848539 49
1794848544 49
```
</details>

---

