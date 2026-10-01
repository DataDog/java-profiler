---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-01 08:19:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 11 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (5 unique values: 52-57 cores)</summary>

```
1790856910 54
1790856915 54
1790856920 54
1790856925 54
1790856930 52
1790856935 52
1790856940 54
1790856945 54
1790856950 54
1790856955 54
1790856960 54
1790856965 54
1790856970 54
1790856975 54
1790856980 54
1790856985 56
1790856990 56
1790856995 53
1790857000 53
1790857005 57
```
</details>

---

