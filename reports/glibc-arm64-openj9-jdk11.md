---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 08:47:48 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 9 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 951 |
| Sample Rate | 15.85/sec |
| Health Score | 991% |
| Threads | 9 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (3 unique values: 34-60 cores)</summary>

```
1794922866 34
1794922871 34
1794922876 34
1794922881 47
1794922886 47
1794922891 47
1794922896 47
1794922901 47
1794922906 47
1794922911 47
1794922916 47
1794922921 47
1794922926 47
1794922931 47
1794922936 47
1794922941 47
1794922946 47
1794922952 47
1794922957 47
1794922962 47
```
</details>

---

