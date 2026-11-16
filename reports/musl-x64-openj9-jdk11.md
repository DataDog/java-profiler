---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 10:15:48 EST

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 829 |
| Sample Rate | 13.82/sec |
| Health Score | 864% |
| Threads | 9 |
| Allocations | 554 |

<details>
<summary>CPU Timeline (2 unique values: 67-69 cores)</summary>

```
1794841828 67
1794841833 67
1794841838 69
1794841843 69
1794841848 69
1794841853 69
1794841858 69
1794841863 69
1794841868 69
1794841873 67
1794841878 67
1794841883 67
1794841888 67
1794841893 67
1794841898 67
1794841903 67
1794841908 67
1794841913 67
1794841918 67
1794841923 69
```
</details>

---

