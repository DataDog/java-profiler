---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-17 09:18:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 12 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1786972424 32
1786972429 32
1786972434 32
1786972439 32
1786972444 32
1786972449 27
1786972454 27
1786972459 27
1786972464 27
1786972469 27
1786972474 27
1786972479 27
1786972484 27
1786972489 27
1786972494 27
1786972499 27
1786972504 27
1786972509 27
1786972514 27
1786972519 27
```
</details>

---

