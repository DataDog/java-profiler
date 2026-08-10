---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-10 18:31:12 EDT

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
| CPU Cores (start) | 6 |
| CPU Cores (end) | 6 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 8 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 8 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (2 unique values: 6-32 cores)</summary>

```
1786400765 6
1786400770 6
1786400775 6
1786400780 6
1786400785 6
1786400790 6
1786400795 6
1786400800 6
1786400805 6
1786400810 6
1786400815 6
1786400820 6
1786400825 6
1786400830 32
1786400835 32
1786400840 32
1786400845 32
1786400850 32
1786400855 32
1786400860 32
```
</details>

---

