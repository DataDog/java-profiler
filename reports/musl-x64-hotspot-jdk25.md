---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-26 06:57:17 EDT

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 11 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (2 unique values: 85-87 cores)</summary>

```
1793011949 87
1793011954 87
1793011959 87
1793011964 87
1793011969 87
1793011974 87
1793011979 87
1793011984 87
1793011989 87
1793011994 87
1793011999 87
1793012004 85
1793012009 85
1793012014 85
1793012019 85
1793012024 85
1793012029 85
1793012034 85
1793012039 85
1793012044 85
```
</details>

---

