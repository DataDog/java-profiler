---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-05 05:22:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 201 |
| Sample Rate | 3.35/sec |
| Health Score | 209% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 269 |
| Sample Rate | 4.48/sec |
| Health Score | 280% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 58-74 cores)</summary>

```
1791191824 74
1791191829 74
1791191834 74
1791191839 74
1791191844 74
1791191849 66
1791191854 66
1791191859 66
1791191864 66
1791191869 66
1791191874 66
1791191879 66
1791191884 66
1791191889 58
1791191894 58
1791191899 58
1791191904 58
1791191909 58
1791191914 58
1791191919 58
```
</details>

---

