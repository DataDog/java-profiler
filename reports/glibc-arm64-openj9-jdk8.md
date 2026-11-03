---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-03 11:22:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1793722593 40
1793722598 40
1793722603 40
1793722608 40
1793722613 40
1793722618 40
1793722623 40
1793722628 40
1793722633 40
1793722638 40
1793722643 40
1793722648 40
1793722653 40
1793722658 40
1793722663 40
1793722668 40
1793722673 40
1793722678 40
1793722683 40
1793722688 40
```
</details>

---

