---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-09 09:57:14 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 9 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 11 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (4 unique values: 41-51 cores)</summary>

```
1794235961 51
1794235966 51
1794235971 51
1794235976 51
1794235981 46
1794235986 46
1794235991 46
1794235996 45
1794236001 45
1794236006 45
1794236011 45
1794236016 45
1794236021 45
1794236026 45
1794236031 45
1794236036 45
1794236041 45
1794236046 46
1794236051 46
1794236056 41
```
</details>

---

