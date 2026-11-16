---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 10:15:46 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 8 |
| Allocations | 92 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 10 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1794841838 38
1794841843 38
1794841848 38
1794841853 38
1794841858 43
1794841863 43
1794841868 43
1794841873 43
1794841878 43
1794841883 43
1794841888 43
1794841893 43
1794841898 43
1794841903 43
1794841908 43
1794841913 43
1794841918 43
1794841923 43
1794841928 43
1794841933 43
```
</details>

---

