---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-14 21:04:20 EST

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
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 11 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 6 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794707971 48
1794707976 48
1794707981 48
1794707986 48
1794707991 48
1794707996 48
1794708001 48
1794708006 48
1794708011 48
1794708016 48
1794708021 48
1794708026 48
1794708031 43
1794708036 43
1794708041 43
1794708046 43
1794708051 43
1794708056 43
1794708061 43
1794708066 43
```
</details>

---

