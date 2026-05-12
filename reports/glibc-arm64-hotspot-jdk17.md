---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-12 03:57:41 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 345 |
| Sample Rate | 5.75/sec |
| Health Score | 359% |
| Threads | 14 |
| Allocations | 119 |

<details>
<summary>CPU Timeline (2 unique values: 52-59 cores)</summary>

```
1778572303 59
1778572308 59
1778572313 59
1778572318 59
1778572323 59
1778572328 59
1778572333 59
1778572338 59
1778572343 59
1778572348 59
1778572353 59
1778572358 59
1778572363 52
1778572369 52
1778572374 52
1778572379 52
1778572384 52
1778572389 52
1778572394 52
1778572399 52
```
</details>

---

