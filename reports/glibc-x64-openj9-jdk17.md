---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 05:38:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 9 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 9.83/sec |
| Health Score | 614% |
| Threads | 11 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (4 unique values: 71-90 cores)</summary>

```
1794479527 71
1794479532 71
1794479537 71
1794479542 71
1794479547 71
1794479552 71
1794479557 71
1794479562 71
1794479567 71
1794479572 71
1794479577 90
1794479582 90
1794479587 90
1794479592 90
1794479597 90
1794479602 90
1794479607 90
1794479612 88
1794479617 88
1794479622 88
```
</details>

---

