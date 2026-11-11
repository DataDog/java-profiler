---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 08:20:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 9 |
| Allocations | 421 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 11 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (5 unique values: 29-56 cores)</summary>

```
1794402911 35
1794402916 35
1794402921 35
1794402926 35
1794402931 35
1794402936 54
1794402941 54
1794402946 56
1794402951 56
1794402956 56
1794402961 34
1794402966 34
1794402971 54
1794402976 54
1794402981 54
1794402986 54
1794402992 54
1794402997 54
1794403002 54
1794403007 54
```
</details>

---

