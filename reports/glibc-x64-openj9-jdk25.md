---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 16:19:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 9 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (3 unique values: 71-94 cores)</summary>

```
1795641322 71
1795641327 71
1795641332 71
1795641337 92
1795641342 92
1795641347 92
1795641352 92
1795641357 92
1795641362 92
1795641367 94
1795641372 94
1795641377 94
1795641382 94
1795641387 94
1795641392 94
1795641397 94
1795641402 94
1795641407 94
1795641412 94
1795641417 94
```
</details>

---

