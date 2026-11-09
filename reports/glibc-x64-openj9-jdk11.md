---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-09 05:57:47 EST

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 844 |
| Sample Rate | 14.07/sec |
| Health Score | 879% |
| Threads | 9 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (2 unique values: 25-30 cores)</summary>

```
1794221547 25
1794221552 25
1794221557 25
1794221562 25
1794221567 25
1794221572 25
1794221577 25
1794221582 25
1794221587 25
1794221592 25
1794221597 25
1794221602 25
1794221607 25
1794221612 25
1794221617 25
1794221622 25
1794221627 25
1794221632 25
1794221637 30
1794221642 30
```
</details>

---

