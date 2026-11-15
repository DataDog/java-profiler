---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-14 19:51:05 EST

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 8 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 11 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (3 unique values: 44-59 cores)</summary>

```
1794703653 44
1794703658 44
1794703663 44
1794703668 44
1794703673 44
1794703678 44
1794703683 44
1794703688 44
1794703693 57
1794703698 57
1794703703 57
1794703708 57
1794703713 57
1794703718 57
1794703723 57
1794703728 57
1794703733 57
1794703738 57
1794703743 59
1794703748 59
```
</details>

---

