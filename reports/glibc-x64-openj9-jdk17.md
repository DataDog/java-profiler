---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 09:06:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 9 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (2 unique values: 25-27 cores)</summary>

```
1795010479 25
1795010484 25
1795010489 25
1795010494 25
1795010499 25
1795010504 25
1795010509 25
1795010514 25
1795010519 25
1795010524 27
1795010529 27
1795010534 27
1795010539 27
1795010544 27
1795010549 27
1795010554 27
1795010559 27
1795010564 27
1795010569 27
1795010574 27
```
</details>

---

