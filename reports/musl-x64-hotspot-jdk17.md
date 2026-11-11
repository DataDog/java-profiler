---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 15:02:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 758 |
| Sample Rate | 12.63/sec |
| Health Score | 789% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (4 unique values: 82-88 cores)</summary>

```
1794427025 86
1794427030 86
1794427035 86
1794427040 84
1794427045 84
1794427050 86
1794427055 86
1794427060 86
1794427065 88
1794427070 88
1794427075 86
1794427080 86
1794427085 86
1794427090 86
1794427095 86
1794427100 86
1794427105 86
1794427111 86
1794427116 86
1794427121 82
```
</details>

---

