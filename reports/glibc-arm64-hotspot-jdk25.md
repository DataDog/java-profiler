---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 05:58:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 150 |
| Sample Rate | 2.50/sec |
| Health Score | 156% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 647 |
| Sample Rate | 10.78/sec |
| Health Score | 674% |
| Threads | 10 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (2 unique values: 51-53 cores)</summary>

```
1793789588 53
1793789593 53
1793789598 53
1793789603 53
1793789609 53
1793789614 53
1793789619 53
1793789624 53
1793789629 53
1793789634 53
1793789639 53
1793789644 53
1793789649 53
1793789654 53
1793789659 53
1793789664 53
1793789669 53
1793789674 53
1793789679 53
1793789684 51
```
</details>

---

