---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-30 10:20:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 13 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (4 unique values: 44-50 cores)</summary>

```
1790777746 50
1790777751 50
1790777756 50
1790777761 50
1790777766 50
1790777771 50
1790777776 48
1790777781 48
1790777786 48
1790777791 49
1790777796 49
1790777801 44
1790777806 44
1790777811 44
1790777816 44
1790777821 44
1790777826 44
1790777831 44
1790777836 44
1790777841 44
```
</details>

---

