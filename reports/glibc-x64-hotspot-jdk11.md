---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-03-11 14:07:58 EDT

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 9 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (4 unique values: 67-82 cores)</summary>

```
1773252305 67
1773252311 67
1773252316 67
1773252321 67
1773252326 72
1773252331 72
1773252336 77
1773252341 77
1773252346 77
1773252351 77
1773252356 77
1773252361 82
1773252366 82
1773252371 82
1773252376 82
1773252381 82
1773252386 82
1773252391 82
1773252396 82
1773252401 82
```
</details>

---

