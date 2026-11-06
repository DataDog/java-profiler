---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-06 16:49:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 670 |
| Sample Rate | 11.17/sec |
| Health Score | 698% |
| Threads | 10 |
| Allocations | 426 |

<details>
<summary>CPU Timeline (2 unique values: 76-78 cores)</summary>

```
1794001464 76
1794001469 76
1794001474 76
1794001479 78
1794001484 78
1794001489 78
1794001494 78
1794001499 78
1794001504 78
1794001509 78
1794001514 78
1794001519 78
1794001524 78
1794001529 78
1794001534 78
1794001539 78
1794001544 78
1794001549 78
1794001554 78
1794001559 78
```
</details>

---

