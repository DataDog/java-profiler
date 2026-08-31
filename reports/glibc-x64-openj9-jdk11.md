---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-31 00:49:30 EDT

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
| CPU Cores (start) | 17 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 8 |
| Allocations | 305 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 9 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (2 unique values: 15-17 cores)</summary>

```
1788151525 17
1788151530 17
1788151535 17
1788151540 17
1788151545 17
1788151550 17
1788151555 17
1788151560 17
1788151565 17
1788151570 15
1788151575 15
1788151580 15
1788151585 15
1788151590 15
1788151595 15
1788151600 15
1788151605 15
1788151610 17
1788151615 17
1788151620 17
```
</details>

---

