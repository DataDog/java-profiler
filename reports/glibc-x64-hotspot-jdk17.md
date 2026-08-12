---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-12 04:38:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 10 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 794 |
| Sample Rate | 13.23/sec |
| Health Score | 827% |
| Threads | 11 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (5 unique values: 43-91 cores)</summary>

```
1786523579 87
1786523584 87
1786523589 89
1786523594 89
1786523599 91
1786523604 91
1786523609 91
1786523614 91
1786523619 55
1786523624 55
1786523629 55
1786523634 55
1786523639 43
1786523644 43
1786523649 43
1786523654 43
1786523659 43
1786523664 43
1786523669 43
1786523674 43
```
</details>

---

