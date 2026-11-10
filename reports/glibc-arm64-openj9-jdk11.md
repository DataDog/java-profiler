---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 10:58:06 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 134 |
| Sample Rate | 2.23/sec |
| Health Score | 139% |
| Threads | 7 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 8 |
| Allocations | 24 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1794325966 48
1794325971 48
1794325976 46
1794325981 46
1794325986 46
1794325991 46
1794325996 46
1794326001 46
1794326006 46
1794326011 46
1794326016 48
1794326021 48
1794326026 48
1794326031 48
1794326036 48
1794326041 48
1794326046 48
1794326051 48
1794326056 48
1794326061 48
```
</details>

---

