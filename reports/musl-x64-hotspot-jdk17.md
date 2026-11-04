---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-04 00:07:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 10 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 11 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (2 unique values: 72-81 cores)</summary>

```
1793768529 72
1793768534 72
1793768539 72
1793768544 72
1793768549 72
1793768554 72
1793768559 72
1793768564 72
1793768569 72
1793768574 72
1793768579 72
1793768584 72
1793768589 72
1793768594 72
1793768599 72
1793768604 72
1793768609 72
1793768614 72
1793768619 81
1793768624 81
```
</details>

---

