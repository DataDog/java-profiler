---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-28 10:16:37 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 10 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (3 unique values: 79-96 cores)</summary>

```
1790604731 79
1790604736 91
1790604741 91
1790604746 91
1790604751 91
1790604756 91
1790604761 91
1790604766 91
1790604771 91
1790604776 91
1790604781 91
1790604786 91
1790604791 91
1790604796 91
1790604801 96
1790604806 96
1790604811 96
1790604816 96
1790604821 96
1790604826 96
```
</details>

---

