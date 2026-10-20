---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-20 13:18:14 EDT

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 669 |
| Sample Rate | 11.15/sec |
| Health Score | 697% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 882 |
| Sample Rate | 14.70/sec |
| Health Score | 919% |
| Threads | 10 |
| Allocations | 545 |

<details>
<summary>CPU Timeline (4 unique values: 75-82 cores)</summary>

```
1792516358 77
1792516363 77
1792516368 75
1792516373 75
1792516378 75
1792516383 75
1792516388 75
1792516393 80
1792516398 80
1792516403 80
1792516408 80
1792516413 80
1792516418 80
1792516423 80
1792516429 80
1792516434 82
1792516439 82
1792516444 77
1792516449 77
1792516454 77
```
</details>

---

