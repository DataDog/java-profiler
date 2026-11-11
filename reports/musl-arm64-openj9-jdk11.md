---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 05:46:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 14 |
| Allocations | 131 |

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

