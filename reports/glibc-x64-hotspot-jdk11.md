---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 12:12:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 10 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (4 unique values: 87-91 cores)</summary>

```
1794589613 89
1794589618 89
1794589623 89
1794589628 89
1794589633 89
1794589638 87
1794589643 87
1794589648 87
1794589653 87
1794589658 87
1794589663 87
1794589668 87
1794589673 87
1794589678 89
1794589683 89
1794589688 89
1794589693 91
1794589698 91
1794589703 91
1794589708 91
```
</details>

---

