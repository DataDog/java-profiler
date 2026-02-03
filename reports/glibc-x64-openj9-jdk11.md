---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-03 05:16:46 EST

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 759 |
| Sample Rate | 12.65/sec |
| Health Score | 791% |
| Threads | 9 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (2 unique values: 23-32 cores)</summary>

```
1770113281 23
1770113286 23
1770113291 23
1770113296 23
1770113301 32
1770113306 32
1770113311 32
1770113316 32
1770113321 32
1770113326 32
1770113331 32
1770113336 32
1770113341 32
1770113346 32
1770113351 32
1770113356 32
1770113361 32
1770113366 32
1770113371 32
1770113376 32
```
</details>

---

