---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-23 10:27:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 174 |
| Sample Rate | 2.90/sec |
| Health Score | 181% |
| Threads | 10 |
| Allocations | 161 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 12 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (3 unique values: 44-48 cores)</summary>

```
1790173280 46
1790173285 44
1790173290 44
1790173296 44
1790173301 44
1790173306 44
1790173311 44
1790173316 44
1790173321 44
1790173326 44
1790173331 44
1790173336 46
1790173341 46
1790173346 46
1790173351 46
1790173356 46
1790173361 46
1790173366 46
1790173371 48
1790173376 48
```
</details>

---

