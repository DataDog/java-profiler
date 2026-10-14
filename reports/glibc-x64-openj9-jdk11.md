---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-14 01:04:00 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 8 |
| Allocations | 323 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 9 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (2 unique values: 40-42 cores)</summary>

```
1791953953 42
1791953958 42
1791953963 40
1791953968 40
1791953973 40
1791953978 40
1791953983 40
1791953988 40
1791953993 40
1791953998 40
1791954003 40
1791954008 40
1791954013 40
1791954018 40
1791954023 40
1791954028 40
1791954033 40
1791954038 40
1791954043 40
1791954048 40
```
</details>

---

