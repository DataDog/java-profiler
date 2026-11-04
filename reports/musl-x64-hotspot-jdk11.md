---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 10:58:23 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 808 |
| Sample Rate | 13.47/sec |
| Health Score | 842% |
| Threads | 9 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (4 unique values: 81-87 cores)</summary>

```
1793807593 87
1793807598 87
1793807603 87
1793807608 87
1793807613 87
1793807618 87
1793807623 87
1793807628 87
1793807633 87
1793807638 85
1793807643 85
1793807648 81
1793807653 81
1793807658 81
1793807663 81
1793807668 81
1793807673 81
1793807678 81
1793807683 81
1793807688 81
```
</details>

---

