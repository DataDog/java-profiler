---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-05 06:30:01 EDT

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 440 |
| Sample Rate | 7.33/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (4 unique values: 65-76 cores)</summary>

```
1777976731 73
1777976736 73
1777976741 73
1777976746 73
1777976751 73
1777976756 73
1777976761 73
1777976766 73
1777976771 73
1777976776 73
1777976781 73
1777976786 73
1777976791 73
1777976796 65
1777976801 65
1777976806 65
1777976811 71
1777976816 71
1777976821 71
1777976826 71
```
</details>

---

