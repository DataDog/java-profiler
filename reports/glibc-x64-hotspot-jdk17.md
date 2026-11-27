---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-27 13:25:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 9 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 12 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (3 unique values: 32-55 cores)</summary>

```
1795803649 55
1795803654 32
1795803659 32
1795803664 32
1795803669 32
1795803674 32
1795803679 32
1795803684 32
1795803689 32
1795803694 32
1795803699 32
1795803704 37
1795803709 37
1795803714 37
1795803719 37
1795803724 37
1795803729 37
1795803734 37
1795803739 37
1795803744 37
```
</details>

---

