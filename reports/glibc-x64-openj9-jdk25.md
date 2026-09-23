---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-23 10:27:22 EDT

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 427 |
| Sample Rate | 7.12/sec |
| Health Score | 445% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 12 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (2 unique values: 63-65 cores)</summary>

```
1790173336 65
1790173341 65
1790173346 65
1790173351 65
1790173356 65
1790173361 65
1790173366 63
1790173371 63
1790173376 63
1790173381 63
1790173386 63
1790173391 63
1790173396 63
1790173401 63
1790173406 63
1790173411 63
1790173416 65
1790173421 65
1790173426 65
1790173431 65
```
</details>

---

