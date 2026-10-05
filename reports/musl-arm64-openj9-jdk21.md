---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-05 05:22:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 9 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 11 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791191809 48
1791191814 48
1791191819 48
1791191824 48
1791191829 48
1791191834 48
1791191839 48
1791191844 48
1791191849 48
1791191854 48
1791191859 48
1791191864 48
1791191869 48
1791191874 48
1791191879 48
1791191884 48
1791191889 48
1791191894 48
1791191899 48
1791191904 43
```
</details>

---

