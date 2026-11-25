---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 05:36:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 14 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (3 unique values: 33-48 cores)</summary>

```
1795602683 33
1795602688 33
1795602693 33
1795602698 33
1795602703 33
1795602708 33
1795602713 33
1795602718 33
1795602723 33
1795602728 48
1795602733 48
1795602738 48
1795602743 48
1795602748 48
1795602753 48
1795602758 48
1795602763 48
1795602768 48
1795602773 48
1795602778 48
```
</details>

---

