---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 06:36:49 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 382 |
| Sample Rate | 6.37/sec |
| Health Score | 398% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 11 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (2 unique values: 47-51 cores)</summary>

```
1794569574 47
1794569579 47
1794569584 47
1794569589 47
1794569594 47
1794569599 47
1794569604 47
1794569609 47
1794569614 51
1794569619 51
1794569624 51
1794569629 51
1794569634 51
1794569639 51
1794569644 51
1794569649 51
1794569654 51
1794569659 51
1794569664 51
1794569669 51
```
</details>

---

