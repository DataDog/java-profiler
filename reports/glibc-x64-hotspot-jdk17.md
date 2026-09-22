---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-22 11:52:08 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 9 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 761 |
| Sample Rate | 12.68/sec |
| Health Score | 792% |
| Threads | 11 |
| Allocations | 428 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1790091847 64
1790091852 64
1790091857 64
1790091862 64
1790091867 64
1790091872 64
1790091877 66
1790091882 66
1790091887 66
1790091892 66
1790091897 66
1790091902 66
1790091907 66
1790091912 66
1790091917 66
1790091922 66
1790091927 66
1790091932 66
1790091937 66
1790091942 66
```
</details>

---

