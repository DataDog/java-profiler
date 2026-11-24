---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-24 09:31:27 EST

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 138 |
| Sample Rate | 2.30/sec |
| Health Score | 144% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 440 |
| Sample Rate | 7.33/sec |
| Health Score | 458% |
| Threads | 15 |
| Allocations | 171 |

<details>
<summary>CPU Timeline (2 unique values: 54-59 cores)</summary>

```
1795530275 54
1795530280 54
1795530285 54
1795530290 54
1795530295 54
1795530300 54
1795530305 54
1795530310 54
1795530315 54
1795530320 54
1795530326 54
1795530331 54
1795530336 54
1795530341 54
1795530346 59
1795530351 59
1795530356 59
1795530361 59
1795530366 59
1795530371 59
```
</details>

---

