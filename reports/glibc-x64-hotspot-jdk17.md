---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 12:33:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 453 |
| Sample Rate | 7.55/sec |
| Health Score | 472% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (3 unique values: 38-76 cores)</summary>

```
1795023028 76
1795023033 76
1795023038 76
1795023043 76
1795023048 58
1795023053 58
1795023058 58
1795023063 58
1795023068 58
1795023073 58
1795023078 58
1795023083 58
1795023088 58
1795023093 58
1795023098 58
1795023103 58
1795023108 58
1795023113 58
1795023118 38
1795023123 38
```
</details>

---

