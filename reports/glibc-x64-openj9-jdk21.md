---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-28 07:12:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 9 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (2 unique values: 16-18 cores)</summary>

```
1793185693 16
1793185698 16
1793185703 16
1793185708 16
1793185713 16
1793185718 16
1793185723 16
1793185728 16
1793185733 18
1793185738 18
1793185743 18
1793185748 18
1793185753 18
1793185758 18
1793185763 18
1793185768 18
1793185773 18
1793185778 18
1793185783 18
1793185788 18
```
</details>

---

