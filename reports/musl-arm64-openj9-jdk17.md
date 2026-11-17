---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-17 10:37:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 14 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1794929301 51
1794929306 51
1794929311 51
1794929316 51
1794929321 51
1794929326 51
1794929331 51
1794929336 51
1794929341 51
1794929346 49
1794929351 49
1794929356 49
1794929361 49
1794929366 49
1794929371 49
1794929376 49
1794929381 49
1794929386 51
1794929391 51
1794929396 51
```
</details>

---

