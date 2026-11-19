---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 12:38:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 920 |
| Sample Rate | 15.33/sec |
| Health Score | 958% |
| Threads | 11 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (2 unique values: 58-67 cores)</summary>

```
1795109607 67
1795109612 67
1795109617 58
1795109622 58
1795109627 58
1795109632 58
1795109637 58
1795109642 58
1795109647 58
1795109652 58
1795109657 58
1795109662 58
1795109667 58
1795109672 58
1795109677 58
1795109682 58
1795109687 58
1795109692 58
1795109697 58
1795109702 58
```
</details>

---

