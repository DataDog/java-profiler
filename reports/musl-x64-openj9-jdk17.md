---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-13 05:44:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 879 |
| Sample Rate | 14.65/sec |
| Health Score | 916% |
| Threads | 11 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (3 unique values: 24-42 cores)</summary>

```
1773394734 24
1773394739 24
1773394744 33
1773394749 33
1773394754 33
1773394759 42
1773394764 42
1773394769 42
1773394774 42
1773394779 42
1773394784 42
1773394789 42
1773394794 42
1773394799 42
1773394804 42
1773394809 42
1773394814 42
1773394819 42
1773394824 42
1773394829 42
```
</details>

---

