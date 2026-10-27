---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-27 07:00:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 9 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 9 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (3 unique values: 9-48 cores)</summary>

```
1793098436 9
1793098441 9
1793098446 9
1793098451 9
1793098456 9
1793098461 9
1793098466 9
1793098471 9
1793098476 9
1793098481 9
1793098486 9
1793098491 9
1793098496 9
1793098501 14
1793098506 14
1793098511 48
1793098516 48
1793098521 48
1793098526 48
1793098531 48
```
</details>

---

