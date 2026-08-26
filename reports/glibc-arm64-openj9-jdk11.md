---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-26 10:30:25 EDT

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
| CPU Samples | 314 |
| Sample Rate | 5.23/sec |
| Health Score | 327% |
| Threads | 10 |
| Allocations | 135 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 14 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787754314 48
1787754319 48
1787754324 48
1787754329 48
1787754334 48
1787754339 48
1787754344 48
1787754349 48
1787754354 48
1787754359 48
1787754364 43
1787754369 43
1787754374 43
1787754379 43
1787754384 43
1787754389 43
1787754394 43
1787754399 43
1787754404 43
1787754409 43
```
</details>

---

