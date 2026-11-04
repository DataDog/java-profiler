---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-04 13:32:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 11 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (7 unique values: 61-84 cores)</summary>

```
1793816885 84
1793816890 84
1793816895 84
1793816900 82
1793816905 82
1793816910 82
1793816915 82
1793816920 76
1793816925 76
1793816930 74
1793816935 74
1793816940 74
1793816945 72
1793816950 72
1793816955 72
1793816960 72
1793816965 72
1793816970 72
1793816975 61
1793816980 61
```
</details>

---

