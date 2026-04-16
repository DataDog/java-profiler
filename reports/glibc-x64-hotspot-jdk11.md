---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-16 12:58:21 EDT

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 460 |
| Sample Rate | 7.67/sec |
| Health Score | 479% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 683 |
| Sample Rate | 11.38/sec |
| Health Score | 711% |
| Threads | 9 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (2 unique values: 37-42 cores)</summary>

```
1776358394 37
1776358399 37
1776358404 37
1776358409 37
1776358414 37
1776358419 37
1776358424 37
1776358429 37
1776358434 37
1776358439 42
1776358444 42
1776358449 42
1776358454 42
1776358459 42
1776358464 42
1776358469 42
1776358474 42
1776358479 42
1776358484 42
1776358489 42
```
</details>

---

