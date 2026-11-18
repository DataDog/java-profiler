---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 13:22:10 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 9 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1795025922 51
1795025927 51
1795025932 51
1795025937 51
1795025942 51
1795025947 51
1795025952 51
1795025957 51
1795025962 51
1795025967 51
1795025972 51
1795025977 51
1795025982 51
1795025987 51
1795025992 51
1795025997 51
1795026002 51
1795026007 51
1795026012 51
1795026017 51
```
</details>

---

