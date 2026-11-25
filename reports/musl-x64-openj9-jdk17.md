---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 16:19:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 6 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (3 unique values: 25-39 cores)</summary>

```
1795641280 25
1795641285 34
1795641290 34
1795641295 34
1795641300 34
1795641305 34
1795641310 34
1795641315 39
1795641320 39
1795641325 39
1795641330 39
1795641335 39
1795641340 39
1795641345 39
1795641350 39
1795641355 39
1795641360 39
1795641365 39
1795641370 39
1795641375 39
```
</details>

---

