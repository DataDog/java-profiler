---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-05 13:29:24 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 406 |
| Sample Rate | 6.77/sec |
| Health Score | 423% |
| Threads | 10 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 12 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (4 unique values: 49-86 cores)</summary>

```
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
1772735073 84
1772735078 84
1772735083 84
1772735088 84
1772735093 84
```
</details>

---

