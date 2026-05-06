---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-06 14:42:34 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 10 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (2 unique values: 41-43 cores)</summary>

```
1778092698 43
1778092703 43
1778092708 43
1778092713 43
1778092718 43
1778092723 43
1778092728 43
1778092733 43
1778092738 43
1778092743 43
1778092748 41
1778092753 41
1778092758 41
1778092763 41
1778092768 41
1778092773 41
1778092778 41
1778092783 41
1778092788 41
1778092793 41
```
</details>

---

