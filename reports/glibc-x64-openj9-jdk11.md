---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-15 14:28:18 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 8 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 9 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (2 unique values: 29-31 cores)</summary>

```
1776277377 31
1776277382 31
1776277387 31
1776277392 31
1776277397 31
1776277402 29
1776277407 29
1776277412 29
1776277417 29
1776277422 29
1776277427 29
1776277432 31
1776277437 31
1776277442 31
1776277447 31
1776277452 31
1776277457 31
1776277462 31
1776277467 31
1776277472 31
```
</details>

---

