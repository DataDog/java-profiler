---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 09:31:54 EST

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 506 |
| Sample Rate | 8.43/sec |
| Health Score | 527% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 848 |
| Sample Rate | 14.13/sec |
| Health Score | 883% |
| Threads | 11 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (4 unique values: 62-71 cores)</summary>

```
1795012019 67
1795012024 69
1795012029 69
1795012034 67
1795012039 67
1795012044 62
1795012049 62
1795012054 62
1795012059 62
1795012064 62
1795012069 62
1795012074 62
1795012079 62
1795012084 62
1795012090 62
1795012095 62
1795012100 62
1795012105 62
1795012110 62
1795012115 62
```
</details>

---

