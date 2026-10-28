---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-27 20:01:54 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 8 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 10 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (3 unique values: 46-49 cores)</summary>

```
1793145450 46
1793145455 46
1793145460 49
1793145465 49
1793145470 49
1793145475 49
1793145480 49
1793145485 49
1793145490 49
1793145495 49
1793145500 49
1793145505 49
1793145510 49
1793145515 49
1793145520 49
1793145525 49
1793145530 49
1793145535 49
1793145540 49
1793145545 49
```
</details>

---

