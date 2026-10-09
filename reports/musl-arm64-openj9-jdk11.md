---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-09 03:59:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 12 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 425 |
| Sample Rate | 7.08/sec |
| Health Score | 442% |
| Threads | 14 |
| Allocations | 175 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1791532523 48
1791532528 48
1791532533 48
1791532538 48
1791532543 48
1791532548 48
1791532553 48
1791532558 48
1791532563 48
1791532568 48
1791532573 48
1791532578 48
1791532583 48
1791532588 48
1791532593 43
1791532598 43
1791532603 43
1791532608 43
1791532613 43
1791532618 43
```
</details>

---

