---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 18:03:52 EST

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 732 |
| Sample Rate | 12.20/sec |
| Health Score | 762% |
| Threads | 9 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (3 unique values: 27-32 cores)</summary>

```
1794524327 27
1794524332 27
1794524337 27
1794524342 27
1794524347 27
1794524352 27
1794524357 27
1794524362 27
1794524367 27
1794524372 27
1794524377 27
1794524382 27
1794524387 27
1794524392 27
1794524397 27
1794524402 32
1794524407 32
1794524412 32
1794524417 29
1794524422 29
```
</details>

---

