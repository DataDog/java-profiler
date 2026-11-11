---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-10 19:10:50 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1794355426 30
1794355431 30
1794355436 30
1794355441 32
1794355446 32
1794355451 30
1794355456 30
1794355461 30
1794355466 30
1794355471 30
1794355476 30
1794355481 30
1794355486 30
1794355491 30
1794355496 30
1794355501 30
1794355506 30
1794355511 30
1794355516 30
1794355521 30
```
</details>

---

