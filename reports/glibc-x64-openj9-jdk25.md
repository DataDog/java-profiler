---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-05 15:44:30 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 11 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 745 |
| Sample Rate | 12.42/sec |
| Health Score | 776% |
| Threads | 13 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (6 unique values: 68-79 cores)</summary>

```
1772742909 76
1772742914 76
1772742919 76
1772742924 76
1772742929 76
1772742934 76
1772742939 76
1772742944 76
1772742950 76
1772742955 74
1772742960 74
1772742965 74
1772742970 74
1772742975 74
1772742980 79
1772742985 79
1772742990 79
1772742995 79
1772743000 75
1772743005 75
```
</details>

---

