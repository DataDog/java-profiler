---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-07 06:54:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1052 |
| Sample Rate | 17.53/sec |
| Health Score | 1096% |
| Threads | 11 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (4 unique values: 76-81 cores)</summary>

```
1778151006 81
1778151011 81
1778151016 81
1778151021 81
1778151026 81
1778151031 81
1778151036 81
1778151041 79
1778151046 79
1778151051 76
1778151056 76
1778151061 78
1778151066 78
1778151071 78
1778151076 78
1778151081 78
1778151086 78
1778151091 78
1778151097 78
1778151102 78
```
</details>

---

