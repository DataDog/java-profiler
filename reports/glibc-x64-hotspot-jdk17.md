---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-11 11:23:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 676 |
| Sample Rate | 11.27/sec |
| Health Score | 704% |
| Threads | 11 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (3 unique values: 67-77 cores)</summary>

```
1778512723 67
1778512728 67
1778512733 67
1778512738 67
1778512743 72
1778512748 72
1778512753 72
1778512758 72
1778512763 72
1778512768 72
1778512773 72
1778512778 72
1778512783 72
1778512788 72
1778512793 72
1778512798 67
1778512803 67
1778512808 67
1778512813 67
1778512818 67
```
</details>

---

