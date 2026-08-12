---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-12 05:48:00 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 9 |
| Allocations | 576 |

<details>
<summary>CPU Timeline (2 unique values: 47-49 cores)</summary>

```
1786527830 49
1786527835 49
1786527840 49
1786527845 49
1786527850 47
1786527855 47
1786527860 47
1786527865 47
1786527870 47
1786527875 47
1786527880 49
1786527885 49
1786527890 49
1786527895 49
1786527900 49
1786527905 49
1786527910 49
1786527915 49
1786527920 49
1786527925 49
```
</details>

---

