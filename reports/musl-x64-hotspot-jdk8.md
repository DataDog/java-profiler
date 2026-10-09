---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-09 05:55:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 166 |
| Sample Rate | 2.77/sec |
| Health Score | 173% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 305 |
| Sample Rate | 5.08/sec |
| Health Score | 318% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 13-17 cores)</summary>

```
1791539320 15
1791539325 15
1791539330 15
1791539335 15
1791539340 15
1791539346 15
1791539351 15
1791539356 13
1791539361 13
1791539366 13
1791539371 13
1791539376 13
1791539381 13
1791539386 13
1791539391 15
1791539396 15
1791539401 17
1791539406 17
1791539411 17
1791539416 17
```
</details>

---

