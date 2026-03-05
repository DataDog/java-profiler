---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-05 15:44:30 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 10 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (3 unique values: 56-80 cores)</summary>

```
1772742940 56
1772742945 56
1772742950 56
1772742955 56
1772742960 56
1772742965 60
1772742970 60
1772742975 60
1772742980 80
1772742985 80
1772742990 80
1772742995 80
1772743000 80
1772743005 80
1772743010 80
1772743015 80
1772743020 80
1772743025 80
1772743030 80
1772743035 80
```
</details>

---

