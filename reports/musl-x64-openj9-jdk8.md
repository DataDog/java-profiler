---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-28 07:43:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 175 |
| Sample Rate | 2.92/sec |
| Health Score | 182% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 148 |
| Sample Rate | 2.47/sec |
| Health Score | 154% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 56-61 cores)</summary>

```
1793187401 56
1793187406 56
1793187411 56
1793187416 61
1793187421 61
1793187426 61
1793187431 61
1793187436 61
1793187441 61
1793187446 61
1793187451 61
1793187456 61
1793187461 61
1793187466 61
1793187471 61
1793187476 61
1793187481 61
1793187486 61
1793187491 61
1793187496 61
```
</details>

---

