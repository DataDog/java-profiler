---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 08:00:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 9 |
| Allocations | 331 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 286 |
| Sample Rate | 4.77/sec |
| Health Score | 298% |
| Threads | 13 |
| Allocations | 134 |

<details>
<summary>CPU Timeline (3 unique values: 39-51 cores)</summary>

```
1795006516 39
1795006521 39
1795006526 39
1795006531 39
1795006536 39
1795006541 39
1795006546 39
1795006551 39
1795006556 39
1795006561 39
1795006566 39
1795006571 39
1795006576 51
1795006581 51
1795006586 51
1795006591 51
1795006596 51
1795006601 46
1795006606 46
1795006611 46
```
</details>

---

