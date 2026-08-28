---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-28 12:57:54 EDT

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 9 |
| Allocations | 323 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 885 |
| Sample Rate | 14.75/sec |
| Health Score | 922% |
| Threads | 11 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (3 unique values: 68-88 cores)</summary>

```
1787935990 88
1787935995 68
1787936000 68
1787936005 68
1787936010 68
1787936015 68
1787936020 68
1787936025 68
1787936030 68
1787936035 68
1787936040 68
1787936045 68
1787936050 68
1787936055 76
1787936060 76
1787936065 76
1787936070 76
1787936075 76
1787936080 76
1787936085 76
```
</details>

---

