---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 13:55:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 633 |
| Sample Rate | 10.55/sec |
| Health Score | 659% |
| Threads | 10 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (3 unique values: 60-96 cores)</summary>

```
1789667354 60
1789667359 60
1789667364 60
1789667369 60
1789667374 96
1789667379 96
1789667384 61
1789667389 61
1789667394 61
1789667399 61
1789667404 61
1789667409 61
1789667414 61
1789667419 61
1789667424 61
1789667429 61
1789667434 61
1789667439 61
1789667444 61
1789667449 61
```
</details>

---

