---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 12:23:48 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 716 |
| Sample Rate | 11.93/sec |
| Health Score | 746% |
| Threads | 10 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (6 unique values: 60-71 cores)</summary>

```
1795627041 60
1795627046 69
1795627051 69
1795627056 71
1795627061 71
1795627066 67
1795627071 67
1795627076 67
1795627081 67
1795627086 67
1795627091 67
1795627096 67
1795627101 67
1795627106 67
1795627111 65
1795627116 65
1795627121 63
1795627126 63
1795627132 63
1795627137 63
```
</details>

---

