---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-11 11:23:12 EDT

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 669 |
| Sample Rate | 11.15/sec |
| Health Score | 697% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 767 |
| Sample Rate | 12.78/sec |
| Health Score | 799% |
| Threads | 10 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (4 unique values: 82-85 cores)</summary>

```
1778512713 82
1778512718 82
1778512723 82
1778512728 82
1778512733 84
1778512738 84
1778512743 84
1778512748 83
1778512753 83
1778512758 83
1778512763 85
1778512768 85
1778512773 85
1778512778 85
1778512783 85
1778512788 85
1778512793 85
1778512798 85
1778512803 83
1778512808 83
```
</details>

---

