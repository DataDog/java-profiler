---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 13:55:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 8 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 10 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (2 unique values: 15-17 cores)</summary>

```
1789667363 17
1789667368 17
1789667373 17
1789667378 17
1789667383 15
1789667388 15
1789667393 15
1789667398 15
1789667403 15
1789667408 15
1789667413 15
1789667418 15
1789667423 15
1789667428 15
1789667433 15
1789667438 15
1789667443 15
1789667448 15
1789667453 15
1789667458 15
```
</details>

---

