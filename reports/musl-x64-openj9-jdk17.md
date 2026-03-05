---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-05 15:44:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 11 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (3 unique values: 33-38 cores)</summary>

```
1772742905 33
1772742910 33
1772742915 38
1772742920 38
1772742925 38
1772742930 38
1772742935 38
1772742940 38
1772742945 38
1772742950 38
1772742955 33
1772742960 33
1772742965 33
1772742970 33
1772742975 33
1772742980 33
1772742985 33
1772742990 33
1772742995 37
1772743000 37
```
</details>

---

