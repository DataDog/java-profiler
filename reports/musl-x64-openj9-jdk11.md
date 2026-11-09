---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-09 09:57:14 EST

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 746 |
| Sample Rate | 12.43/sec |
| Health Score | 777% |
| Threads | 9 |
| Allocations | 545 |

<details>
<summary>CPU Timeline (2 unique values: 85-92 cores)</summary>

```
1794235958 92
1794235963 92
1794235968 92
1794235973 85
1794235978 85
1794235983 85
1794235988 85
1794235993 85
1794235998 85
1794236003 85
1794236008 85
1794236013 85
1794236018 85
1794236023 85
1794236028 85
1794236033 85
1794236038 85
1794236044 85
1794236049 85
1794236054 85
```
</details>

---

