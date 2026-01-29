---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ❌ FAIL

**Date:** 2026-01-29 08:17:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 2.17/sec |
| Health Score | 136% |
| Threads | 7 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 8 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 6 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1769692423 24
1769692428 24
1769692433 24
1769692438 24
1769692443 24
1769692448 24
1769692453 24
1769692458 24
1769692463 24
1769692468 24
1769692473 24
1769692478 24
1769692484 24
1769692489 24
1769692494 24
1769692499 24
1769692504 24
1769692509 24
1769692514 24
1769692519 24
```
</details>

---

