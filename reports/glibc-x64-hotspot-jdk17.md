---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-29 12:43:57 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 11 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (3 unique values: 49-54 cores)</summary>

```
1793291794 52
1793291799 52
1793291804 52
1793291809 54
1793291814 54
1793291819 49
1793291824 49
1793291829 49
1793291834 49
1793291839 54
1793291844 54
1793291849 54
1793291854 54
1793291859 54
1793291864 54
1793291869 54
1793291874 54
1793291879 54
1793291884 54
1793291889 54
```
</details>

---

