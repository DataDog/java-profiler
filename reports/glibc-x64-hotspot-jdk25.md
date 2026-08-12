---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-12 04:38:14 EDT

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 418 |
| Sample Rate | 6.97/sec |
| Health Score | 436% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 10 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (2 unique values: 56-68 cores)</summary>

```
1786523559 68
1786523564 68
1786523569 68
1786523574 68
1786523579 68
1786523584 68
1786523589 68
1786523594 68
1786523599 68
1786523604 68
1786523609 68
1786523614 68
1786523619 68
1786523624 68
1786523629 68
1786523634 56
1786523639 56
1786523644 56
1786523649 56
1786523654 56
```
</details>

---

