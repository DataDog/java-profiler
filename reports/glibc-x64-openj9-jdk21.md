---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-02 12:03:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 11 |
| Allocations | 481 |

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
1790956844 85
1790956849 85
1790956854 85
1790956859 85
1790956864 85
1790956869 85
1790956874 85
1790956879 85
```
</details>

---

