---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-08 10:53:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 677 |
| Sample Rate | 11.28/sec |
| Health Score | 705% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 910 |
| Sample Rate | 15.17/sec |
| Health Score | 948% |
| Threads | 10 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (3 unique values: 75-83 cores)</summary>

```
1791470956 77
1791470961 75
1791470966 75
1791470971 75
1791470976 75
1791470981 75
1791470986 75
1791470991 77
1791470996 77
1791471001 77
1791471006 83
1791471011 83
1791471016 83
1791471021 83
1791471026 83
1791471031 83
1791471036 83
1791471041 83
1791471046 83
1791471051 83
```
</details>

---

