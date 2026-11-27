---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 10:38:58 EST

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 6 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (2 unique values: 23-28 cores)</summary>

```
1795793685 23
1795793690 23
1795793695 28
1795793700 28
1795793705 28
1795793710 28
1795793715 28
1795793720 28
1795793725 28
1795793730 28
1795793735 28
1795793740 28
1795793745 28
1795793750 28
1795793755 28
1795793760 28
1795793765 28
1795793770 28
1795793775 28
1795793780 28
```
</details>

---

