---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-05 13:29:24 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 388 |
| Sample Rate | 6.47/sec |
| Health Score | 404% |
| Threads | 8 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 11 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (2 unique values: 27-29 cores)</summary>

```
1772734988 29
1772734993 29
1772734998 29
1772735003 29
1772735008 29
1772735013 29
1772735018 29
1772735023 29
1772735028 29
1772735033 29
1772735038 29
1772735043 29
1772735048 29
1772735053 29
1772735058 29
1772735063 29
1772735068 27
1772735074 27
1772735079 27
1772735084 27
```
</details>

---

