---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 17:22:57 EST

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 9 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (3 unique values: 25-75 cores)</summary>

```
1793830741 25
1793830746 25
1793830751 25
1793830756 25
1793830761 25
1793830766 25
1793830771 25
1793830776 25
1793830781 25
1793830786 25
1793830791 25
1793830796 42
1793830801 42
1793830806 42
1793830811 42
1793830816 42
1793830821 42
1793830826 42
1793830831 42
1793830836 75
```
</details>

---

