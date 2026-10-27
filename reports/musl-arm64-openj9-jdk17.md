---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-27 07:00:17 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 772 |
| Sample Rate | 12.87/sec |
| Health Score | 804% |
| Threads | 11 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1793098435 64
1793098440 64
1793098446 64
1793098451 64
1793098456 64
1793098461 64
1793098466 64
1793098471 64
1793098476 59
1793098481 59
1793098486 59
1793098491 59
1793098496 59
1793098501 59
1793098506 59
1793098511 59
1793098516 59
1793098521 59
1793098526 59
1793098531 59
```
</details>

---

