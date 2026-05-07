---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-07 10:54:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 818 |
| Sample Rate | 13.63/sec |
| Health Score | 852% |
| Threads | 10 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (4 unique values: 71-77 cores)</summary>

```
1778165323 72
1778165328 72
1778165333 72
1778165338 72
1778165343 72
1778165348 72
1778165353 72
1778165358 73
1778165363 73
1778165368 73
1778165374 77
1778165379 77
1778165384 77
1778165389 77
1778165394 77
1778165399 77
1778165404 77
1778165409 77
1778165414 77
1778165419 77
```
</details>

---

