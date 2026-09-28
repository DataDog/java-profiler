---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-28 10:34:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 9 |
| Allocations | 331 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 11 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (5 unique values: 68-79 cores)</summary>

```
1790605746 70
1790605751 70
1790605756 70
1790605761 70
1790605766 70
1790605771 70
1790605776 70
1790605781 70
1790605786 70
1790605791 70
1790605796 70
1790605801 70
1790605806 68
1790605811 68
1790605816 77
1790605821 77
1790605826 72
1790605831 72
1790605836 72
1790605841 72
```
</details>

---

