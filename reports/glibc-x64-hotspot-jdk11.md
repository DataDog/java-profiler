---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-07 10:58:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 724 |
| Sample Rate | 12.07/sec |
| Health Score | 754% |
| Threads | 9 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (7 unique values: 31-60 cores)</summary>

```
1778165581 36
1778165586 36
1778165591 38
1778165596 38
1778165601 38
1778165606 38
1778165611 38
1778165616 38
1778165621 31
1778165626 31
1778165631 31
1778165636 31
1778165641 31
1778165646 31
1778165651 31
1778165656 31
1778165661 35
1778165666 35
1778165671 37
1778165676 37
```
</details>

---

