---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-14 04:32:38 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 8 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 727 |
| Sample Rate | 12.12/sec |
| Health Score | 757% |
| Threads | 10 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (2 unique values: 61-63 cores)</summary>

```
1791966416 61
1791966421 61
1791966426 61
1791966431 61
1791966436 61
1791966441 61
1791966446 63
1791966451 63
1791966456 63
1791966461 63
1791966466 63
1791966471 63
1791966476 63
1791966481 63
1791966486 63
1791966491 63
1791966496 63
1791966501 63
1791966506 63
1791966511 63
```
</details>

---

