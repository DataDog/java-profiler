---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 10:50:56 EST

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
| CPU Cores (start) | 21 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 812 |
| Sample Rate | 13.53/sec |
| Health Score | 846% |
| Threads | 9 |
| Allocations | 596 |

<details>
<summary>CPU Timeline (2 unique values: 21-23 cores)</summary>

```
1795189625 21
1795189630 23
1795189635 23
1795189640 23
1795189645 23
1795189650 21
1795189655 21
1795189660 21
1795189665 21
1795189670 21
1795189675 21
1795189680 21
1795189685 21
1795189690 21
1795189695 21
1795189700 21
1795189705 21
1795189710 21
1795189715 21
1795189720 21
```
</details>

---

