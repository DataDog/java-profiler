---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-27 06:17:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 9 |
| Allocations | 430 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 834 |
| Sample Rate | 13.90/sec |
| Health Score | 869% |
| Threads | 11 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (3 unique values: 62-66 cores)</summary>

```
1795777983 66
1795777988 66
1795777993 66
1795777998 66
1795778003 66
1795778008 66
1795778013 66
1795778018 66
1795778023 66
1795778028 64
1795778033 64
1795778038 64
1795778043 64
1795778048 64
1795778053 64
1795778058 64
1795778063 64
1795778068 64
1795778073 64
1795778078 62
```
</details>

---

