---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 07:21:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 335 |
| Sample Rate | 5.58/sec |
| Health Score | 349% |
| Threads | 10 |
| Allocations | 170 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 17-22 cores)</summary>

```
1789989489 17
1789989494 17
1789989499 17
1789989504 17
1789989509 17
1789989514 17
1789989519 17
1789989524 17
1789989529 17
1789989534 17
1789989539 17
1789989544 22
1789989549 22
1789989554 22
1789989559 22
1789989564 22
1789989569 22
1789989574 22
1789989579 22
1789989584 22
```
</details>

---

