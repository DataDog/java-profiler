---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-04 00:07:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 9 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (3 unique values: 18-22 cores)</summary>

```
1793768564 22
1793768569 22
1793768574 22
1793768579 22
1793768584 22
1793768589 22
1793768594 22
1793768599 18
1793768604 18
1793768609 18
1793768614 18
1793768619 18
1793768624 18
1793768629 18
1793768634 18
1793768639 18
1793768644 18
1793768649 18
1793768654 18
1793768659 18
```
</details>

---

