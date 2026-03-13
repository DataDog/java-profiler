---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-03-13 05:44:28 EDT

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 846 |
| Sample Rate | 14.10/sec |
| Health Score | 881% |
| Threads | 10 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (3 unique values: 66-68 cores)</summary>

```
1773394734 67
1773394739 67
1773394744 66
1773394749 66
1773394754 66
1773394759 66
1773394764 66
1773394769 68
1773394774 68
1773394779 68
1773394784 68
1773394789 68
1773394794 68
1773394799 68
1773394804 68
1773394809 68
1773394814 68
1773394819 68
1773394824 68
1773394829 68
```
</details>

---

