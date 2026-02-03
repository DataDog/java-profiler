---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-03 09:47:06 EST

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 432 |
| Sample Rate | 7.20/sec |
| Health Score | 450% |
| Threads | 9 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1022 |
| Sample Rate | 17.03/sec |
| Health Score | 1064% |
| Threads | 12 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (3 unique values: 54-79 cores)</summary>

```
1770129672 79
1770129677 79
1770129682 79
1770129687 79
1770129692 79
1770129697 79
1770129702 58
1770129707 58
1770129712 58
1770129717 58
1770129722 58
1770129727 58
1770129732 58
1770129737 58
1770129742 58
1770129747 58
1770129752 58
1770129757 58
1770129762 58
1770129767 58
```
</details>

---

