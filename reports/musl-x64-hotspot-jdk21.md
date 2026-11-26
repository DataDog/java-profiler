---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-26 10:25:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 10 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 11 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (3 unique values: 58-62 cores)</summary>

```
1795706321 58
1795706326 58
1795706331 58
1795706336 58
1795706341 58
1795706346 58
1795706351 58
1795706356 58
1795706361 58
1795706366 58
1795706371 60
1795706376 60
1795706381 60
1795706386 60
1795706391 60
1795706396 60
1795706401 60
1795706406 62
1795706411 62
1795706416 60
```
</details>

---

