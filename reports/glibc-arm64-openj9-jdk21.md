---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 10:09:36 EST

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
| CPU Cores (start) | 48 |
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
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 14 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794495969 48
1794495974 48
1794495979 48
1794495984 48
1794495989 48
1794495994 48
1794495999 48
1794496004 48
1794496009 48
1794496014 48
1794496019 48
1794496024 48
1794496029 48
1794496034 48
1794496039 43
1794496044 43
1794496049 43
1794496054 43
1794496059 43
1794496064 43
```
</details>

---

