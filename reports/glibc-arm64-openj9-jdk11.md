---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 08:24:38 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 333 |
| Sample Rate | 5.55/sec |
| Health Score | 347% |
| Threads | 9 |
| Allocations | 177 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 7 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (2 unique values: 53-64 cores)</summary>

```
1790770849 64
1790770854 64
1790770859 64
1790770864 64
1790770869 64
1790770874 64
1790770879 64
1790770884 64
1790770889 64
1790770894 64
1790770899 64
1790770904 64
1790770909 64
1790770914 64
1790770919 53
1790770924 53
1790770929 53
1790770934 53
1790770939 53
1790770944 53
```
</details>

---

