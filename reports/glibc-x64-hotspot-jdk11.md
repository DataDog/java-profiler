---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-16 07:25:14 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 996 |
| Sample Rate | 16.60/sec |
| Health Score | 1038% |
| Threads | 9 |
| Allocations | 431 |

<details>
<summary>CPU Timeline (2 unique values: 56-58 cores)</summary>

```
1794831591 56
1794831596 56
1794831602 56
1794831607 56
1794831612 56
1794831617 56
1794831622 56
1794831627 58
1794831632 58
1794831637 58
1794831642 58
1794831647 58
1794831652 58
1794831657 58
1794831662 58
1794831667 58
1794831672 58
1794831677 58
1794831682 58
1794831687 58
```
</details>

---

