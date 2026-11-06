---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-06 00:04:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 7 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 11 |
| Allocations | 80 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1793941227 29
1793941232 29
1793941237 29
1793941242 29
1793941247 29
1793941252 29
1793941257 29
1793941262 29
1793941267 29
1793941272 29
1793941277 29
1793941282 29
1793941287 29
1793941292 29
1793941297 29
1793941302 29
1793941307 29
1793941312 29
1793941317 29
1793941322 29
```
</details>

---

