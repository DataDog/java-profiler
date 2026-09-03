---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-03 18:51:25 EDT

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
| CPU Cores (start) | 10 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 715 |
| Sample Rate | 11.92/sec |
| Health Score | 745% |
| Threads | 9 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (2 unique values: 10-12 cores)</summary>

```
1788475518 10
1788475523 10
1788475528 10
1788475533 10
1788475538 12
1788475543 12
1788475548 12
1788475553 12
1788475558 12
1788475563 12
1788475568 12
1788475573 12
1788475578 12
1788475583 12
1788475588 12
1788475593 12
1788475598 12
1788475603 12
1788475608 12
1788475613 12
```
</details>

---

