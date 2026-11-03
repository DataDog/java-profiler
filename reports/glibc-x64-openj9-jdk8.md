---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-03 11:22:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 195 |
| Sample Rate | 3.25/sec |
| Health Score | 203% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 190 |
| Sample Rate | 3.17/sec |
| Health Score | 198% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 80-82 cores)</summary>

```
1793722603 82
1793722608 82
1793722613 82
1793722618 82
1793722623 82
1793722628 82
1793722633 82
1793722638 82
1793722643 82
1793722648 82
1793722653 82
1793722658 82
1793722663 82
1793722668 82
1793722673 82
1793722678 82
1793722683 82
1793722688 82
1793722693 82
1793722698 82
```
</details>

---

