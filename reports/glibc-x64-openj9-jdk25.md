---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-02 14:28:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 11 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1793647454 64
1793647459 64
1793647464 64
1793647469 64
1793647474 64
1793647479 64
1793647484 64
1793647489 64
1793647494 64
1793647499 66
1793647504 66
1793647509 66
1793647514 66
1793647519 66
1793647524 66
1793647529 66
1793647534 66
1793647539 66
1793647544 64
1793647549 64
```
</details>

---

