---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-16 12:58:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 463 |
| Sample Rate | 7.72/sec |
| Health Score | 482% |
| Threads | 8 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 773 |
| Sample Rate | 12.88/sec |
| Health Score | 805% |
| Threads | 9 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (3 unique values: 24-29 cores)</summary>

```
1776358404 25
1776358409 25
1776358414 25
1776358419 25
1776358424 25
1776358429 25
1776358434 25
1776358439 25
1776358444 25
1776358449 25
1776358454 25
1776358459 25
1776358464 29
1776358469 29
1776358474 29
1776358479 29
1776358484 24
1776358489 24
1776358494 24
1776358499 24
```
</details>

---

