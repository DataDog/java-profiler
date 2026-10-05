---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-05 05:22:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 754 |
| Sample Rate | 12.57/sec |
| Health Score | 786% |
| Threads | 9 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (3 unique values: 48-58 cores)</summary>

```
1791191804 48
1791191809 48
1791191814 48
1791191819 48
1791191824 48
1791191829 48
1791191834 58
1791191839 58
1791191844 58
1791191849 58
1791191854 58
1791191859 58
1791191864 50
1791191869 50
1791191874 50
1791191879 50
1791191884 50
1791191889 50
1791191894 50
1791191899 50
```
</details>

---

