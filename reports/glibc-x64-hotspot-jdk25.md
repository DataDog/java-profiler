---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-16 07:37:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 415 |
| Sample Rate | 6.92/sec |
| Health Score | 432% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 10 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1794832318 64
1794832323 64
1794832329 64
1794832334 64
1794832339 64
1794832344 64
1794832349 64
1794832354 64
1794832359 64
1794832364 64
1794832369 47
1794832374 47
1794832379 47
1794832384 47
1794832389 47
1794832394 47
1794832399 47
1794832404 47
1794832409 47
1794832414 47
```
</details>

---

