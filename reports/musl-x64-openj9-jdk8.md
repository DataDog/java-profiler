---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-13 08:55:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 347 |
| Sample Rate | 5.78/sec |
| Health Score | 361% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 215 |
| Sample Rate | 3.58/sec |
| Health Score | 224% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1794577823 32
1794577828 32
1794577833 32
1794577838 32
1794577843 32
1794577848 32
1794577853 32
1794577858 32
1794577863 32
1794577868 32
1794577873 27
1794577878 27
1794577883 27
1794577888 27
1794577893 27
1794577898 27
1794577903 27
1794577908 27
1794577913 27
1794577918 27
```
</details>

---

