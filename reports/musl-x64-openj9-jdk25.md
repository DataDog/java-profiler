---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-17 11:12:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 10 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (2 unique values: 66-68 cores)</summary>

```
1794931689 66
1794931694 66
1794931699 66
1794931704 66
1794931709 66
1794931714 66
1794931719 66
1794931724 66
1794931729 68
1794931734 68
1794931739 68
1794931744 68
1794931749 68
1794931754 68
1794931759 68
1794931764 68
1794931769 68
1794931774 68
1794931779 68
1794931784 68
```
</details>

---

