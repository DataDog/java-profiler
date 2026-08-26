---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-26 10:30:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 9 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (3 unique values: 88-96 cores)</summary>

```
1787754338 88
1787754343 91
1787754348 91
1787754353 91
1787754358 91
1787754363 91
1787754368 91
1787754373 91
1787754378 91
1787754383 96
1787754388 96
1787754393 96
1787754398 96
1787754403 96
1787754408 96
1787754413 96
1787754418 96
1787754423 96
1787754428 96
1787754433 96
```
</details>

---

