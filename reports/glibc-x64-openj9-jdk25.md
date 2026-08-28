---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-28 12:57:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 10 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (4 unique values: 60-88 cores)</summary>

```
1787936065 88
1787936070 88
1787936075 88
1787936080 88
1787936085 88
1787936090 88
1787936095 88
1787936100 88
1787936105 88
1787936110 88
1787936115 88
1787936120 88
1787936125 68
1787936130 68
1787936135 68
1787936140 68
1787936145 68
1787936150 68
1787936155 68
1787936160 76
```
</details>

---

