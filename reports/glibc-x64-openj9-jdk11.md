---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 00:08:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 791 |
| Sample Rate | 13.18/sec |
| Health Score | 824% |
| Threads | 9 |
| Allocations | 561 |

<details>
<summary>CPU Timeline (4 unique values: 50-81 cores)</summary>

```
1794287005 64
1794287010 64
1794287015 64
1794287020 64
1794287025 64
1794287030 64
1794287035 64
1794287040 64
1794287045 64
1794287050 64
1794287055 64
1794287060 64
1794287065 64
1794287070 64
1794287075 64
1794287080 64
1794287085 64
1794287090 64
1794287095 64
1794287100 81
```
</details>

---

