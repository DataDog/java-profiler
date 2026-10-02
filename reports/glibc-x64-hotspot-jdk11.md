---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-02 12:03:18 EDT

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 989 |
| Sample Rate | 16.48/sec |
| Health Score | 1030% |
| Threads | 10 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (2 unique values: 84-86 cores)</summary>

```
1790956803 84
1790956808 84
1790956813 84
1790956818 84
1790956823 84
1790956828 84
1790956833 84
1790956838 84
1790956843 84
1790956848 84
1790956853 86
1790956858 86
1790956863 86
1790956868 86
1790956873 86
1790956878 86
1790956883 86
1790956888 86
1790956893 86
1790956898 86
```
</details>

---

