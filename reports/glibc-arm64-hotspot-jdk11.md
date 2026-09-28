---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-28 00:58:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 36 |
| Sample Rate | 0.60/sec |
| Health Score | 37% |
| Threads | 9 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (1 unique values: 17-17 cores)</summary>

```
1790571288 17
1790571293 17
1790571298 17
1790571303 17
1790571308 17
1790571313 17
1790571318 17
1790571323 17
1790571328 17
1790571333 17
1790571338 17
1790571343 17
1790571348 17
1790571353 17
1790571358 17
1790571363 17
1790571368 17
1790571373 17
1790571378 17
1790571383 17
```
</details>

---

