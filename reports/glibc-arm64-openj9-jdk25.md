---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 05:46:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 240 |
| Sample Rate | 4.00/sec |
| Health Score | 250% |
| Threads | 11 |
| Allocations | 134 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 12 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794393779 46
1794393784 51
1794393789 51
1794393794 51
1794393799 51
1794393804 51
1794393809 51
1794393814 51
1794393819 51
1794393824 51
1794393829 51
1794393834 51
1794393839 51
1794393844 51
1794393849 51
1794393854 51
1794393859 51
1794393864 51
1794393869 51
1794393874 51
```
</details>

---

