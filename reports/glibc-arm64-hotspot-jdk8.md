---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-10 06:26:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 4 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 44-64 cores)</summary>

```
1786357291 61
1786357296 61
1786357301 61
1786357306 61
1786357311 61
1786357316 61
1786357321 61
1786357326 61
1786357331 61
1786357336 64
1786357341 64
1786357346 64
1786357351 64
1786357356 44
1786357361 44
1786357366 44
1786357371 44
1786357376 44
1786357381 44
1786357386 44
```
</details>

---

