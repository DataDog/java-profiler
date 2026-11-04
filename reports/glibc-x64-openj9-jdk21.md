---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-04 13:32:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 641 |
| Sample Rate | 10.68/sec |
| Health Score | 668% |
| Threads | 10 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (3 unique values: 57-61 cores)</summary>

```
1793816903 61
1793816908 57
1793816913 57
1793816918 57
1793816923 57
1793816928 57
1793816933 57
1793816938 57
1793816943 57
1793816948 57
1793816953 57
1793816958 57
1793816963 57
1793816968 57
1793816973 57
1793816978 57
1793816983 57
1793816988 57
1793816993 57
1793816998 59
```
</details>

---

