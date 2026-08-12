---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-12 00:57:47 EDT

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 8 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (2 unique values: 16-18 cores)</summary>

```
1786510444 18
1786510449 18
1786510454 18
1786510459 18
1786510464 18
1786510469 16
1786510474 16
1786510479 16
1786510484 16
1786510489 16
1786510494 16
1786510499 16
1786510504 16
1786510510 16
1786510515 16
1786510520 18
1786510525 18
1786510530 18
1786510535 18
1786510540 18
```
</details>

---

