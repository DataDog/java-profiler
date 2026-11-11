---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 11:40:36 EST

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 10 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 217 |
| Sample Rate | 3.62/sec |
| Health Score | 226% |
| Threads | 10 |
| Allocations | 115 |

<details>
<summary>CPU Timeline (3 unique values: 35-40 cores)</summary>

```
1794414843 35
1794414848 35
1794414853 35
1794414858 35
1794414863 35
1794414868 35
1794414873 35
1794414878 35
1794414883 37
1794414888 37
1794414893 37
1794414898 37
1794414903 37
1794414909 37
1794414914 37
1794414919 37
1794414924 37
1794414929 37
1794414934 40
1794414939 40
```
</details>

---

