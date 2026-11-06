---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-06 16:49:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 13 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (3 unique values: 25-29 cores)</summary>

```
1794001479 25
1794001484 25
1794001489 27
1794001494 27
1794001499 27
1794001504 27
1794001509 29
1794001514 29
1794001519 27
1794001524 27
1794001529 27
1794001534 27
1794001539 27
1794001544 27
1794001549 27
1794001554 27
1794001559 27
1794001564 27
1794001569 27
1794001574 27
```
</details>

---

