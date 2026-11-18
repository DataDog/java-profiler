---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 09:30:44 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 10 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (6 unique values: 66-76 cores)</summary>

```
1795011960 76
1795011965 76
1795011970 76
1795011976 76
1795011981 76
1795011986 74
1795011991 74
1795011996 74
1795012001 72
1795012006 72
1795012011 72
1795012016 72
1795012021 66
1795012026 66
1795012031 66
1795012036 66
1795012041 66
1795012046 66
1795012051 66
1795012056 68
```
</details>

---

