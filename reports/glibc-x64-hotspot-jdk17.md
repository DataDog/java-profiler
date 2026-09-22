---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-22 13:10:30 EDT

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
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 9 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (2 unique values: 25-27 cores)</summary>

```
1790096689 25
1790096694 25
1790096699 25
1790096704 25
1790096709 25
1790096714 25
1790096719 25
1790096724 27
1790096729 27
1790096734 25
1790096739 25
1790096744 25
1790096749 25
1790096754 25
1790096759 25
1790096764 25
1790096769 25
1790096774 25
1790096779 25
1790096784 27
```
</details>

---

