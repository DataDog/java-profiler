---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-11 15:02:16 EST

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 823 |
| Sample Rate | 13.72/sec |
| Health Score | 857% |
| Threads | 11 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (3 unique values: 55-93 cores)</summary>

```
1794427055 55
1794427060 55
1794427065 55
1794427070 55
1794427075 93
1794427080 93
1794427085 93
1794427090 93
1794427095 93
1794427100 93
1794427105 72
1794427110 72
1794427115 72
1794427120 72
1794427125 72
1794427130 72
1794427135 72
1794427140 72
1794427145 72
1794427150 72
```
</details>

---

