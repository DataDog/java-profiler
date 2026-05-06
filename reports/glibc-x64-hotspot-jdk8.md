---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-05-06 14:42:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 354 |
| Sample Rate | 5.90/sec |
| Health Score | 369% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 213 |
| Sample Rate | 3.55/sec |
| Health Score | 222% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 41-45 cores)</summary>

```
1778092693 45
1778092698 45
1778092703 45
1778092708 45
1778092713 45
1778092718 41
1778092723 41
1778092728 41
1778092733 41
1778092738 41
1778092743 41
1778092748 41
1778092753 41
1778092758 41
1778092763 41
1778092768 41
1778092773 41
1778092778 41
1778092783 41
1778092788 41
```
</details>

---

