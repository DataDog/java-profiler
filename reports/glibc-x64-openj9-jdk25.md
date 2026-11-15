---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-14 21:04:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 415 |
| Sample Rate | 6.92/sec |
| Health Score | 432% |
| Threads | 9 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 10 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 92-94 cores)</summary>

```
1794707976 92
1794707981 92
1794707986 92
1794707991 92
1794707996 94
1794708001 94
1794708006 94
1794708011 94
1794708016 94
1794708021 94
1794708026 94
1794708031 94
1794708036 94
1794708041 94
1794708046 94
1794708051 94
1794708056 94
1794708061 94
1794708066 94
1794708071 94
```
</details>

---

