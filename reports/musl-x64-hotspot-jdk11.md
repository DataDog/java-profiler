---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-25 15:07:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 744 |
| Sample Rate | 12.40/sec |
| Health Score | 775% |
| Threads | 9 |
| Allocations | 546 |

<details>
<summary>CPU Timeline (2 unique values: 92-96 cores)</summary>

```
1787684454 96
1787684459 96
1787684464 96
1787684469 96
1787684474 96
1787684479 96
1787684484 92
1787684489 92
1787684494 92
1787684499 92
1787684504 92
1787684509 92
1787684514 92
1787684519 92
1787684524 92
1787684529 92
1787684534 92
1787684539 92
1787684544 92
1787684549 92
```
</details>

---

