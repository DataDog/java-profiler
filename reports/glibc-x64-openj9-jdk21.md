---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-16 05:57:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
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
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 843 |
| Sample Rate | 14.05/sec |
| Health Score | 878% |
| Threads | 11 |
| Allocations | 449 |

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
1794826473 93
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

