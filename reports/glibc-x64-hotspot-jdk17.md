---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-22 09:50:43 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 433 |
| Sample Rate | 7.22/sec |
| Health Score | 451% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 9 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (4 unique values: 28-45 cores)</summary>

```
1790084718 45
1790084723 45
1790084728 45
1790084733 45
1790084738 28
1790084743 28
1790084748 28
1790084753 28
1790084758 28
1790084763 28
1790084768 28
1790084773 28
1790084778 28
1790084783 28
1790084788 28
1790084793 28
1790084798 38
1790084803 38
1790084808 38
1790084813 38
```
</details>

---

