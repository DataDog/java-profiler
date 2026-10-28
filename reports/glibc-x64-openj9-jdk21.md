---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-28 07:43:22 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 9 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 10 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (2 unique values: 56-61 cores)</summary>

```
1793187421 61
1793187426 61
1793187431 61
1793187436 61
1793187441 56
1793187446 56
1793187451 56
1793187456 56
1793187461 56
1793187466 56
1793187471 56
1793187476 56
1793187481 56
1793187486 56
1793187491 56
1793187496 56
1793187501 56
1793187506 56
1793187511 56
1793187516 56
```
</details>

---

