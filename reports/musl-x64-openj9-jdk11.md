---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-20 10:05:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 506 |
| Sample Rate | 8.43/sec |
| Health Score | 527% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 712 |
| Sample Rate | 11.87/sec |
| Health Score | 742% |
| Threads | 11 |
| Allocations | 550 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1787234361 94
1787234366 94
1787234371 94
1787234376 94
1787234381 96
1787234386 96
1787234391 96
1787234396 96
1787234401 96
1787234406 96
1787234411 96
1787234416 96
1787234421 96
1787234426 96
1787234431 96
1787234436 96
1787234441 96
1787234446 96
1787234451 96
1787234456 96
```
</details>

---

