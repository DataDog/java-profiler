---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-21 03:29:12 EDT

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 662 |
| Sample Rate | 11.03/sec |
| Health Score | 689% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 952 |
| Sample Rate | 15.87/sec |
| Health Score | 992% |
| Threads | 11 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (2 unique values: 84-96 cores)</summary>

```
1789975486 84
1789975491 84
1789975496 84
1789975501 84
1789975506 84
1789975511 84
1789975516 84
1789975521 84
1789975526 84
1789975531 84
1789975536 84
1789975541 84
1789975546 84
1789975551 84
1789975557 84
1789975562 84
1789975567 84
1789975572 96
1789975577 96
1789975582 96
```
</details>

---

