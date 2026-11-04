---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 00:07:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 11 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (2 unique values: 67-90 cores)</summary>

```
1793768588 90
1793768593 90
1793768598 90
1793768603 90
1793768608 90
1793768613 90
1793768618 67
1793768623 67
1793768628 67
1793768633 67
1793768638 67
1793768643 67
1793768648 67
1793768653 67
1793768658 67
1793768663 67
1793768668 67
1793768673 67
1793768678 67
1793768683 67
```
</details>

---

