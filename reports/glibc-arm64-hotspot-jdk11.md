---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 00:08:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
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
| CPU Samples | 157 |
| Sample Rate | 2.62/sec |
| Health Score | 164% |
| Threads | 8 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 424 |
| Sample Rate | 7.07/sec |
| Health Score | 442% |
| Threads | 14 |
| Allocations | 167 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794287045 48
1794287050 48
1794287055 48
1794287060 48
1794287065 48
1794287070 43
1794287075 43
1794287080 43
1794287085 43
1794287090 43
1794287095 43
1794287100 43
1794287105 43
1794287110 43
1794287115 43
1794287120 43
1794287125 43
1794287130 48
1794287135 48
1794287140 48
```
</details>

---

