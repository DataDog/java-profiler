---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-18 21:26:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 10 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 10 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 19-24 cores)</summary>

```
1792372859 19
1792372864 19
1792372869 19
1792372874 19
1792372879 19
1792372884 19
1792372889 19
1792372894 19
1792372899 19
1792372904 19
1792372909 19
1792372914 19
1792372919 19
1792372924 19
1792372929 24
1792372934 24
1792372939 24
1792372944 24
1792372949 24
1792372954 24
```
</details>

---

