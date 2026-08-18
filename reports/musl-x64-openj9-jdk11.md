---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-18 10:51:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 9 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 882 |
| Sample Rate | 14.70/sec |
| Health Score | 919% |
| Threads | 10 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (3 unique values: 72-92 cores)</summary>

```
1787064350 72
1787064355 72
1787064360 72
1787064365 72
1787064370 92
1787064375 92
1787064380 92
1787064385 72
1787064390 72
1787064395 72
1787064400 72
1787064405 72
1787064410 72
1787064415 72
1787064420 72
1787064425 72
1787064430 72
1787064435 74
1787064440 74
1787064445 74
```
</details>

---

