---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-08 10:54:34 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 11 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1791470941 61
1791470946 61
1791470951 61
1791470956 59
1791470961 59
1791470966 59
1791470971 59
1791470976 61
1791470981 61
1791470986 61
1791470991 59
1791470996 59
1791471001 59
1791471006 59
1791471011 59
1791471016 59
1791471021 59
1791471026 59
1791471031 59
1791471036 59
```
</details>

---

