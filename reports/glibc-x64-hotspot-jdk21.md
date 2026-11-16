---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-16 05:57:36 EST

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 845 |
| Sample Rate | 14.08/sec |
| Health Score | 880% |
| Threads | 10 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (4 unique values: 71-93 cores)</summary>

```
1794826428 71
1794826433 91
1794826438 91
1794826443 91
1794826448 91
1794826453 91
1794826458 91
1794826463 91
1794826468 91
1794826473 91
1794826478 93
1794826483 93
1794826488 76
1794826493 76
1794826498 76
1794826503 76
1794826508 76
1794826513 76
1794826518 76
1794826523 76
```
</details>

---

