---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-03-05 15:44:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 924 |
| Sample Rate | 15.40/sec |
| Health Score | 962% |
| Threads | 10 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1772742942 46
1772742947 46
1772742952 46
1772742957 46
1772742962 48
1772742967 48
1772742972 48
1772742977 48
1772742982 48
1772742987 48
1772742992 48
1772742997 48
1772743002 48
1772743007 48
1772743012 48
1772743017 48
1772743022 48
1772743027 48
1772743032 48
1772743037 48
```
</details>

---

