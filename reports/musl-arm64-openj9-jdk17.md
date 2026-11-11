---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-10 19:10:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 328 |
| Sample Rate | 5.47/sec |
| Health Score | 342% |
| Threads | 9 |
| Allocations | 170 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 742 |
| Sample Rate | 12.37/sec |
| Health Score | 773% |
| Threads | 11 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1794355421 47
1794355426 47
1794355431 47
1794355436 47
1794355441 47
1794355446 47
1794355451 47
1794355456 47
1794355461 47
1794355466 47
1794355471 47
1794355476 47
1794355481 47
1794355486 42
1794355491 42
1794355496 42
1794355501 42
1794355506 42
1794355511 42
1794355516 42
```
</details>

---

