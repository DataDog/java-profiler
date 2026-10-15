---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-15 11:57:02 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 7 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 7 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (3 unique values: 20-26 cores)</summary>

```
1792079277 24
1792079282 24
1792079287 24
1792079292 24
1792079297 24
1792079302 24
1792079307 24
1792079312 26
1792079317 26
1792079322 26
1792079327 26
1792079332 26
1792079337 26
1792079342 20
1792079347 20
1792079352 20
1792079357 20
1792079362 20
1792079367 20
1792079372 20
```
</details>

---

