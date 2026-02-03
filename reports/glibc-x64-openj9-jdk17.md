---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-03 09:47:05 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 414 |
| Sample Rate | 6.90/sec |
| Health Score | 431% |
| Threads | 8 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 9 |
| Allocations | 421 |

<details>
<summary>CPU Timeline (5 unique values: 21-32 cores)</summary>

```
1770129672 30
1770129677 30
1770129682 30
1770129687 30
1770129692 32
1770129697 32
1770129702 32
1770129707 32
1770129712 32
1770129717 32
1770129722 28
1770129727 28
1770129732 23
1770129737 23
1770129742 21
1770129747 21
1770129752 21
1770129757 21
1770129762 21
1770129767 21
```
</details>

---

