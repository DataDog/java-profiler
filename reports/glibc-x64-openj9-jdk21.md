---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-03-13 05:44:20 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 11 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (3 unique values: 47-51 cores)</summary>

```
1773394724 50
1773394729 51
1773394734 51
1773394739 51
1773394744 51
1773394749 51
1773394754 51
1773394759 47
1773394764 47
1773394769 47
1773394774 47
1773394779 47
1773394784 47
1773394789 47
1773394794 47
1773394799 47
1773394804 47
1773394809 47
1773394814 47
1773394820 47
```
</details>

---

