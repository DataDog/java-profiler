---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-04 10:58:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
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
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793807598 48
1793807603 48
1793807608 43
1793807613 43
1793807618 43
1793807623 43
1793807628 43
1793807633 43
1793807638 43
1793807643 43
1793807648 43
1793807653 43
1793807658 43
1793807663 48
1793807668 48
1793807673 48
1793807678 48
1793807683 48
1793807688 48
1793807693 48
```
</details>

---

