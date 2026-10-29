---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-29 12:44:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 641 |
| Sample Rate | 10.68/sec |
| Health Score | 668% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 773 |
| Sample Rate | 12.88/sec |
| Health Score | 805% |
| Threads | 12 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (4 unique values: 65-85 cores)</summary>

```
1793291814 85
1793291819 85
1793291824 85
1793291829 85
1793291834 81
1793291839 81
1793291844 84
1793291849 84
1793291854 84
1793291859 84
1793291864 84
1793291869 84
1793291874 84
1793291879 65
1793291884 65
1793291889 65
1793291894 65
1793291899 65
1793291904 65
1793291909 65
```
</details>

---

