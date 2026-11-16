---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-15 19:49:11 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 8 |
| Allocations | 423 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 773 |
| Sample Rate | 12.88/sec |
| Health Score | 805% |
| Threads | 10 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (3 unique values: 84-94 cores)</summary>

```
1794789900 94
1794789905 94
1794789910 94
1794789915 86
1794789920 86
1794789925 84
1794789930 84
1794789935 84
1794789940 84
1794789945 84
1794789950 84
1794789955 84
1794789960 84
1794789965 84
1794789970 84
1794789975 84
1794789980 84
1794789985 84
1794789990 84
1794789995 84
```
</details>

---

