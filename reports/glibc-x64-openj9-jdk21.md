---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-03-05 15:44:30 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 10 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 739 |
| Sample Rate | 12.32/sec |
| Health Score | 770% |
| Threads | 13 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (5 unique values: 68-79 cores)</summary>

```
1772742915 76
1772742920 76
1772742925 76
1772742930 76
1772742935 76
1772742940 76
1772742945 76
1772742950 76
1772742955 74
1772742960 74
1772742965 74
1772742970 74
1772742975 79
1772742980 79
1772742985 79
1772742990 79
1772742995 79
1772743000 70
1772743005 70
1772743010 70
```
</details>

---

