---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-22 16:32:55 EST

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 747 |
| Sample Rate | 12.45/sec |
| Health Score | 778% |
| Threads | 10 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (5 unique values: 31-92 cores)</summary>

```
1795382904 31
1795382909 31
1795382914 31
1795382919 78
1795382924 78
1795382929 78
1795382935 74
1795382940 74
1795382945 74
1795382950 74
1795382955 74
1795382960 74
1795382965 74
1795382970 74
1795382975 74
1795382980 74
1795382985 83
1795382990 83
1795382995 92
1795383000 92
```
</details>

---

