---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-10 06:26:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 944 |
| Sample Rate | 15.73/sec |
| Health Score | 983% |
| Threads | 11 |
| Allocations | 428 |

<details>
<summary>CPU Timeline (2 unique values: 28-31 cores)</summary>

```
1786357316 28
1786357321 28
1786357326 28
1786357331 28
1786357336 28
1786357341 28
1786357346 28
1786357351 28
1786357356 28
1786357361 31
1786357366 31
1786357371 31
1786357376 31
1786357381 31
1786357386 31
1786357391 31
1786357396 31
1786357401 31
1786357406 31
1786357411 31
```
</details>

---

