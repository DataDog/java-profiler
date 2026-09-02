---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-02 11:43:32 EDT

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 776 |
| Sample Rate | 12.93/sec |
| Health Score | 808% |
| Threads | 10 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1788363604 92
1788363609 92
1788363614 92
1788363619 92
1788363624 92
1788363629 92
1788363634 94
1788363639 94
1788363644 94
1788363649 94
1788363654 94
1788363659 94
1788363664 96
1788363669 96
1788363674 96
1788363679 96
1788363684 96
1788363689 96
1788363694 96
1788363699 96
```
</details>

---

