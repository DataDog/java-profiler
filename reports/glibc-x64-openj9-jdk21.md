---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-26 06:57:16 EDT

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
| CPU Cores (start) | 13 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 401 |
| Sample Rate | 6.68/sec |
| Health Score | 418% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 9 |
| Allocations | 425 |

<details>
<summary>CPU Timeline (3 unique values: 13-32 cores)</summary>

```
1793011968 13
1793011973 13
1793011978 13
1793011983 13
1793011988 13
1793011993 13
1793011998 13
1793012003 13
1793012008 15
1793012013 15
1793012018 15
1793012023 15
1793012028 15
1793012033 15
1793012038 15
1793012043 15
1793012048 32
1793012053 32
1793012058 32
1793012063 32
```
</details>

---

