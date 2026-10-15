---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-15 11:57:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 355 |
| Sample Rate | 5.92/sec |
| Health Score | 370% |
| Threads | 8 |
| Allocations | 316 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 11 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (4 unique values: 20-26 cores)</summary>

```
1792079302 24
1792079307 24
1792079312 26
1792079317 26
1792079322 26
1792079327 26
1792079332 26
1792079337 26
1792079342 26
1792079347 26
1792079352 20
1792079357 20
1792079362 20
1792079367 20
1792079372 20
1792079377 20
1792079382 20
1792079387 20
1792079392 20
1792079397 20
```
</details>

---

