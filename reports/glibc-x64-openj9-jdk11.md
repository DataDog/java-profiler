---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-03-13 05:44:20 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 10 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (3 unique values: 60-64 cores)</summary>

```
1773394739 60
1773394744 60
1773394749 60
1773394754 60
1773394759 60
1773394764 60
1773394769 60
1773394774 60
1773394779 60
1773394784 62
1773394789 62
1773394794 62
1773394799 62
1773394804 62
1773394809 62
1773394814 62
1773394819 62
1773394824 62
1773394829 62
1773394834 62
```
</details>

---

