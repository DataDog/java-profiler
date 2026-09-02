---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ❌ FAIL

**Date:** 2026-09-02 11:44:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
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
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 2 |
| Sample Rate | 0.03/sec |
| Health Score | 2% |
| Threads | 1 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1788363473 48
1788363478 48
1788363483 48
1788363488 48
1788363493 48
1788363498 48
1788363503 48
1788363508 48
1788363513 48
1788363518 48
1788363523 48
1788363528 48
1788363533 48
1788363538 48
1788363543 48
1788363548 48
1788363553 48
1788363558 48
1788363563 48
1788363568 48
```
</details>

---

