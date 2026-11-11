---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 05:46:24 EST

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 10 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (3 unique values: 67-96 cores)</summary>

```
1794393734 96
1794393739 89
1794393744 89
1794393749 67
1794393754 67
1794393759 67
1794393764 67
1794393769 67
1794393774 67
1794393779 67
1794393784 67
1794393789 67
1794393794 67
1794393799 67
1794393804 67
1794393809 67
1794393814 67
1794393819 67
1794393824 67
1794393829 67
```
</details>

---

