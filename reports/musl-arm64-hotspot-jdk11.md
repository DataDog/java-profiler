---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-27 20:01:53 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 8 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 285 |
| Sample Rate | 4.75/sec |
| Health Score | 297% |
| Threads | 10 |
| Allocations | 141 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793145459 48
1793145464 48
1793145469 48
1793145474 48
1793145479 48
1793145484 48
1793145489 48
1793145494 48
1793145499 48
1793145504 48
1793145509 48
1793145514 48
1793145519 48
1793145524 48
1793145529 48
1793145534 48
1793145539 48
1793145544 48
1793145549 48
1793145554 48
```
</details>

---

