---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-20 09:32:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 8 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 768 |
| Sample Rate | 12.80/sec |
| Health Score | 800% |
| Threads | 10 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1787232473 96
1787232478 96
1787232483 96
1787232488 96
1787232493 96
1787232498 96
1787232503 96
1787232508 96
1787232513 96
1787232518 96
1787232523 96
1787232528 96
1787232533 96
1787232538 96
1787232543 96
1787232548 96
1787232553 96
1787232558 96
1787232563 94
1787232568 94
```
</details>

---

