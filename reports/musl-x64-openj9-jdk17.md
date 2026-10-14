---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-14 11:49:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 748 |
| Sample Rate | 12.47/sec |
| Health Score | 779% |
| Threads | 11 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (2 unique values: 55-75 cores)</summary>

```
1791992503 75
1791992508 75
1791992513 55
1791992518 55
1791992523 55
1791992528 55
1791992533 55
1791992538 55
1791992543 55
1791992548 55
1791992553 55
1791992558 55
1791992563 55
1791992569 55
1791992574 55
1791992579 55
1791992584 55
1791992589 55
1791992594 55
1791992599 55
```
</details>

---

