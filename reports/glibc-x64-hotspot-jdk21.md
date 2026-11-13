---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 13:36:36 EST

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
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 9 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1794594725 30
1794594730 30
1794594735 30
1794594740 30
1794594745 32
1794594750 32
1794594755 32
1794594760 32
1794594765 32
1794594770 32
1794594775 32
1794594780 32
1794594785 32
1794594790 32
1794594795 32
1794594800 32
1794594805 32
1794594810 32
1794594815 30
1794594820 30
```
</details>

---

