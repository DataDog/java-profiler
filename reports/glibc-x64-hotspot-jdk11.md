---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 09:02:29 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 720 |
| Sample Rate | 12.00/sec |
| Health Score | 750% |
| Threads | 10 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (5 unique values: 68-92 cores)</summary>

```
1794405422 72
1794405427 72
1794405432 70
1794405437 70
1794405442 70
1794405447 68
1794405452 68
1794405457 68
1794405462 68
1794405467 68
1794405472 68
1794405477 68
1794405482 68
1794405487 90
1794405492 90
1794405497 90
1794405502 90
1794405507 92
1794405512 92
1794405517 92
```
</details>

---

