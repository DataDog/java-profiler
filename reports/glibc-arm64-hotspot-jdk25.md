---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-27 20:01:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
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
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 8 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 10 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793145504 48
1793145509 48
1793145514 48
1793145519 48
1793145524 48
1793145529 48
1793145534 48
1793145539 48
1793145544 48
1793145549 48
1793145554 48
1793145559 48
1793145564 48
1793145569 48
1793145574 48
1793145579 48
1793145584 48
1793145589 48
1793145594 48
1793145599 48
```
</details>

---

