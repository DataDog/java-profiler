---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-16 09:37:45 EST

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 10 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (2 unique values: 77-79 cores)</summary>

```
1794839622 77
1794839627 77
1794839632 77
1794839637 77
1794839642 77
1794839647 77
1794839652 77
1794839657 77
1794839662 77
1794839667 77
1794839672 77
1794839677 77
1794839682 79
1794839687 79
1794839692 79
1794839697 79
1794839702 79
1794839707 79
1794839712 79
1794839717 79
```
</details>

---

