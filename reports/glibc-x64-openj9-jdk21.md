---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-26 06:43:02 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 971 |
| Sample Rate | 16.18/sec |
| Health Score | 1011% |
| Threads | 11 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (2 unique values: 47-49 cores)</summary>

```
1793011073 47
1793011078 47
1793011083 47
1793011088 47
1793011093 47
1793011098 47
1793011103 49
1793011108 49
1793011113 49
1793011118 49
1793011123 49
1793011128 49
1793011133 49
1793011138 49
1793011143 49
1793011149 49
1793011154 49
1793011159 49
1793011164 49
1793011169 49
```
</details>

---

