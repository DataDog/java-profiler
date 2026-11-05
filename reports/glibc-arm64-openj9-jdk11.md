---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-05 10:57:51 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 424 |
| Sample Rate | 7.07/sec |
| Health Score | 442% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 10 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793893956 32
1793893961 32
1793893966 32
1793893971 32
1793893976 32
1793893981 32
1793893986 32
1793893991 32
1793893996 32
1793894001 32
1793894006 32
1793894011 32
1793894016 32
1793894021 32
1793894026 32
1793894031 32
1793894036 32
1793894041 32
1793894046 32
1793894051 32
```
</details>

---

