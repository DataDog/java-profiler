---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-23 05:54:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 437 |
| Sample Rate | 7.28/sec |
| Health Score | 455% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 222 |
| Sample Rate | 3.70/sec |
| Health Score | 231% |
| Threads | 13 |
| Allocations | 128 |

<details>
<summary>CPU Timeline (4 unique values: 41-46 cores)</summary>

```
1790156710 46
1790156715 46
1790156720 44
1790156725 44
1790156730 43
1790156735 43
1790156740 43
1790156745 43
1790156750 43
1790156755 43
1790156760 44
1790156765 44
1790156770 43
1790156775 43
1790156780 43
1790156785 43
1790156790 43
1790156795 43
1790156800 43
1790156805 43
```
</details>

---

