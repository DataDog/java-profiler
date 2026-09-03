---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-03 18:51:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 10 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1788475513 59
1788475518 59
1788475523 59
1788475528 59
1788475533 61
1788475538 61
1788475543 61
1788475548 61
1788475553 61
1788475558 61
1788475563 61
1788475568 61
1788475573 61
1788475578 61
1788475583 61
1788475588 61
1788475593 59
1788475598 59
1788475603 59
1788475608 59
```
</details>

---

