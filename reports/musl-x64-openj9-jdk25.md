---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-01-27 14:14:22 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 22.50/sec |
| Health Score | 1406% |
| Threads | 11 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 796 |
| Sample Rate | 26.53/sec |
| Health Score | 1658% |
| Threads | 11 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1769540956 32
1769540961 32
1769540966 32
1769540971 32
1769540976 32
1769540981 32
1769540986 32
1769540991 32
1769540996 32
1769541001 32
1769541006 32
1769541011 32
1769541016 32
1769541021 32
1769541026 32
1769541031 32
1769541036 32
1769541041 32
1769541046 32
1769541051 32
```
</details>

---

