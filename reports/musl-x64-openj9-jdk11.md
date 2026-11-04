---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 10:58:24 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 9 |
| Allocations | 584 |

<details>
<summary>CPU Timeline (2 unique values: 49-55 cores)</summary>

```
1793807598 49
1793807603 49
1793807608 49
1793807613 49
1793807618 49
1793807623 49
1793807628 49
1793807633 49
1793807638 49
1793807643 49
1793807648 49
1793807653 49
1793807658 49
1793807663 49
1793807668 49
1793807673 49
1793807678 49
1793807683 49
1793807688 49
1793807693 49
```
</details>

---

