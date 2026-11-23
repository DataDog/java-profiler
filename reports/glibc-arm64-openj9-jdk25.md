---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 06:01:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 11 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 280 |
| Sample Rate | 4.67/sec |
| Health Score | 292% |
| Threads | 13 |
| Allocations | 132 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
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
1795431404 64
1795431409 64
1795431414 64
1795431419 64
1795431424 64
1795431429 64
1795431434 59
1795431439 59
```
</details>

---

