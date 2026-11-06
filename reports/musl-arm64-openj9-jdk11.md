---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-06 00:04:48 EST

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 289 |
| Sample Rate | 4.82/sec |
| Health Score | 301% |
| Threads | 15 |
| Allocations | 180 |

<details>
<summary>CPU Timeline (2 unique values: 22-27 cores)</summary>

```
1793941197 27
1793941202 27
1793941207 27
1793941212 27
1793941217 27
1793941222 27
1793941227 27
1793941232 27
1793941237 27
1793941242 27
1793941247 22
1793941252 22
1793941257 22
1793941262 22
1793941267 22
1793941272 22
1793941277 22
1793941282 22
1793941287 22
1793941292 22
```
</details>

---

