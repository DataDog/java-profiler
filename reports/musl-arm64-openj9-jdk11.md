---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 16:45:46 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
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
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 30 |
| Sample Rate | 0.50/sec |
| Health Score | 31% |
| Threads | 11 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795642889 64
1795642894 64
1795642899 64
1795642904 64
1795642909 64
1795642914 64
1795642919 64
1795642924 64
1795642929 64
1795642934 64
1795642939 64
1795642944 64
1795642949 64
1795642954 64
1795642959 64
1795642964 64
1795642969 64
1795642974 64
1795642979 64
1795642984 64
```
</details>

---

