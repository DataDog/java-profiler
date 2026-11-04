---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 13:32:32 EST

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 742 |
| Sample Rate | 12.37/sec |
| Health Score | 773% |
| Threads | 9 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (3 unique values: 73-77 cores)</summary>

```
1793816864 73
1793816869 75
1793816874 75
1793816879 75
1793816884 75
1793816889 73
1793816894 73
1793816899 73
1793816904 75
1793816909 75
1793816914 75
1793816919 75
1793816924 75
1793816929 75
1793816934 75
1793816939 75
1793816944 77
1793816949 77
1793816954 77
1793816959 77
```
</details>

---

