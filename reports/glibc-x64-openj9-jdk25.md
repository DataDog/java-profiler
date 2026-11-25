---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 10:08:10 EST

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 383 |
| Sample Rate | 6.38/sec |
| Health Score | 399% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 10 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (4 unique values: 66-96 cores)</summary>

```
1795618920 66
1795618925 66
1795618930 66
1795618935 66
1795618940 66
1795618945 66
1795618950 66
1795618955 66
1795618960 66
1795618965 75
1795618970 75
1795618975 75
1795618981 75
1795618986 75
1795618991 75
1795618996 75
1795619001 75
1795619006 96
1795619011 96
1795619016 96
```
</details>

---

