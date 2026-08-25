---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-25 15:07:38 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 10 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (6 unique values: 76-88 cores)</summary>

```
1787684436 80
1787684441 80
1787684446 78
1787684451 78
1787684456 78
1787684461 78
1787684466 78
1787684471 78
1787684476 76
1787684481 76
1787684486 76
1787684491 84
1787684496 84
1787684501 84
1787684506 86
1787684511 86
1787684516 88
1787684521 88
1787684526 88
1787684531 88
```
</details>

---

