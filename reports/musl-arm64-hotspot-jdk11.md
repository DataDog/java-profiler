---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-11 01:02:45 EDT

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 9 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 14 |
| Allocations | 126 |

<details>
<summary>CPU Timeline (2 unique values: 16-18 cores)</summary>

```
1791694705 18
1791694710 18
1791694715 18
1791694720 16
1791694725 16
1791694730 16
1791694735 16
1791694740 16
1791694745 16
1791694750 16
1791694755 16
1791694760 16
1791694765 16
1791694770 18
1791694775 18
1791694780 18
1791694785 18
1791694790 18
1791694795 18
1791694800 18
```
</details>

---

