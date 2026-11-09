---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-09 16:18:59 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 8 |
| Allocations | 42 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 10 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (5 unique values: 35-45 cores)</summary>

```
1794258897 43
1794258902 43
1794258907 43
1794258912 43
1794258917 45
1794258922 45
1794258927 45
1794258932 45
1794258937 45
1794258942 45
1794258947 45
1794258952 45
1794258957 45
1794258962 42
1794258967 42
1794258972 42
1794258977 42
1794258982 37
1794258987 37
1794258992 37
```
</details>

---

