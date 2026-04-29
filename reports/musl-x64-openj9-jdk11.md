---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-29 07:38:33 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 819 |
| Sample Rate | 13.65/sec |
| Health Score | 853% |
| Threads | 9 |
| Allocations | 558 |

<details>
<summary>CPU Timeline (3 unique values: 41-56 cores)</summary>

```
1777462478 41
1777462483 41
1777462488 41
1777462493 41
1777462498 41
1777462503 41
1777462508 41
1777462513 41
1777462518 41
1777462523 41
1777462528 56
1777462533 56
1777462538 56
1777462543 56
1777462548 56
1777462553 56
1777462558 54
1777462563 54
1777462568 54
1777462573 54
```
</details>

---

