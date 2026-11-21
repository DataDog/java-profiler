---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-21 05:47:05 EST

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 8 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (3 unique values: 45-81 cores)</summary>

```
1795257752 45
1795257757 45
1795257762 62
1795257767 62
1795257772 62
1795257777 62
1795257782 62
1795257787 62
1795257792 62
1795257797 62
1795257802 62
1795257807 62
1795257812 62
1795257817 62
1795257822 81
1795257827 81
1795257832 81
1795257837 81
1795257842 81
1795257847 81
```
</details>

---

