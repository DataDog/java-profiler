---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-02 08:00:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 10 |
| Allocations | 434 |

<details>
<summary>CPU Timeline (3 unique values: 32-36 cores)</summary>

```
1793624213 36
1793624218 36
1793624223 34
1793624228 34
1793624233 32
1793624238 32
1793624243 32
1793624248 32
1793624253 32
1793624258 32
1793624263 32
1793624268 32
1793624273 32
1793624278 32
1793624283 32
1793624288 32
1793624293 32
1793624298 32
1793624303 32
1793624308 32
```
</details>

---

