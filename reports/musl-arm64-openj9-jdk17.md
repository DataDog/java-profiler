---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-20 13:25:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 11 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 402 |
| Sample Rate | 6.70/sec |
| Health Score | 419% |
| Threads | 14 |
| Allocations | 138 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1787246474 40
1787246479 40
1787246484 40
1787246489 40
1787246494 40
1787246499 40
1787246504 40
1787246509 40
1787246514 40
1787246519 40
1787246524 40
1787246529 40
1787246534 40
1787246539 40
1787246544 40
1787246549 40
1787246554 40
1787246559 40
1787246564 40
1787246569 40
```
</details>

---

