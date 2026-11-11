---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-11 18:20:11 EST

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 289 |
| Sample Rate | 4.82/sec |
| Health Score | 301% |
| Threads | 11 |
| Allocations | 147 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 9 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (3 unique values: 31-41 cores)</summary>

```
1794438994 31
1794438999 36
1794439004 36
1794439009 36
1794439014 31
1794439019 31
1794439024 31
1794439029 31
1794439034 31
1794439039 31
1794439044 31
1794439049 31
1794439054 36
1794439059 36
1794439064 36
1794439069 36
1794439074 36
1794439079 36
1794439084 36
1794439089 36
```
</details>

---

