---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-26 16:34:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (2 unique values: 87-94 cores)</summary>

```
1777235417 94
1777235422 94
1777235427 94
1777235432 94
1777235437 94
1777235442 94
1777235447 94
1777235452 94
1777235457 94
1777235462 94
1777235467 94
1777235472 94
1777235477 94
1777235482 94
1777235487 94
1777235492 94
1777235497 94
1777235502 87
1777235507 87
1777235512 87
```
</details>

---

