---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 05:59:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 683 |
| Sample Rate | 11.38/sec |
| Health Score | 711% |
| Threads | 10 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (2 unique values: 49-64 cores)</summary>

```
1795431339 64
1795431344 64
1795431349 64
1795431354 64
1795431359 64
1795431364 64
1795431369 64
1795431374 64
1795431379 64
1795431384 64
1795431389 64
1795431394 64
1795431399 64
1795431404 49
1795431409 49
1795431414 49
1795431419 49
1795431424 49
1795431429 49
1795431434 49
```
</details>

---

