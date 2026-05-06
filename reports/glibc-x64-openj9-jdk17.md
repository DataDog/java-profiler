---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-06 15:34:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 651 |
| Sample Rate | 10.85/sec |
| Health Score | 678% |
| Threads | 10 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (3 unique values: 71-77 cores)</summary>

```
1778095760 77
1778095765 76
1778095770 76
1778095776 76
1778095781 76
1778095786 76
1778095791 76
1778095796 76
1778095801 77
1778095806 77
1778095811 77
1778095816 77
1778095821 77
1778095826 77
1778095831 71
1778095836 71
1778095841 71
1778095846 71
1778095851 71
1778095856 71
```
</details>

---

