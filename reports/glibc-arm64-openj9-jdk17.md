---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 05:28:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 354 |
| Sample Rate | 5.90/sec |
| Health Score | 369% |
| Threads | 13 |
| Allocations | 156 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794392637 48
1794392642 48
1794392647 43
1794392652 43
1794392657 43
1794392662 43
1794392667 43
1794392672 43
1794392677 43
1794392682 43
1794392687 43
1794392692 43
1794392697 43
1794392702 43
1794392707 43
1794392712 43
1794392717 43
1794392722 43
1794392727 43
1794392732 43
```
</details>

---

