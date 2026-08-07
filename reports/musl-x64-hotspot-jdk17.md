---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-07 07:56:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 10 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 697 |
| Sample Rate | 11.62/sec |
| Health Score | 726% |
| Threads | 11 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (2 unique values: 64-67 cores)</summary>

```
1786103476 64
1786103481 64
1786103486 64
1786103491 64
1786103496 64
1786103501 64
1786103506 64
1786103511 64
1786103516 64
1786103521 64
1786103526 64
1786103531 64
1786103536 64
1786103541 64
1786103546 64
1786103551 67
1786103556 67
1786103561 67
1786103566 67
1786103571 67
```
</details>

---

