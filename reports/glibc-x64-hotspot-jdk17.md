---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-22 15:55:18 EST

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 426 |
| Sample Rate | 7.10/sec |
| Health Score | 444% |
| Threads | 8 |
| Allocations | 328 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 9 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (4 unique values: 25-55 cores)</summary>

```
1795380713 25
1795380718 25
1795380723 25
1795380728 25
1795380733 27
1795380738 27
1795380743 27
1795380748 27
1795380753 29
1795380758 29
1795380763 29
1795380768 29
1795380773 29
1795380778 29
1795380783 29
1795380788 29
1795380793 27
1795380798 27
1795380803 27
1795380808 27
```
</details>

---

