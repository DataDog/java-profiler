---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-17 11:12:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 11 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (5 unique values: 85-93 cores)</summary>

```
1794931719 93
1794931724 93
1794931729 91
1794931734 91
1794931739 91
1794931744 91
1794931749 91
1794931754 91
1794931759 91
1794931764 89
1794931769 89
1794931774 89
1794931779 89
1794931784 89
1794931789 89
1794931794 89
1794931799 89
1794931804 89
1794931809 89
1794931814 87
```
</details>

---

