---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-27 10:39:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
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
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 7 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (2 unique values: 23-28 cores)</summary>

```
1795793675 23
1795793680 23
1795793685 23
1795793690 23
1795793695 23
1795793700 23
1795793705 23
1795793710 23
1795793715 23
1795793720 23
1795793725 23
1795793730 23
1795793735 23
1795793740 23
1795793745 23
1795793750 23
1795793755 28
1795793760 28
1795793765 28
1795793770 28
```
</details>

---

