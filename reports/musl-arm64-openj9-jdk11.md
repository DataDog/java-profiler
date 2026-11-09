---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-09 15:36:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 301 |
| Sample Rate | 5.02/sec |
| Health Score | 314% |
| Threads | 12 |
| Allocations | 196 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 12 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (3 unique values: 20-56 cores)</summary>

```
1794256291 20
1794256296 20
1794256301 20
1794256306 20
1794256311 20
1794256316 20
1794256321 20
1794256326 20
1794256331 20
1794256336 20
1794256341 20
1794256346 20
1794256351 20
1794256356 20
1794256361 56
1794256366 56
1794256371 56
1794256376 56
1794256381 56
1794256386 56
```
</details>

---

