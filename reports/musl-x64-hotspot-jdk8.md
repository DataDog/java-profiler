---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-20 13:06:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 323 |
| Sample Rate | 5.38/sec |
| Health Score | 336% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 416 |
| Sample Rate | 6.93/sec |
| Health Score | 433% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 53-58 cores)</summary>

```
1795197729 58
1795197734 58
1795197739 58
1795197744 53
1795197749 53
1795197754 53
1795197759 53
1795197764 53
1795197769 53
1795197774 53
1795197779 53
1795197784 53
1795197789 53
1795197794 53
1795197799 53
1795197804 53
1795197809 53
1795197814 53
1795197819 53
1795197824 53
```
</details>

---

