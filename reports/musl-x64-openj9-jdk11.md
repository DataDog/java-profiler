---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 16:24:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1023 |
| Sample Rate | 17.05/sec |
| Health Score | 1066% |
| Threads | 11 |
| Allocations | 555 |

<details>
<summary>CPU Timeline (2 unique values: 91-93 cores)</summary>

```
1794431669 91
1794431674 91
1794431679 93
1794431684 93
1794431689 93
1794431694 93
1794431699 93
1794431704 93
1794431709 93
1794431714 93
1794431719 93
1794431724 93
1794431729 93
1794431734 93
1794431739 93
1794431744 93
1794431749 93
1794431754 93
1794431759 93
1794431764 93
```
</details>

---

