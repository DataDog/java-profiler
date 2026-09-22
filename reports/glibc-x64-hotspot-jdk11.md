---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 11:47:42 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 799 |
| Sample Rate | 13.32/sec |
| Health Score | 832% |
| Threads | 9 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (7 unique values: 73-84 cores)</summary>

```
1790091694 75
1790091699 75
1790091704 75
1790091709 75
1790091714 75
1790091719 75
1790091724 75
1790091729 75
1790091734 77
1790091739 77
1790091744 78
1790091749 78
1790091754 78
1790091759 73
1790091764 73
1790091769 73
1790091774 73
1790091779 73
1790091784 75
1790091789 75
```
</details>

---

