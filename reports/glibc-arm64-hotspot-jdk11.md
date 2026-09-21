---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 03:29:10 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 8 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 433 |
| Sample Rate | 7.22/sec |
| Health Score | 451% |
| Threads | 11 |
| Allocations | 185 |

<details>
<summary>CPU Timeline (3 unique values: 27-37 cores)</summary>

```
1789975508 27
1789975513 27
1789975518 32
1789975523 32
1789975528 37
1789975533 37
1789975538 37
1789975543 37
1789975548 37
1789975553 37
1789975558 37
1789975563 37
1789975568 37
1789975573 37
1789975578 37
1789975583 37
1789975588 37
1789975593 37
1789975598 37
1789975603 37
```
</details>

---

