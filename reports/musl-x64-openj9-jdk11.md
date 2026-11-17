---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 11:50:09 EST

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 944 |
| Sample Rate | 15.73/sec |
| Health Score | 983% |
| Threads | 11 |
| Allocations | 553 |

<details>
<summary>CPU Timeline (2 unique values: 74-91 cores)</summary>

```
1794933911 91
1794933916 91
1794933921 91
1794933926 91
1794933931 91
1794933936 91
1794933941 74
1794933946 74
1794933951 74
1794933956 74
1794933961 74
1794933966 74
1794933971 74
1794933976 74
1794933981 74
1794933986 74
1794933991 74
1794933996 74
1794934001 74
1794934006 74
```
</details>

---

