---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-02 12:03:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 11 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (4 unique values: 75-85 cores)</summary>

```
1790956784 77
1790956789 77
1790956794 77
1790956799 77
1790956804 77
1790956809 77
1790956814 77
1790956819 77
1790956824 75
1790956829 75
1790956834 75
1790956839 75
1790956844 75
1790956849 85
1790956854 85
1790956859 85
1790956864 85
1790956869 85
1790956875 85
1790956880 85
```
</details>

---

