---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-03 11:22:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 215 |
| Sample Rate | 3.58/sec |
| Health Score | 224% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 187 |
| Sample Rate | 3.12/sec |
| Health Score | 195% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 60-68 cores)</summary>

```
1793722598 66
1793722603 66
1793722608 66
1793722613 66
1793722618 66
1793722623 66
1793722628 66
1793722633 66
1793722638 66
1793722643 66
1793722648 66
1793722653 66
1793722658 68
1793722663 68
1793722668 68
1793722673 62
1793722678 62
1793722683 60
1793722688 60
1793722693 60
```
</details>

---

