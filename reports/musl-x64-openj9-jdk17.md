---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-12 05:19:45 EDT

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 835 |
| Sample Rate | 13.92/sec |
| Health Score | 870% |
| Threads | 11 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (5 unique values: 73-79 cores)</summary>

```
1778577281 78
1778577286 78
1778577291 78
1778577296 74
1778577301 74
1778577306 74
1778577311 76
1778577316 76
1778577321 76
1778577326 76
1778577331 76
1778577336 76
1778577341 76
1778577346 76
1778577351 79
1778577356 79
1778577361 79
1778577366 79
1778577371 79
1778577376 73
```
</details>

---

