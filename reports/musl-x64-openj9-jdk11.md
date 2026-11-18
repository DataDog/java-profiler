---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 09:34:26 EST

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 506 |
| Sample Rate | 8.43/sec |
| Health Score | 527% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1027 |
| Sample Rate | 17.12/sec |
| Health Score | 1070% |
| Threads | 11 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (3 unique values: 76-79 cores)</summary>

```
1795011951 77
1795011956 77
1795011961 77
1795011966 77
1795011971 77
1795011976 79
1795011981 79
1795011986 79
1795011991 76
1795011996 76
1795012001 76
1795012006 76
1795012011 76
1795012016 76
1795012021 76
1795012026 76
1795012031 76
1795012036 76
1795012041 76
1795012046 76
```
</details>

---

