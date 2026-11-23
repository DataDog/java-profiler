---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 09:03:26 EST

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 9 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 742 |
| Sample Rate | 12.37/sec |
| Health Score | 773% |
| Threads | 12 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (3 unique values: 39-49 cores)</summary>

```
1795442338 39
1795442343 39
1795442348 39
1795442353 39
1795442358 39
1795442363 39
1795442368 44
1795442373 44
1795442378 44
1795442383 44
1795442388 44
1795442393 44
1795442398 44
1795442403 44
1795442408 44
1795442413 44
1795442418 44
1795442423 44
1795442428 44
1795442433 44
```
</details>

---

