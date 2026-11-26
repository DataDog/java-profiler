---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 10:25:31 EST

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 94 |
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
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 7 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (3 unique values: 71-94 cores)</summary>

```
1795706321 71
1795706326 71
1795706331 75
1795706336 75
1795706341 75
1795706346 75
1795706351 75
1795706356 75
1795706361 75
1795706366 75
1795706371 75
1795706376 75
1795706381 75
1795706386 75
1795706391 75
1795706396 75
1795706401 75
1795706406 75
1795706411 75
1795706416 75
```
</details>

---

