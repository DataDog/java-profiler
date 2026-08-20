---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-20 13:25:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 13 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1787246453 29
1787246459 29
1787246464 29
1787246469 34
1787246474 34
1787246479 34
1787246484 34
1787246489 34
1787246494 34
1787246499 34
1787246504 34
1787246509 34
1787246514 34
1787246519 34
1787246524 34
1787246529 34
1787246534 34
1787246539 34
1787246544 34
1787246549 34
```
</details>

---

