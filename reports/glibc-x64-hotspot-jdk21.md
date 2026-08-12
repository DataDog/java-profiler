---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-12 04:38:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 10 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (3 unique values: 50-60 cores)</summary>

```
1786523563 50
1786523568 50
1786523573 50
1786523578 50
1786523583 58
1786523588 58
1786523593 60
1786523598 60
1786523603 60
1786523608 60
1786523613 60
1786523618 60
1786523623 58
1786523628 58
1786523633 58
1786523638 58
1786523643 58
1786523648 58
1786523653 58
1786523658 60
```
</details>

---

