---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-10 10:58:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 12 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 9 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1794325991 43
1794325996 48
1794326001 48
1794326006 48
1794326011 48
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
1794326066 48
1794326071 48
1794326076 48
1794326081 48
1794326086 48
```
</details>

---

