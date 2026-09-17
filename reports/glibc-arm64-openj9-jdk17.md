---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 13:55:46 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 9 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 12 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (2 unique values: 28-59 cores)</summary>

```
1789667404 28
1789667409 28
1789667414 28
1789667419 28
1789667424 28
1789667429 28
1789667434 28
1789667439 28
1789667444 28
1789667449 28
1789667454 28
1789667459 59
1789667464 59
1789667469 59
1789667474 59
1789667479 59
1789667484 59
1789667489 59
1789667494 59
1789667499 59
```
</details>

---

