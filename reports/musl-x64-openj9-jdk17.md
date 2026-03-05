---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-05 13:29:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 9 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 10 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (4 unique values: 49-86 cores)</summary>

```
1772734973 56
1772734978 56
1772734983 56
1772734988 56
1772734993 56
1772734998 56
1772735003 56
1772735008 56
1772735013 56
1772735018 49
1772735023 49
1772735028 84
1772735033 84
1772735038 84
1772735043 84
1772735048 84
1772735053 84
1772735058 84
1772735063 86
1772735068 86
```
</details>

---

