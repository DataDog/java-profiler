---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-19 10:58:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 10 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (2 unique values: 53-73 cores)</summary>

```
1787151268 73
1787151273 73
1787151278 73
1787151283 73
1787151288 73
1787151293 73
1787151298 73
1787151303 53
1787151308 53
1787151313 53
1787151318 53
1787151323 53
1787151328 53
1787151333 53
1787151338 53
1787151343 53
1787151348 53
1787151353 53
1787151358 53
1787151363 53
```
</details>

---

