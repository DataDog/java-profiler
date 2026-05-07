---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-07 06:49:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1012 |
| Sample Rate | 16.87/sec |
| Health Score | 1054% |
| Threads | 10 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (3 unique values: 88-92 cores)</summary>

```
1778150771 88
1778150776 88
1778150781 88
1778150786 88
1778150791 90
1778150796 90
1778150801 90
1778150806 92
1778150811 92
1778150816 92
1778150821 92
1778150826 92
1778150831 92
1778150836 92
1778150841 92
1778150846 92
1778150851 92
1778150856 92
1778150861 92
1778150866 88
```
</details>

---

