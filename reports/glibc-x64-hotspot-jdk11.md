---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 09:33:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 822 |
| Sample Rate | 13.70/sec |
| Health Score | 856% |
| Threads | 9 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (2 unique values: 40-62 cores)</summary>

```
1795011979 62
1795011984 62
1795011989 62
1795011994 62
1795011999 62
1795012004 62
1795012009 62
1795012014 62
1795012019 62
1795012024 62
1795012029 62
1795012034 62
1795012039 62
1795012044 62
1795012049 62
1795012054 62
1795012059 62
1795012064 62
1795012069 62
1795012074 62
```
</details>

---

