---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-03 18:51:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 9 |
| Allocations | 542 |

<details>
<summary>CPU Timeline (2 unique values: 61-81 cores)</summary>

```
1788475518 61
1788475523 61
1788475528 61
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
1788475583 81
1788475588 81
1788475593 81
1788475598 81
1788475603 81
1788475608 81
1788475613 81
```
</details>

---

