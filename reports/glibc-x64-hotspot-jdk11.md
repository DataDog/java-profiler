---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-31 00:49:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 10 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (2 unique values: 12-32 cores)</summary>

```
1788151525 12
1788151530 12
1788151535 12
1788151540 12
1788151545 32
1788151550 32
1788151555 32
1788151560 32
1788151565 32
1788151570 32
1788151575 32
1788151580 32
1788151585 32
1788151590 32
1788151595 32
1788151600 32
1788151605 32
1788151610 32
1788151615 32
1788151620 32
```
</details>

---

