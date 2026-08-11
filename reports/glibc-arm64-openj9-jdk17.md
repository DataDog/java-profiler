---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-11 08:48:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 8 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 13 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (3 unique values: 32-39 cores)</summary>

```
1786452256 32
1786452261 32
1786452266 32
1786452271 32
1786452276 32
1786452281 37
1786452286 37
1786452291 37
1786452296 37
1786452301 37
1786452306 37
1786452311 37
1786452316 37
1786452321 39
1786452326 39
1786452331 39
1786452336 39
1786452341 39
1786452346 39
1786452351 39
```
</details>

---

