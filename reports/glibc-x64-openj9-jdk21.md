---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-30 11:36:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 9 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 781 |
| Sample Rate | 13.02/sec |
| Health Score | 814% |
| Threads | 11 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (4 unique values: 74-79 cores)</summary>

```
1790782317 79
1790782322 79
1790782327 79
1790782332 79
1790782337 79
1790782342 79
1790782347 77
1790782352 77
1790782357 75
1790782362 75
1790782367 75
1790782372 75
1790782377 75
1790782382 75
1790782387 75
1790782392 75
1790782397 75
1790782402 75
1790782407 75
1790782412 74
```
</details>

---

