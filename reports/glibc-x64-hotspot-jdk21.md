---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 17:06:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 10 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (5 unique values: 70-87 cores)</summary>

```
1794434543 71
1794434548 71
1794434553 71
1794434558 71
1794434563 71
1794434568 71
1794434573 71
1794434578 73
1794434583 73
1794434588 73
1794434593 73
1794434598 70
1794434603 70
1794434608 70
1794434613 70
1794434618 87
1794434623 87
1794434628 87
1794434633 87
1794434638 84
```
</details>

---

