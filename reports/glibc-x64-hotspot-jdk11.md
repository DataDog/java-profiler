---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 18:03:50 EST

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
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 814 |
| Sample Rate | 13.57/sec |
| Health Score | 848% |
| Threads | 10 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (4 unique values: 67-84 cores)</summary>

```
1794524340 81
1794524345 81
1794524350 84
1794524355 84
1794524360 84
1794524365 84
1794524370 84
1794524375 84
1794524380 84
1794524385 84
1794524390 84
1794524395 84
1794524400 84
1794524405 84
1794524410 84
1794524415 84
1794524420 84
1794524425 84
1794524430 67
1794524435 67
```
</details>

---

