---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-14 08:32:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 408 |
| Sample Rate | 6.80/sec |
| Health Score | 425% |
| Threads | 8 |
| Allocations | 331 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 8 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (2 unique values: 27-29 cores)</summary>

```
1791980541 29
1791980546 29
1791980551 29
1791980556 29
1791980561 29
1791980566 29
1791980571 29
1791980576 29
1791980581 29
1791980586 29
1791980591 29
1791980596 29
1791980601 29
1791980606 29
1791980611 29
1791980616 29
1791980621 27
1791980626 27
1791980631 27
1791980636 27
```
</details>

---

