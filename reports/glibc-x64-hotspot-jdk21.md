---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 09:22:00 EST

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 9 |
| Allocations | 316 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 654 |
| Sample Rate | 10.90/sec |
| Health Score | 681% |
| Threads | 10 |
| Allocations | 432 |

<details>
<summary>CPU Timeline (4 unique values: 79-92 cores)</summary>

```
1794579380 92
1794579385 92
1794579390 92
1794579395 90
1794579400 90
1794579405 90
1794579410 90
1794579415 90
1794579420 90
1794579425 90
1794579430 90
1794579435 90
1794579440 81
1794579445 81
1794579450 81
1794579455 81
1794579460 81
1794579465 81
1794579470 81
1794579475 79
```
</details>

---

