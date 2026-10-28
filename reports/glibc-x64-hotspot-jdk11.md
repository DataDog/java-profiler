---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-28 07:01:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 76 |
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
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 763 |
| Sample Rate | 12.72/sec |
| Health Score | 795% |
| Threads | 9 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (3 unique values: 74-81 cores)</summary>

```
1793184695 81
1793184700 81
1793184705 76
1793184710 76
1793184715 76
1793184720 76
1793184725 76
1793184730 76
1793184735 76
1793184740 76
1793184745 76
1793184750 76
1793184755 76
1793184760 76
1793184765 76
1793184770 76
1793184775 74
1793184780 74
1793184785 74
1793184790 74
```
</details>

---

