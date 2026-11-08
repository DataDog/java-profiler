---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-08 14:27:51 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 227 |
| Sample Rate | 3.78/sec |
| Health Score | 236% |
| Threads | 10 |
| Allocations | 144 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (3 unique values: 24-34 cores)</summary>

```
1794165871 24
1794165876 24
1794165881 24
1794165886 24
1794165891 24
1794165896 24
1794165901 24
1794165906 24
1794165911 24
1794165916 29
1794165921 29
1794165926 34
1794165931 34
1794165936 34
1794165941 34
1794165946 34
1794165951 34
1794165956 34
1794165961 34
1794165966 34
```
</details>

---

