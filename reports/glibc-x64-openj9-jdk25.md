---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 05:30:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 396 |
| Sample Rate | 6.60/sec |
| Health Score | 412% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 11 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (4 unique values: 58-64 cores)</summary>

```
1794997511 58
1794997516 58
1794997521 58
1794997526 58
1794997531 60
1794997536 60
1794997541 60
1794997546 60
1794997551 60
1794997556 60
1794997561 60
1794997566 60
1794997571 64
1794997576 64
1794997582 64
1794997587 64
1794997592 64
1794997597 64
1794997602 64
1794997607 62
```
</details>

---

