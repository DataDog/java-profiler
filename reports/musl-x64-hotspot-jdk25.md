---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 11:32:49 EST

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 663 |
| Sample Rate | 11.05/sec |
| Health Score | 691% |
| Threads | 11 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (2 unique values: 58-61 cores)</summary>

```
1795192064 61
1795192069 61
1795192074 61
1795192079 61
1795192084 61
1795192089 61
1795192094 61
1795192099 61
1795192104 61
1795192109 61
1795192114 61
1795192119 58
1795192124 58
1795192130 58
1795192135 58
1795192140 58
1795192145 58
1795192150 58
1795192155 58
1795192160 58
```
</details>

---

