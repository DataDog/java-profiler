---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-22 05:47:56 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 716 |
| Sample Rate | 11.93/sec |
| Health Score | 746% |
| Threads | 11 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (2 unique values: 34-36 cores)</summary>

```
1795344252 36
1795344257 36
1795344262 36
1795344267 36
1795344272 36
1795344277 36
1795344282 36
1795344287 36
1795344292 36
1795344298 36
1795344303 36
1795344308 36
1795344313 36
1795344318 36
1795344323 36
1795344328 36
1795344333 36
1795344338 36
1795344343 34
1795344348 34
```
</details>

---

