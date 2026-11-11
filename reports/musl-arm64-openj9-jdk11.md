---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 18:20:13 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 8 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 265 |
| Sample Rate | 4.42/sec |
| Health Score | 276% |
| Threads | 13 |
| Allocations | 133 |

<details>
<summary>CPU Timeline (3 unique values: 41-46 cores)</summary>

```
1794438878 46
1794438883 46
1794438888 46
1794438893 46
1794438898 46
1794438903 46
1794438908 41
1794438913 41
1794438918 41
1794438923 41
1794438928 41
1794438933 41
1794438938 43
1794438943 43
1794438948 43
1794438953 43
1794438958 43
1794438963 43
1794438968 43
1794438973 43
```
</details>

---

