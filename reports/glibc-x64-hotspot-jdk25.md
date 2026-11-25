---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 16:21:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 43 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 11 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1795641315 81
1795641320 81
1795641325 81
1795641330 81
1795641335 81
1795641340 81
1795641345 81
1795641350 81
1795641355 81
1795641360 81
1795641365 81
1795641370 81
1795641375 81
1795641380 81
1795641385 81
1795641390 81
1795641395 79
1795641400 79
1795641405 79
1795641410 79
```
</details>

---

