---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-16 05:21:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 11 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (3 unique values: 56-78 cores)</summary>

```
1794824131 57
1794824136 57
1794824141 57
1794824146 57
1794824151 57
1794824156 57
1794824161 78
1794824166 78
1794824171 56
1794824176 56
1794824181 56
1794824186 56
1794824191 56
1794824196 56
1794824201 56
1794824206 56
1794824211 56
1794824216 56
1794824221 56
1794824226 56
```
</details>

---

