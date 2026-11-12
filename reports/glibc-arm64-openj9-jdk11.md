---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 05:58:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 217 |
| Sample Rate | 3.62/sec |
| Health Score | 226% |
| Threads | 12 |
| Allocations | 86 |

<details>
<summary>CPU Timeline (2 unique values: 19-23 cores)</summary>

```
1794480728 23
1794480733 23
1794480738 23
1794480743 23
1794480748 23
1794480753 23
1794480758 23
1794480763 23
1794480768 23
1794480773 23
1794480778 23
1794480783 23
1794480788 23
1794480793 23
1794480798 23
1794480803 23
1794480808 23
1794480813 19
1794480818 19
1794480823 19
```
</details>

---

