---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-03 14:44:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 454 |
| Sample Rate | 7.57/sec |
| Health Score | 473% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 10 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1793734765 30
1793734770 30
1793734775 30
1793734780 30
1793734785 30
1793734790 32
1793734795 32
1793734800 32
1793734805 32
1793734810 32
1793734815 32
1793734820 32
1793734825 30
1793734830 30
1793734835 30
1793734840 30
1793734845 30
1793734850 30
1793734855 30
1793734860 30
```
</details>

---

