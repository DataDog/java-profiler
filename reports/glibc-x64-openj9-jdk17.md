---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 00:05:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 712 |
| Sample Rate | 11.87/sec |
| Health Score | 742% |
| Threads | 12 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (3 unique values: 39-64 cores)</summary>

```
1794805291 39
1794805296 39
1794805301 39
1794805306 39
1794805311 39
1794805316 64
1794805321 64
1794805326 64
1794805331 64
1794805336 64
1794805341 64
1794805346 64
1794805351 64
1794805356 64
1794805361 47
1794805366 47
1794805371 47
1794805376 47
1794805381 47
1794805386 47
```
</details>

---

