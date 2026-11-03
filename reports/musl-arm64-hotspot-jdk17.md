---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-03 06:24:35 EST

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
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 10 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 10 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793704767 48
1793704772 48
1793704777 48
1793704782 48
1793704787 48
1793704792 48
1793704797 48
1793704802 48
1793704807 48
1793704812 48
1793704817 48
1793704822 48
1793704827 48
1793704832 48
1793704837 48
1793704842 48
1793704847 48
1793704852 48
1793704857 48
1793704862 48
```
</details>

---

