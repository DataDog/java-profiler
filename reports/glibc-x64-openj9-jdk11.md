---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 05:46:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 9 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (5 unique values: 64-76 cores)</summary>

```
1794393754 66
1794393759 66
1794393764 66
1794393769 66
1794393774 66
1794393779 66
1794393784 66
1794393789 66
1794393794 66
1794393799 64
1794393804 64
1794393809 73
1794393814 73
1794393819 73
1794393824 71
1794393829 71
1794393834 73
1794393839 73
1794393844 73
1794393849 73
```
</details>

---

