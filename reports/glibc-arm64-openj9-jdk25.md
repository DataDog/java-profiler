---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 11:54:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 9 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 210 |
| Sample Rate | 3.50/sec |
| Health Score | 219% |
| Threads | 13 |
| Allocations | 155 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1794329334 46
1794329339 46
1794329344 46
1794329349 46
1794329354 46
1794329359 48
1794329364 48
1794329369 48
1794329374 48
1794329379 48
1794329384 48
1794329389 48
1794329394 48
1794329399 48
1794329404 48
1794329409 48
1794329414 48
1794329419 48
1794329424 48
1794329429 48
```
</details>

---

