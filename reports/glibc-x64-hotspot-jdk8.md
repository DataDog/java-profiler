---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-16 09:37:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 159 |
| Sample Rate | 2.65/sec |
| Health Score | 166% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 181 |
| Sample Rate | 3.02/sec |
| Health Score | 189% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 71-90 cores)</summary>

```
1794839607 77
1794839612 75
1794839617 75
1794839622 71
1794839627 71
1794839632 71
1794839637 73
1794839642 73
1794839647 73
1794839652 73
1794839657 73
1794839662 73
1794839667 73
1794839672 73
1794839677 73
1794839682 73
1794839687 90
1794839692 90
1794839697 90
1794839702 90
```
</details>

---

