---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-05 05:22:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 872 |
| Sample Rate | 14.53/sec |
| Health Score | 908% |
| Threads | 10 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 24-32 cores)</summary>

```
1791191809 32
1791191814 32
1791191819 32
1791191824 32
1791191829 32
1791191834 32
1791191839 32
1791191844 32
1791191849 24
1791191854 24
1791191859 24
1791191864 24
1791191869 24
1791191874 24
1791191879 24
1791191884 24
1791191889 24
1791191894 24
1791191899 24
1791191904 24
```
</details>

---

