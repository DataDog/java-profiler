---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-03-11 14:07:41 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 8 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 10 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (3 unique values: 57-61 cores)</summary>

```
1773252245 59
1773252250 59
1773252255 59
1773252260 59
1773252265 59
1773252270 59
1773252275 59
1773252280 61
1773252285 61
1773252290 61
1773252295 61
1773252300 61
1773252305 61
1773252310 59
1773252315 59
1773252320 59
1773252325 59
1773252330 57
1773252335 57
1773252340 57
```
</details>

---

