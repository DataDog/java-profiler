---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-06 00:04:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 8 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 13 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (4 unique values: 33-48 cores)</summary>

```
1793941242 33
1793941247 33
1793941252 33
1793941257 33
1793941262 38
1793941267 38
1793941272 38
1793941277 38
1793941282 38
1793941287 38
1793941292 38
1793941297 38
1793941302 38
1793941307 38
1793941312 38
1793941317 38
1793941322 38
1793941327 38
1793941332 38
1793941337 43
```
</details>

---

