---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-12 08:46:05 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 11 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (5 unique values: 74-83 cores)</summary>

```
1786538576 79
1786538581 79
1786538586 79
1786538591 79
1786538596 79
1786538601 74
1786538606 74
1786538611 74
1786538616 76
1786538621 76
1786538626 76
1786538631 76
1786538636 78
1786538641 78
1786538646 78
1786538651 78
1786538656 78
1786538661 78
1786538666 78
1786538671 78
```
</details>

---

