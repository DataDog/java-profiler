---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-27 13:25:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 33 |
| Sample Rate | 0.55/sec |
| Health Score | 34% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 5 |
| Sample Rate | 0.08/sec |
| Health Score | 5% |
| Threads | 5 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 61-66 cores)</summary>

```
1795803654 62
1795803659 62
1795803664 62
1795803669 62
1795803674 62
1795803679 64
1795803684 64
1795803689 64
1795803694 64
1795803699 66
1795803704 66
1795803709 66
1795803714 65
1795803719 65
1795803724 63
1795803729 63
1795803734 63
1795803739 63
1795803744 63
1795803749 63
```
</details>

---

