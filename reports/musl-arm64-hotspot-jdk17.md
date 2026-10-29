---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-29 11:32:08 EDT

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
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 654 |
| Sample Rate | 10.90/sec |
| Health Score | 681% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 11 |
| Allocations | 77 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1793287607 48
1793287612 48
1793287617 48
1793287622 48
1793287627 48
1793287632 48
1793287637 46
1793287642 46
1793287647 46
1793287653 46
1793287658 46
1793287663 46
1793287668 46
1793287673 46
1793287678 48
1793287683 48
1793287688 48
1793287693 48
1793287698 48
1793287703 48
```
</details>

---

