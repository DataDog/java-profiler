---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-16 12:58:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 415 |
| Sample Rate | 6.92/sec |
| Health Score | 432% |
| Threads | 8 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 12.53/sec |
| Health Score | 783% |
| Threads | 10 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (4 unique values: 21-32 cores)</summary>

```
1776358394 26
1776358399 21
1776358404 21
1776358409 21
1776358414 21
1776358419 21
1776358424 21
1776358429 21
1776358434 26
1776358439 26
1776358444 26
1776358449 26
1776358454 26
1776358459 26
1776358464 26
1776358469 26
1776358474 30
1776358479 30
1776358484 32
1776358489 32
```
</details>

---

