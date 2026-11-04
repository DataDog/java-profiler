---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 13:32:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 390 |
| Sample Rate | 6.50/sec |
| Health Score | 406% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 10 |
| Allocations | 580 |

<details>
<summary>CPU Timeline (3 unique values: 55-59 cores)</summary>

```
1793816898 57
1793816903 57
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
1793816958 59
1793816963 59
1793816968 57
1793816973 57
1793816978 57
1793816983 55
1793816988 55
1793816993 55
```
</details>

---

