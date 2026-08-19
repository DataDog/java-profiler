---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-19 11:10:58 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 11 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1787151524 48
1787151529 48
1787151534 48
1787151539 48
1787151544 48
1787151549 48
1787151554 48
1787151559 48
1787151564 48
1787151569 48
1787151574 48
1787151579 48
1787151584 48
1787151589 48
1787151594 48
1787151599 48
1787151604 48
1787151609 48
1787151614 43
1787151619 43
```
</details>

---

