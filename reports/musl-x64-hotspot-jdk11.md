---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-07 10:54:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 837 |
| Sample Rate | 13.95/sec |
| Health Score | 872% |
| Threads | 10 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (3 unique values: 74-81 cores)</summary>

```
1778165406 81
1778165411 81
1778165416 81
1778165421 81
1778165426 81
1778165431 79
1778165436 79
1778165441 74
1778165446 74
1778165451 74
1778165456 74
1778165461 74
1778165466 74
1778165471 74
1778165476 74
1778165481 74
1778165486 74
1778165491 74
1778165496 74
1778165501 74
```
</details>

---

