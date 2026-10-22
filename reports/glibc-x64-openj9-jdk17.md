---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-22 09:44:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 8 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 9 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (2 unique values: 20-29 cores)</summary>

```
1792676352 29
1792676357 29
1792676362 29
1792676367 29
1792676372 29
1792676377 29
1792676382 29
1792676387 29
1792676392 20
1792676397 20
1792676402 20
1792676407 20
1792676412 20
1792676417 20
1792676422 20
1792676427 20
1792676432 20
1792676437 20
1792676442 20
1792676447 20
```
</details>

---

