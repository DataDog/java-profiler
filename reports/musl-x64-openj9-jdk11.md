---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-01-27 14:14:22 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 18.00/sec |
| Health Score | 1125% |
| Threads | 8 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 774 |
| Sample Rate | 25.80/sec |
| Health Score | 1612% |
| Threads | 9 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1769540951 30
1769540956 30
1769540961 30
1769540966 30
1769540971 30
1769540976 30
1769540981 30
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
```
</details>

---

