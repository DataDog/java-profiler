---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-21 05:26:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 27-32 cores)</summary>

```
1789982372 28
1789982377 28
1789982382 30
1789982387 30
1789982392 30
1789982397 30
1789982402 30
1789982407 30
1789982412 28
1789982417 28
1789982422 29
1789982427 29
1789982432 29
1789982437 29
1789982442 29
1789982447 29
1789982452 32
1789982457 32
1789982462 32
1789982467 27
```
</details>

---

