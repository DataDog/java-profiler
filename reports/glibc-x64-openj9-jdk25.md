---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-03 05:16:46 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 670 |
| Sample Rate | 11.17/sec |
| Health Score | 698% |
| Threads | 9 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (3 unique values: 14-32 cores)</summary>

```
1770113275 32
1770113280 32
1770113285 32
1770113290 32
1770113295 32
1770113300 32
1770113305 32
1770113310 32
1770113315 32
1770113320 32
1770113325 32
1770113330 32
1770113335 32
1770113340 32
1770113345 32
1770113350 32
1770113355 32
1770113360 23
1770113366 23
1770113371 23
```
</details>

---

