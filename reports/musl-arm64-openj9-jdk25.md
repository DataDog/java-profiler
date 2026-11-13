---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 11:44:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 279 |
| Sample Rate | 4.65/sec |
| Health Score | 291% |
| Threads | 12 |
| Allocations | 143 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 10 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (3 unique values: 41-51 cores)</summary>

```
1794587971 51
1794587976 51
1794587981 51
1794587986 51
1794587991 51
1794587996 51
1794588001 51
1794588006 51
1794588011 51
1794588016 51
1794588021 51
1794588026 51
1794588031 51
1794588036 51
1794588041 51
1794588046 51
1794588051 51
1794588056 51
1794588061 46
1794588066 46
```
</details>

---

