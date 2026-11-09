---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-09 16:19:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 753 |
| Sample Rate | 12.55/sec |
| Health Score | 784% |
| Threads | 10 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (2 unique values: 56-58 cores)</summary>

```
1794258862 56
1794258867 56
1794258872 56
1794258877 56
1794258882 56
1794258887 56
1794258892 58
1794258897 58
1794258902 58
1794258907 58
1794258912 58
1794258917 58
1794258922 58
1794258927 58
1794258932 58
1794258937 58
1794258942 58
1794258947 58
1794258952 58
1794258957 58
```
</details>

---

