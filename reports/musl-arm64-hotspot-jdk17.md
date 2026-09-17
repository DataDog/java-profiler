---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-17 13:55:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 8 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 250 |
| Sample Rate | 4.17/sec |
| Health Score | 261% |
| Threads | 9 |
| Allocations | 145 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (2 unique values: 8-13 cores)</summary>

```
1789667434 8
1789667439 8
1789667444 8
1789667449 8
1789667454 8
1789667459 8
1789667464 8
1789667469 13
1789667474 13
1789667479 13
1789667484 13
1789667489 13
1789667494 13
1789667499 13
1789667504 13
1789667509 13
1789667514 13
1789667519 13
1789667524 13
1789667529 13
```
</details>

---

