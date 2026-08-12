---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-12 11:23:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 10 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 10 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (4 unique values: 80-96 cores)</summary>

```
1786547955 92
1786547960 92
1786547965 92
1786547970 92
1786547975 92
1786547980 92
1786547985 92
1786547990 92
1786547995 92
1786548000 92
1786548005 92
1786548010 94
1786548015 94
1786548020 94
1786548025 96
1786548030 96
1786548035 80
1786548040 80
1786548045 80
1786548050 80
```
</details>

---

