---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 14:28:39 EST

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 746 |
| Sample Rate | 12.43/sec |
| Health Score | 777% |
| Threads | 9 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (3 unique values: 58-62 cores)</summary>

```
1793647439 62
1793647444 62
1793647449 62
1793647454 62
1793647459 62
1793647464 62
1793647469 62
1793647474 62
1793647479 60
1793647484 60
1793647489 60
1793647494 60
1793647499 60
1793647504 60
1793647509 60
1793647514 60
1793647519 60
1793647524 60
1793647529 60
1793647534 60
```
</details>

---

