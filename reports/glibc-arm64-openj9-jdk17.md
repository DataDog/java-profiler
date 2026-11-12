---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 06:49:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 15 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1794483886 38
1794483891 38
1794483896 38
1794483901 38
1794483906 38
1794483911 38
1794483916 38
1794483921 38
1794483926 38
1794483931 38
1794483936 38
1794483941 38
1794483946 38
1794483951 43
1794483956 43
1794483961 43
1794483966 43
1794483971 43
1794483976 43
1794483981 43
```
</details>

---

