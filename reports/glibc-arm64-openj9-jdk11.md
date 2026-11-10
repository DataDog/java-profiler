---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 11:54:21 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1010 |
| Sample Rate | 16.83/sec |
| Health Score | 1052% |
| Threads | 10 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794329324 48
1794329329 48
1794329334 48
1794329339 48
1794329344 48
1794329349 48
1794329354 48
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
```
</details>

---

