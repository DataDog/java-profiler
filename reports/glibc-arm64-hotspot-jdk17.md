---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-23 07:23:31 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 356 |
| Sample Rate | 5.93/sec |
| Health Score | 371% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 11 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (5 unique values: 40-46 cores)</summary>

```
1792754381 42
1792754386 40
1792754391 40
1792754396 40
1792754401 40
1792754406 40
1792754411 40
1792754416 40
1792754421 40
1792754426 46
1792754431 46
1792754436 46
1792754441 46
1792754446 46
1792754451 46
1792754456 46
1792754461 41
1792754466 41
1792754471 41
1792754476 41
```
</details>

---

