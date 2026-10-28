---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-28 07:12:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 411 |
| Sample Rate | 6.85/sec |
| Health Score | 428% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 10 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (4 unique values: 31-42 cores)</summary>

```
1793185716 33
1793185721 33
1793185726 33
1793185731 33
1793185736 33
1793185741 33
1793185746 33
1793185751 33
1793185756 33
1793185761 33
1793185766 33
1793185771 33
1793185776 31
1793185781 31
1793185786 31
1793185791 31
1793185796 33
1793185801 33
1793185806 40
1793185811 40
```
</details>

---

