---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 09:33:08 EST

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 9 |
| Allocations | 418 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 641 |
| Sample Rate | 10.68/sec |
| Health Score | 668% |
| Threads | 10 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (3 unique values: 69-75 cores)</summary>

```
1795011946 75
1795011951 75
1795011956 75
1795011961 75
1795011966 75
1795011971 75
1795011976 75
1795011981 75
1795011986 75
1795011991 75
1795011996 75
1795012001 75
1795012006 75
1795012011 75
1795012016 75
1795012021 75
1795012026 69
1795012031 69
1795012036 69
1795012041 69
```
</details>

---

