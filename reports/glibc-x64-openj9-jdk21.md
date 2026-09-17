---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-17 13:55:47 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 11 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (2 unique values: 72-81 cores)</summary>

```
1789667364 72
1789667369 72
1789667374 81
1789667379 81
1789667384 81
1789667389 81
1789667394 81
1789667399 81
1789667404 81
1789667409 81
1789667414 81
1789667419 81
1789667424 81
1789667429 81
1789667434 81
1789667439 81
1789667444 81
1789667449 81
1789667454 81
1789667459 81
```
</details>

---

