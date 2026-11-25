---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 03:20:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 412 |
| Sample Rate | 6.87/sec |
| Health Score | 429% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 11 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (4 unique values: 51-65 cores)</summary>

```
1795594570 51
1795594575 51
1795594580 51
1795594585 51
1795594590 51
1795594595 53
1795594600 53
1795594605 55
1795594610 55
1795594615 55
1795594620 55
1795594625 55
1795594630 55
1795594635 55
1795594640 55
1795594645 65
1795594650 65
1795594655 65
1795594660 65
1795594665 65
```
</details>

---

